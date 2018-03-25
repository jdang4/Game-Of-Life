/* Game of Life
*/

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"
void playOne(int maxR, int maxCol, unsigned int x, unsigned int y, char **old, char **new);



/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 *
 * @author Jonathan Dang
 */


int main(int argc, char **argv) {
	printf("\nGame of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input; // Stream descriptor for file containing initial grid
	int rows; // Number of rows in the grid
	int columns; // Number of columns in the grid
	int gens; // Number of generations to produce
	int doPrint; // 1 if user wants to print each generation, 0 if not
	int doPause; // 1 if user wants to pause after each generation, 0 if not
	char **inital;
	char **gridA; // A 2D array to hold the pattern
	char **gridB;
	char **gridC;
	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	/* Save the command-line arguments.
	   Also need to check if print and/or pause arguments were entered,
	   and if so, what they were.
	   A switch statement might be handy here.
	*/
	rows = atoi(argv[1]); // Convert from character string to integer.
	columns = atoi(argv[2]); // Convert from character string to integer.
	gens = atoi(argv[3]); // Convert from character string to integer.
	inputFileName = argv[4]; // Convert from character string to integer.

	if (argc > 5) {
		if (*argv[5] == 'y') {
			doPrint = 1;
		}
	}

	else {
		doPrint = 0;
	}

	if (argc > 6) {
		if (*argv[6] == 'y') {
			doPause = 1;
		}
	}
	else {
		doPause = 0;
	}

	// gens has to be at least 1
	if (gens <= 0) {
		printf("Gens needs to be larger than 0\n");
		exit(0);
	}
	/* Here is how you would allocate an array to hold the grid.
	*/
	// allocating 3 arrays, each being large enough to hold one generation
	inital = make2Dchar(rows, columns);
	gridA = make2Dchar(rows, columns);
	gridB = make2Dchar(rows, columns);
	gridC = make2Dchar(rows, columns);

	// You should check that it succeeded.

	// these checks to see if the memory was successfully allocated for the arrays
	if (gridA == (char **) NULL) {
		printf("Unable to allocate the array\n");
	}

	if (gridB == (char **) NULL) {
		printf("Unable to allocate the array");
		return EXIT_FAILURE;
	}

	if (gridC == (char **) NULL) {
		printf("Unable to allocate the array");
		return EXIT_FAILURE;
	}



	/* Eventually, need to try to open the input file.
	*/
	input = fopen(inputFileName, "r");
	if (!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}

	/*Once opened, you can read from the file one character at a time with fgetc().
	 * You can read one line at a time using fgets().
	 * You can read from standard input (the keyboard) with getchar().
	*/

	int numOfRow = 0;  // holds the maximum number of rows in the text file
	int numOfCol = 0;  // records the number of columns for each row in the file
	int maxCol = 0;    // holds the maximum number of columns in the text file
	char c;

	// finds the maximum number of characters in the file
	// also determines the number of lines within it
	while ((c = fgetc(input)) != EOF) {
		if (c != '\n' || c != ' ') {
			numOfCol++;
		}

		if (c == '\n') {
			numOfRow++;
			if (numOfCol > maxCol) {
				maxCol = numOfCol;
			}
			numOfCol = 0;
		}
	}

	// this handles the situation if the user's inputed values of rows and columns will not create
	// a large enough grid
	if ((rows * columns) < ((numOfRow * maxCol))) {
		printf("There was an error with your size of grid\n");
		exit(0);
	}

	rewind(input);

	// adds in the characters into the initial grid
	for (int r = 0; r < numOfRow; r++) {
		for (int co = 0; co < maxCol; co++) {
			char c1 = fgetc(input);
			if (c1 == '\n') {
				// Loop Invariant: at this point the file has read the last actual character ('o' or 'x')
				for (int k = co; k < maxCol; k++) {
					inital[r][k] = ' ';
					co++;
				}

			}
			else if (c1 == 'o') {
				inital[r][co] = ' ';
			}
			else if (c1 == 'x'){
				inital[r][co] = 'x';
			}
		}
		// Loop Invariant: at this point, the current row has been printed out onto the grid
	}

	// this centers gridA
	centerGrid(rows, columns, numOfRow, maxCol, inital, gridA);

	int gen; // keeps track of the current generation

	// prints the initial grid before running the playOne function
	printf("\nThe grid of the initial generation before starting Game of Life:\n\n");
	printGrid(rows, columns, gridA);


	for (gen = 1; gen < gens; gen++) {

		if (allDeadCells(rows, columns, gridA)) {
			printf("The grid was blank so program terminated\n");
			printf("The grid of the last generation before termination:\n\n");
			printGrid(rows, columns, gridC); // reprints the last grid before termination
			exit(0);
		}

		if (sameGrids(rows, columns, gridA, gridB) ||
			(sameGrids(rows, columns, gridA, gridC))) {
			printf("There was a pattern that repeated so program terminated\n");
			printf("The grid of the last generation before termination:\n\n");
			printGrid(rows, columns, gridC); // reprints the last grid before termination
			exit(0);
		}

		printf("Generation %d\n", gen);

		if (doPrint) {
			printGrid(rows, columns, gridA);
		}
		// Loop Invariant: at this point the current there has been no conditions that would cause the program to terminate
		playOne(rows, columns, numOfRow, maxCol, gridA, gridB);
		char **temp = gridC;
		gridC = gridA;
		gridA = gridB;
		gridB = temp;
		// Loop Invariant: at this point, the grids have been updated

		if (doPause) {
			getchar();
		}
	}

	printf("The grid of the last generation before termination:\n\n");
	printGrid(rows, columns, gridC); // reprints the last grid before termination

	//frees up the board that those arrays had allocated them
	free(gridA);
	free(gridB);
	free(gridC);



return EXIT_SUCCESS;

}

/**
 * plays one generation of the game of life
 * @param maxR Maximum number of rows gotten from reading the text file
 * @param maxCol Maximum number of columns gotten from reading the text file
 * @param row The current row
 * @param column THe current column
 * @param old the char array of the the original array before game is played
 * @param new the updated char array
 * @return returns nothing, but it does update the grid
 *
 * @author Jonathan Dang
 */
void playOne(int maxR, int maxCol, unsigned int row, unsigned int column, char **old, char **new) {
	for (int r = 0; r < maxR; r++) {
		// Loop Invariant: at this point it will evaluate as long as r is less than the user given number of row
		for (int c = 0; c < maxCol; c++) {
			// Loop Invariant: at this point it will evaluate as long as c is less than the user given number of column
			int sum = getNeighbors(maxR, maxCol, r, c, old);
			if (sum < 432 || sum > 520) {  // 432 is equivalent of there being 2 'x' that surrounds the current cell
				                           // 520 is equivalent of there being 3 'x' that surrounds the current cell
				new[r][c] = ' ';
			}

			else if (sum == 520) {
				new[r][c] = 'x';
			}
			else if (sum == 432){
				new[r][c] = old[r][c];
			}
		}
	}


}
