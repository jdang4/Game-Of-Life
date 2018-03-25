/**
 * twoD.h
 *
 * @author: Mike Ciaraldi
 */

#ifndef TWOD_H_
#define TWOD_H_

// Function prototypes:
int** make2Dint(int rows, int columns);
char** make2Dchar(int rows, int columns);
void printGrid(int maxR, int maxC, char** grid);
void centerGrid(int maxR, int maxCol, int row, int column, char** grid0, char **grid1);
int sameGrids(int maxR, int maxCol, char **grid1, char **grid2);
char isCellValid(int maxR, int maxC, int currentR, int currentC, char **grid);
int getNeighbors(int maxR, int maxC, int currentR, int currentC, char **grid);
int allDeadCells(int maxR, int maxC, char **grid);

#endif /* 2D_H_ */
