#include <raylib.h>
#include <time.h>
#include "neighbourPixl.h"
#include "pixl.h"
#include <stdio.h>
#include <stdlib.h>

const int width = 400;
const int height = 200;
int scale = 5;
int screenWidth;
int screenHeight;

short isPaused = 0;

int targetFPS = 24;
int minFPS = 1;
int maxFPS = 60;

Color* pixls;

unsigned char windowIcon[256*256*4];

int updateType = 0;

int main(void)
{
    setWidthHeight(scale);

    setIcon();

    InitWindow(screenWidth, screenHeight, "PIXL");
    
    SetWindowIcon((Image){windowIcon, 256, 256, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8});

    SetRandomSeed(time(NULL));
    SetTargetFPS(targetFPS);
    pixlsAlloc();
    setPixls();
    while(!WindowShouldClose())
    {
        checkInput();
        if (!isPaused) { updateFromType(); }
        else if (IsKeyPressed(KEY_PERIOD)) { updateFromType(); }
        BeginDrawing();
        drawPixlsRect();
        EndDrawing();
    }
    pixlsDealloc();
    CloseWindow();
}

void setWidthHeight(int scale)
{
    screenWidth = width*scale;
    screenHeight = height*scale;
}

void setIcon()
{
    for (int i = 0; i < 256*256; i++)
    {
        for (int j = 0; j<3; j++)
        {
            windowIcon[j+i*4] = GetRandomValue(0, 255);
        }
        windowIcon[3+i*4] = 255;
    }
}

void setPixls()
{
    for (int i = 0; i < width*height; i++)
    {
        pixls[i].a = 255;
        pixls[i].r = GetRandomValue(0, 255);
        pixls[i].g = GetRandomValue(0, 255);
        pixls[i].b = GetRandomValue(0, 255);
    }
}

void setPixls216Colors()
{
    for (int i = 0; i < width*height; i++)
    {
        pixls[i].a = 255;
        pixls[i].r = 50*GetRandomValue(0, 5);
        pixls[i].g = 50*GetRandomValue(0, 5);
        pixls[i].b = 50*GetRandomValue(0, 5);
        printf("pixl #%d - %d, %d, %d,  ", i, pixls[i].r, pixls[i].g, pixls[i].b);
    }
}

void setPixlsGreyscale()
{
    int rng;
    for (int i = 0; i < width*height; i++)
    {
        rng = GetRandomValue(0, 255);
        pixls[i].a = 255;
        pixls[i].r = rng;
        pixls[i].g = rng;
        pixls[i].b = rng;
    }
}


void checkInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        if (isPaused) { isPaused = 0;}
        else isPaused = 1;
    } else if (IsKeyPressed(KEY_MINUS) || IsKeyDown(KEY_MINUS))
    {
        if (targetFPS>minFPS)
        {
            targetFPS--;
            printf("Current frames per second: %d --- ", targetFPS);
            SetTargetFPS(targetFPS);
        }
    } else if (IsKeyPressed(KEY_EQUAL) || IsKeyDown(KEY_EQUAL))
    {
        if (targetFPS<maxFPS) 
        {
            targetFPS++;
            printf("Current frames per second: %d --- ", targetFPS);
            SetTargetFPS(targetFPS);
        }
    } else if (IsKeyPressed(KEY_R))
    {
        setPixls();
    } else if (IsKeyPressed(KEY_G))
    {
        setPixlsGreyscale();
    } else if (IsKeyPressed(KEY_C))
    {
        updateType = COMBINE;
    } else if (IsKeyPressed(KEY_N))
    {
        updateType = NORMAL;
    } else if (IsKeyPressed(KEY_H))
    {
        updateType = HIGHER; // doesn't work
    } else if (IsKeyPressed(KEY_L))
    {
        updateType = LOWER; // not implemented
    }
    
}

void updateFromType()
{
    switch(updateType)
    {
        case COMBINE:
            updatePixlsCombine();
            break;
        case HIGHER:
            updatePixlsHigher(); /* Why do you not work ;(*/
            break;
        default:
            updatePixlsFast();
    }
}

void updatePixlsFast()
{
    pixls[0] = pixls[getNeighbourPixelNW(width)];
    for (int j = 1; j < width-1; j++)
    {
        pixls[j] = pixls[getNeighbourPixelN(j, width)]; 
    }
    pixls[width-1] = pixls[getNeighbourPixelNE(width)];

    for (int i = 1; i < height-1; i++)
    {
        pixls[i*width] = pixls[getNeighbourPixelW(i*width, width)];
        for (int k = 1; k < width-1; k++)
        {
            pixls[k+width*i] = pixls[getNeighbourPixelM(k+width*i, width)];
        }
        pixls[width*i+width-1] = pixls[getNeighbourPixelE(width*i+width-1, width)];
    }

    pixls[(height-1)*width] = pixls[getNeighbourPixelSW(width, height)];
    for (int l = 1; l < width-1; l++)
    {
        pixls[l+width*(height-1)] = pixls[getNeighbourPixelS(l+width*(height-1), width)];
    }
    pixls[width*(height-1)+width-1] = pixls[getNeighbourPixelSE(width, height)];
}

