#include "pixl.h"
#include "neighbourPixl.h"
#include <stdio.h>

int getNeighbourPixelNW(int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 3);
    switch(rng)
    {
        case 1:
            nbPixl = 1; /* RIGHT */
            break;
        case 2:
            nbPixl = width; /* BOTTOM */
            break;
        case 3:
            nbPixl = width+1; /* BOTTOM RIGHT */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelN(int pixl, int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 5);
    switch(rng)
    {
        case 1:
            nbPixl = pixl-1; /* LEFT */
            break;
        case 2:
            nbPixl = pixl+1; /* RIGHT */
            break;
        case 3:
            nbPixl = pixl+width-1; /* BOTTOM LEFT */
            break;
        case 4:
            nbPixl = pixl+width; /* BOTTOM */
            break;
        case 5:
            nbPixl = pixl+width+1; /* BOTTOM RIGHT */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelNE(int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 3);
    switch(rng)
    {
        case 1:
            nbPixl = width-1-1; /* LEFT */
            break;
        case 2:
            nbPixl = width-1+width-1; /* BOTTOM LEFT */
            break;
        case 3:
            nbPixl = width-1+width; /* BOTTOM */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelW(int pixl, int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 5);
    switch(rng)
    {
        case 1:
            nbPixl = pixl-width; /* TOP */
            break;
        case 2:
            nbPixl = pixl-width+1; /* TOP RIGHT */
            break;
        case 3:
            nbPixl = pixl+1; /* RIGHT */
            break;
        case 4:
            nbPixl = pixl+width; /* BOTTOM */
            break;
        case 5:
            nbPixl = pixl+width+1; /* BOTTOM RIGHT */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelE(int pixl, int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 5);
    switch(rng)
    {
        case 1:
            nbPixl = pixl-width-1; /* TOP LEFT*/
            break;
        case 2:
            nbPixl = pixl-width; /* TOP */
            break;
        case 3:
            nbPixl = pixl-1; /* LEFT */
            break;
        case 4:
            nbPixl = pixl+width-1; /* BOTTOM LEFT */
            break;
        case 5:
            nbPixl = pixl+width; /* BOTTOM */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelSW(int width, int height)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 3);
    switch(rng)
    {
        case 1:
            nbPixl = (width*(height-1))-width; /* TOP */
            break;
        case 2:
            nbPixl = (width*(height-1))-width+1; /* TOP RIGHT */
            break;
        case 3:
            nbPixl = (width*(height-1))+1; /* RIGHT */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelS(int pixl, int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 5);
    switch(rng)
    {
        case 1:
            nbPixl = pixl-width-1; /* TOP LEFT */
            break;
        case 2:
            nbPixl = pixl-width; /* TOP */
            break;
        case 3:
            nbPixl = pixl-width+1; /* TOP RIGHT */
            break;
        case 4:
            nbPixl = pixl-1; /* LEFT */
            break;
        case 5:
            nbPixl = pixl+1; /* RIGHT */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelSE(int width, int height)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 3);
    switch(rng)
    {
        case 1:
            nbPixl = (width*height-1)-width-1; /* TOP LEFT*/
            break;
        case 2:
            nbPixl = (width*height-1)-width; /* TOP */
            break;
        case 3:
            nbPixl = (width*height-1)-1; /* LEFT */
            break;
    }
    return nbPixl;
}

int getNeighbourPixelM(int pixl, int width)
{
    int rng;
    int nbPixl = 0;
    rng = GetRandomValue(1, 8);
    switch(rng)
    {
        case 1:
            nbPixl = pixl-width-1; /* TOP LEFT*/
            break;
        case 2:
            nbPixl = pixl-width; /* TOP */
            break;
        case 3:
            nbPixl = pixl-width+1; /* TOP RIGHT */
            break;
        case 4:
            nbPixl = pixl-1; /*  LEFT */
            break;
        case 5:
            nbPixl = pixl+1; /* RIGHT */
            break;
        case 6:
            nbPixl = pixl+width-1; /* BOTTOM LEFT */
            break;
        case 7:
            nbPixl = pixl+width; /* BOTTOM */
            break;
        case 8:
            nbPixl = pixl+width+1; /* BOTTOM RIGHT */
            break;
    }
    return nbPixl;
}