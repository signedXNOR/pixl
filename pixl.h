#ifndef PIXL_H
#define PIXL_X

#include <raylib.h>


void pixlsAlloc();
void pixlsDealloc();
void drawPixls();
void setPixls();
void drawPixlsVector();
void setPixls216Colors();
void setPixlsGreyscale();
void updatePixlsFast();
void setWidthHeight(int scale);
void drawPixlsRect();
void checkInput();
void setIcon();
void updatePixlsCombine();
void updatePixlsHigher();
void updateFromType();
Color mean2pixls(Color p1, Color p2);
Color high2pixls(Color p1, Color p2);

typedef enum {
    NORMAL,
    COMBINE,
    HIGHER,
    LOWER
} UpdateType;



#endif