void updatePixlsCombine()
{
    int nbpixl = getNeighbourPixelNW(width);
    Color mean = mean2pixls(pixls[0], pixls[nbpixl]);
    pixls[0] = mean;
    pixls[nbpixl] = mean;
    for (int j = 1; j < width-1; j++)
    {
        nbpixl = getNeighbourPixelN(j, width);
        mean = mean2pixls(pixls[j], pixls[nbpixl]);
        pixls[j] = mean;
        pixls[nbpixl] = mean; 
    }
    nbpixl = getNeighbourPixelNE(width);
    mean = mean2pixls(pixls[width-1], pixls[nbpixl]);
    pixls[width-1] = mean;
    pixls[nbpixl] = mean;

    for (int i = 1; i < height-1; i++)
    {
        nbpixl = getNeighbourPixelW(i*width, width);
        mean = mean2pixls(pixls[i*width], pixls[nbpixl]);
        pixls[i*width] = mean;
        pixls[nbpixl] = mean;
        for (int k = 1; k < width-1; k++)
        {
            nbpixl = getNeighbourPixelM(k+width*i, width);
            mean = mean2pixls(pixls[k+width*1], pixls[nbpixl]);
            pixls[k+width*i] = mean;
            pixls[nbpixl] = mean;
        }
        nbpixl = getNeighbourPixelE(width*i+width-1, width);
        mean = mean2pixls(pixls[width*i+width-1], pixls[nbpixl]);
        pixls[width*i+width-1] = mean;
        pixls[nbpixl] = mean;
    }

    nbpixl = getNeighbourPixelSW(width, height);
    mean = mean2pixls(pixls[(height-1)*width], pixls[nbpixl]);
    pixls[(height-1)*width] = mean;
    pixls[nbpixl] = mean;
    for (int l = 1; l < width-1; l++)
    {
        nbpixl = getNeighbourPixelS(l+width*(height-1), width);
        mean = mean2pixls(pixls[l+width*(height-1)], pixls[nbpixl]);
        pixls[l+width*(height-1)] = mean;
        pixls[nbpixl] = mean;
    }
    nbpixl = getNeighbourPixelSE(width, height);
    mean = mean2pixls(pixls[width*(height-1)+width-1], pixls[nbpixl]);
    pixls[width*(height-1)+width-1] = mean;
    pixls[nbpixl]= mean;
}

/* For some reason this function breaks the program */
void updatePixlsHigher()
{
    pixls[0] = high2pixls(pixls[0], pixls[getNeighbourPixelNW(width)]);
    for (int j = 1; j < width-1; j++)
    {
        pixls[j] = high2pixls(pixls[j], pixls[getNeighbourPixelN(j, width)]); 
    }
    pixls[width-1] = high2pixls(pixls[width-1], pixls[getNeighbourPixelNE(width)]);

    for (int i = 1; i < height-1; i++)
    {
        pixls[i*width] = high2pixls(pixls[i*width], pixls[getNeighbourPixelW(i*width, width)]);
        for (int k = 1; k < width-1; k++)
        {
            pixls[k+width*i] = high2pixls(pixls[k+width*i], pixls[getNeighbourPixelM(k+width*i, width)]);
        }
        pixls[width*i+width-1] = high2pixls(pixls[width*i+width-1], pixls[getNeighbourPixelE(width*i+width-1, width)]);
    }

    pixls[(height-1)*width] = high2pixls(pixls[(height-1)*width], pixls[getNeighbourPixelSW(width, height)]);
    for (int l = 1; l < width-1; l++)
    {
        pixls[l+width*(height-1)] = high2pixls(pixls[l+width*(height-1)], pixls[getNeighbourPixelS(l+width*(height-1), width)]);
    }
    pixls[width*(height-1)+width-1] = high2pixls(pixls[width*(height-1)+width-1], pixls[getNeighbourPixelSE(width, height)]);
}

Color mean2pixls(Color p1, Color p2)
{
    Color p3;
    p3.r = (p1.r+p2.r)/2;
    p3.g = (p1.g+p2.g)/2;
    p3.b = (p1.b+p2.b)/2;
    p3.a = 255;
    return p3;
}

Color high2pixls(Color p1, Color p2)
{
    Color p3;
    if (p1.r > p2.r) {p3.r = p1.r;} else p3.r = p2.r;
    if (p1.g > p2.g) {p3.g = p1.g;} else p3.g = p2.g;
    if (p1.b > p2.b) {p3.b = p1.b;} else p3.b = p2.b;
    return p3;
}

void drawPixls()
{
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            DrawPixel(j, i, pixls[ j + width*i ]);
        }
    }
}

void drawPixlsVector()
{
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            DrawPixelV((Vector2){j, i}, pixls[ j + width*i ]);
        }
    }
}

void drawPixlsRect()
{
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            DrawRectangle(j*scale, i*scale, scale, scale, pixls[ j + width*i ]);
        }
    }
}

void pixlsAlloc()
{
    pixls = MemAlloc(width*height * sizeof(Color));
}

void pixlsDealloc()
{
    MemFree(pixls);
}

