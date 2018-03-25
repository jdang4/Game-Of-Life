#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"


/** Make a 2D array of integers
 *
 * @param rows Number of rows
 * @param columns Number of columns
 * @return Pointer to the array of pointers to the rows.
 * 	  or null pointer if unable to allocate memory.
 * 	  Note: Will not free partially-allocated memory.
 *
 * @author Mike Ciaraldi
 */
// Do not use this function at all
int** make2Dint(int rows, int columns) {

	int **a; // Array of pointers to rows
	unsigned int i; // Loop counter

	// First allocate the array of pointers to rows
	a = (int **) malloc(rows * sizeof(int *));
	if (!a) { // Unable to allocate the array
		return (int **) NULL;
	}

	// Now allocate array for each row
	for (i = 0; i < rows; i++) {
		// i is the row we are about to allocate
		a[i] = malloc(columns * sizeof (int));
		if (!a[i]) {
			return (int **) NULL; // Unable to allocate
		}
	}
	return a;
}

/** Make a 2D array of chars
 *
 * @param rows Number of rows
 * @param columns Number of columns
 * @return Pointer to the array of pointers to the rows.
 * 	  or null pointer if unable to allocate memory.
 * 	  Note: Will not free partially-allocated memory.
 *
 * @author Jonathan Dang
 */
char** make2Dchar(int rows, int columns) {

	char **a; // Array of pointers to rows

	a = (char **) malloc(rows * sizeof(char *));
	if (!a) {
		return (char **) NULL;
	}

	for (int i = 0; i < rows; i++) {
		a[i] = malloc(columns * sizeof (char));
		if (!a[i]) {
			return (char **) NULL;
		}
	}

	return a;
}

/** prints out the grid
 *
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxC Maximum number of columns gotten from reading the text file
 * @param grid The grid that is being printed out
 * @return nothing is returned. It just prints out the grid with 'x' and ' ' at the correct positions
 *
 * @author Jonathan Dang
 */
void printGrid(int maxR, int maxC, char** grid) {
	for (int r = 0; r < maxR; r++) {
		// loop invariant: at this point it is about to print all of the values within row r
		for (int c = 0; c < maxC; c++) {
			if (grid[r][c] == 'x') {
				printf("x");
			}
			else {
				printf("%c", grid[r][c]);
			}
		}
		// loop invariant: at this point all the columns within r (row) have been printed out
		printf("\n");
	}
	printf("\r");
}

/** centers out the grid
 *
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxCol Maximum number of columns gotten from reading the text file
 * @param row The current row
 * @param column THe current column
 * @param grid0 the initial grid that is not centered
 * @param grid1 the grid that is centered
 * @return the printed grid with 'x' and ' ' at the correct positions
 *
 * @author Jonathan Dang
 */
void centerGrid(int maxR, int maxCol, int row, int column, char** grid0, char **grid1) {

	for (int r = 0; r < maxR; r++) {
		for (int c = 0; c < maxCol; c++) {
			// loop invariant: at this point the position is within the grid and is adding blanks to the grid
			grid1[r][c] = ' ';
		}
	}

	// values used to center the grid
	int centR = ((maxR / 2) - (row / 2)); // this is used to center the row position
	int centC = ((maxCol / 2) - (column / 2)); // this is used to center the column position

	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++) {
			if ((grid0[r][c] == ' ') || (grid0[r][c] == 'x')) {
				// loop invariant: at this point the previous position has been centered
				grid1[r + centR][c + centC] = grid0[r][c];
			}
		}
		// loop invariant: at this point the column within the row has reached the end of grid
	}
}

/**
 * compares the two character arrays to see if they are the same
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxCol Maximum number of columns gotten from reading the text file
 * @param grid1 one of the char arrays being used to compare with
 * @param grid2 one of the char arrays being used to compare with
 * @return will return a 1 if the 2 char arrays are equaled or a 0 if not equaled
 *
 * @author Jonathan Dang
 */
int sameGrids(int maxR, int maxCol, char **grid1, char **grid2) {

	for (int i = 0; i < maxR; i++) {
		for (int j = 0; j < maxCol; j++) {
			//loop invariant: at this point the value of i is less than maxR and j is less than maxCol
			if (grid1[i][j] != grid2[i][j]) {
				return 0;
				//loop invariant: at this point the current position for both grids don't equal each other
			}
		}
	}
	return 1;
}


/**
 * tests to see if the current position of the array is within the array boundary
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxC Maximum number of columns gotten from reading the text file
 * @param currentR The current row position
 * @param currentC The current column position
 * @param grid is the grid that the currentR and currentC are based from
 * @return will return the value of outArray (a blank) if the position is outside the boundary
 * or will return the value at that position if the position is a valid cell
 *
 * @author Jonathan Dang
 */
char isCellValid(int maxR, int maxC, int currentR, int currentC, char **grid) {
	char outArray = ' ';

	// all these if statements are to test if the position is within the grid
	if (currentR < 0) {
		return outArray;
	}

	if (currentC < 0) {
		return outArray;
	}

	if (currentR >= maxR) {
		return outArray;
	}

	if (currentC >= maxC) {
		return outArray;
	}

	// would return this value if the current position is a valid cell
	return grid[currentR][currentC];
}

/**
 * detects the number of 'x' characters that surrounds the current position of the grid and
 * basically adds up the int values of the characters that surrounds the current position
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxC Maximum number of columns gotten from reading the text file
 * @param currentR The current row position
 * @param currentC The current column position
 * @param grid is the grid that the currentR and currentC are based from
 * @return will return the sum of the int values of the characters that surrounds the current position on the grid
 *
 * @author Jonathan Dang
 */
int getNeighbors(int maxR, int maxC, int currentR, int currentC, char **grid) {
	int value = 0;

	// checks the left hand side of the current position of the grid
	value += isCellValid(maxR, maxC, (currentR - 1), (currentC - 1), grid);
	value += isCellValid(maxR, maxC, (currentR), (currentC - 1), grid);
	value += isCellValid(maxR, maxC, (currentR + 1), (currentC - 1), grid);

	// checks the top and bottom of the current position of the grid
	value += isCellValid(maxR, maxC, (currentR - 1), (currentC), grid);
	value += isCellValid(maxR, maxC, (currentR + 1), (currentC), grid);

	// checks the right hand side of the current position of the grid
	value += isCellValid(maxR, maxC, (currentR - 1), (currentC + 1), grid);
	value += isCellValid(maxR, maxC, (currentR), (currentC + 1), grid);
	value += isCellValid(maxR, maxC, (currentR + 1), (currentC + 1), grid);

	// the int value that would represent how many 'x' or ' ' surrounds the current position
	return value;
}

/**
 * detects there are any 'x' characters (alive ones) within the array
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxC Maximum number of columns gotten from reading the text file
 * @param grid is the grid that the currentR and currentC are based from
 * @return will return a value of 1 if all the cells are dead (blank) and a 0 if there are
 * some live ones
 *
 * @author Jonathan Dang
 */
int allDeadCells(int maxR, int maxC, char **grid) {
	for (int r = 0; r < maxR; r++) {
		for (int c = 0; c < maxC; c++) {
			if (grid[r][c] == 'x') {
				return 0;
			}
		}
		// Loop Invariant: at this point, the current r has been completed
	}
	return 1;
}

