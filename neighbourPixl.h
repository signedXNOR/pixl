#ifndef NEIGHBOURPIXL_H
#define NEIGHBOURPIXL_H

int getNeighbourPixelNW(int width);
int getNeighbourPixelN(int pixl, int width);
int getNeighbourPixelNE(int width);
int getNeighbourPixelW(int pixl, int width);
int getNeighbourPixelE(int pixl, int width);
int getNeighbourPixelSW(int width, int height);
int getNeighbourPixelS(int pixl, int width);
int getNeighbourPixelSE(int width, int height);
int getNeighbourPixelM(int pixl, int width);

#endif