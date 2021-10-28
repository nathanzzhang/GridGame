#pragma once
// Grid library interface

#ifndef GRID_INCLUDED
#define GRID_INCLUDED

const int MAXROWS = 25;
const int MAXCOLS = 30;

void setSize(int nr, int nc);
int getRows();
int getCols();
void setWall(int r, int c);
bool isWall(int r, int c);
void draw(int rStart, int cStart, int rEnd, int cEnd);
void draw(int rStart, int cStart, int rEnd, int cEnd, int rCar, int cCar);

#endif // GRID_INCLUDED