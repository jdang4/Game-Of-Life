# Game-Of-Life

README for life.c by Jonathan Dang (1/29/2018)

My entire program was original.

Summary:
This program runs John Conway's Game of Life, which is played on a rectangular grid of cells, so that each cell has eight neighbors (adjacent cells). Each cell is either occupied by an organism or not. A pattern of occupied and unoccupied cells in the grid is called a generation. The program will terminate if the generation count is no longer less than the number of generation the user inputed into the command line, or if there are errors within the user's inputed values or if there are repeated patterns with the previous grid or the grid before the previous grid when comparing to the current grid.

During this assignment I did face some issues with dealing with the segmentation faults. This was mainly due to when I was checking the neighbors of the cells at the edge of the grid and from how I designed my program to check the neighboring cells it led to me checking outside the grid, thus giving me a segmentation fault.

How to Run Program:
To run this program the user must type in the file name, an integer value to represent the number of rows they want the grid to be, an integer value to represent the number of columns they want the grid to be, the text file they want to read from, an optional character of 'y' or 'n' that would specify if the user wants to be printing the grid of each generation, and an optional character of 'y' or 'n' that would allow the user to pause after a generation has been printing. If these 2 optional characters were excluded in the command line, the program should still work, it would just default them to being 'n'. It should end of looking like this:
"./life 60 60 100 blinker.txt y n" or "./life 60 60 100 blinker.txt" should still work.

Function Descriptions:

Main: This function is basically where the Game Of Life is being played on. In this function it will read the inputs from the text files, initalize the grid and center it and then go on to go through the generations, updating the grid in a way that matches with the rules of the Game of Life.

playOne: This function updates the board for one generation. It goes through each cell within the original grid and checks how many 'x' surrounding the current position of the cell on the original grid. Depending on that number of 'x' surrounding that index position, it will be filled in with a blank or an x and store that current position from the original grid onto the new grid.

make2Dchar: This function creates a 2D array of chars.

printGrid: This function is in charge of printing the grid out. It checks through each index position of the grid provided in its parameter and if sees an 'x' it will print out an "x" at that position of the array, else will print out the value at that position.

centerGrid: This function is in charge of centering the grid. It takes in an uncentered grid in its parameters and it will go through each position within that grid and center it. I was able to center it by first calulating the position that will be at the center of the grid for. Then I would go through each position within the array and if the position is equaled to either a blank or an x it will add the center values of the rows and columns to tha current position's row and column, but on the new grid and set it to the value of that same position from the uncentered grid. By doing this I was able to center the grid.

compareGrid: This function is designed to compare two character arrays. It goes through each elements for each grids and tests to see if they are not equaled to each other. If they ended up not equaling each other, this function should produce a false case, which in this case a 0, else will return a true case, a value of 1.

isCellValid: This function is basically used to help my program avoid getting a segmentation fault. It is designed so that it would take the current position and if that appears to have values that would appear outside of the array's boundary, it will return a blank, otherwise if the position is a valid cell, it will return that character value at that position.

getNeighbors: This function is in charge of detecting the number of 'x' characters that surrounds the current position of the grid. It basically adds up the int values of the characters that surrounds the current position and returns that sum. I would use that number to decide how many 'x' were detected.

allDeadCells: This function goes through the given char array and looks to see if there are any 'x' characters within the array. If it doesn't, that means that the entire grid is just blank and basically that would terminate the program because nothing would happen if the grid is blank. There wouldn't be any use of continuing on. It will return a value of 1 if all the cells are dead (blank) and a 0 if there are some live ones

Loop Invariants:

	In Main:
	   Loop Invariant: at this point the file has read the last actual character ('o' or 'x')
	   Loop Invariant: at this point, the current row has been printed out onto the grid
	   Loop Invariant: at this point the current there has been no conditions that would cause the program to terminate
           Loop Invariant: at this point, the grids have been updated

	In playOne:
	   Loop Invariant: at this point it will evaluate as long as r is less than the user given number of row
           Loop Invariant: at this point it will evaluate as long as c is less than the user given number of column

	In printGrid:
           Loop Invariant: at this point it is about to print all of the values within row r
	   Loop Invariant: at this point all the columns within r (row) have been printed out

	In centerGrid:
	   Loop Invariant: at this point the position is within the grid and is adding blanks to the grid
	   Loop Invariant: at this point the column within the row has reached the end of grid

	In sameGrids:
	   Loop Invariant: at this point the value of i is less than maxR and j is less than maxCol
	   Loop Invariant: at this point the current position for both grids don't equal each other

	In allDeadCells:
	   Loop Invariant: at this point, the current r has been completed

Test Case:
For my test case I used the acorn.txt
I used this command for my arguments: "./life 40 40 100 acorn.txt y y"
When I ran this test case I noticed that it seemed to be expanding, mainly stretching itself to the left side of the grid. The image also starts to divide from each other and this one was able to go all the way to the end of the generation without facing any errors or repetitive patterns.
