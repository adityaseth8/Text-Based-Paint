#include <stdio.h>
#include <stdlib.h>
#include "board.h"	
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// typedef enum {
// 	q = 113,
// 	h = 104,
// 	w = 119
// 	// i think 119 is ascii 
// }option;
BOARD* inputValid (int argc, char** argv, BOARD* userBoard);
bool isInteger (char* userInput);

int main(int argc, char** argv) {
	BOARD userBoard;
	inputValid(argc, argv, &userBoard);
	create_empty_board(&userBoard);
	print_board(&userBoard);

	return 0;
}

BOARD* inputValid (int argc, char** argv, BOARD* userBoard) {
	int rowUserInput;
	int colUserInput;
	if (argc == 3) {
		sscanf(argv[1], "%d", &rowUserInput);
		sscanf(argv[2], "%d", &colUserInput);

		if (isInteger(argv[2]) == false) {
				printf("The number of columns is not an integer.\n");
				printf("Making default board of 10 X 10.\n");
			userBoard->numRows = 10;
			userBoard->numCols = 10;
			} else if (isInteger(argv[1]) == false) {
				printf("The number of rows is not an integer.\n");
				printf("Making default board of 10 X 10.\n");
			userBoard->numRows = 10;
			userBoard->numCols = 10;
			} else if (colUserInput < 1) {
				printf("The number of columns is less than 1.\n");
				printf("Making default board of 10 X 10.\n");
			userBoard->numRows = 10;
			userBoard->numCols = 10;
			} else if (rowUserInput < 1) {
				printf("The number of rows is less than 1.\n");
				printf("Making default board of 10 X 10.\n");
			userBoard->numRows = 10;
			userBoard->numCols = 10;
			} else if ((rowUserInput >= 1) && (colUserInput >= 1)) {
			userBoard->numRows = rowUserInput;
			userBoard->numCols = colUserInput;
			}
	} else if (argc == 1) {
		userBoard->numRows = 10;
		userBoard->numCols = 10;
	} else {
		printf("Wrong number of command line arguements entered.\n");
		printf("Usage: ./paint.out [num_rows num_cols]\n");
		printf("Making default board of 10 X 10.\n");
		userBoard->numRows = 10;
		userBoard->numCols = 10;
	}
	return userBoard;
}

bool isInteger (char* userInput) {
	// int length = strlen(userInput);
	if ((userInput[0] == '-')) {
		for (int i = 1; userInput[i] != '\0'; ++i){
		
		if (isdigit(userInput[i])) {
			continue;
		} else {
			return false;
			}
		}
	}else if (userInput[0] != '-'){
		for (int i = 0; userInput[i] != '\0'; ++i){
		
		if (isdigit(userInput[i])) {
			continue;
		} else {
			return false;
			}
		}
	}
return true;
}
	
// "4wasd" userInput[0] "4"
