#include <stdio.h>
#include <stdlib.h>
#include "board.h"

char** create_empty_board(BOARD* userBoard) {
	char blankChar = '*';
	userBoard->board = (char**) malloc(userBoard->numRows * sizeof(char*));
	for(int curRow = 0; curRow < userBoard->numRows; ++curRow) {
		userBoard->board[curRow] = (char*) malloc(userBoard->numCols * sizeof(char));
		for (int curCol = 0; curCol < userBoard->numCols; ++curCol) {
			userBoard->board[curRow][curCol] = blankChar;
		}
	}
	return userBoard->board;
}

void print_board(BOARD* userBoard) {
	for(int i = 0; i < userBoard->numRows; ++i) {
        printf("%d ", userBoard->numRows - i -1);
        for(int j = 0; j < userBoard->numCols; ++j) {
            printf("%c ", userBoard->board[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for(int i = 0; i < userBoard->numCols; ++i){
        printf("%d ", i);
    }
    printf("\n");
	getUserInput(userBoard);
}

void write_funct(BOARD* userBoard, int startRow, int startCol, int endRow, int endCol) {

	int rowDist = endRow - startRow;
	int colDist = endCol - startCol;
	char paintSymbol = paintChar(rowDist, colDist);

	int j = startCol;
	if (paintSymbol == '/') {
		
		if (startRow < endRow) {
			// left to right
			for (int i = startRow; i <= endRow || j <= endCol; ++i, ++j) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		} else {
			// right to left
			for (int i = startRow; i >= endRow || j >= endCol; --i, --j) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		}


	} else if (paintSymbol == '-') {
		if (startCol < endCol) {
			// left to right
			for (int i = startRow; j <= endCol; ++j) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		} else {
			// right to left
			for (int i = startRow; j >= endCol; --j) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		}
	} else if (paintSymbol == '|') {
		if (startRow < endRow) {
			// bottom to top
			for (int i = startRow; i <= endRow; ++i) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		} else {
			// top to bottom
			for (int i = startRow; i >= endRow; --i) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		}
	} else if (paintSymbol == '\\') {
		if (startRow > endRow) {
			// left to right
			for (int i = startRow; i >= endRow || j <= endCol; --i, ++j) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		} else {
			// right to left
			for (int i = startRow; i <= endRow || j >= endCol; ++i, --j) {
				if ((userBoard->board[userBoard->numRows - i -1][j] == '*') || (userBoard->board[userBoard->numRows - i -1][j] == paintSymbol)) {
					userBoard->board[userBoard->numRows - i -1][j] = paintSymbol;
				} else {
					userBoard->board[userBoard->numRows - i -1][j] = '+';
				}
			}
		}
	}
	
	//  else if (paintSymbol == '\\') {
	// 	9 0 0 9
	// 	0 0 0 9
	// }
	print_board(userBoard);
}

void erase_funct(BOARD* userBoard, int row, int col) {
	char blankChar = '*';
	userBoard->board[userBoard->numRows - row -1][col] = blankChar;
	print_board(userBoard);
}

int paintChar (int rowDistance, int ColumnDistance) {
	char lineChar;
	// if row and col distance have the same signs: / 
	// if row and col distance have oppo signs: "\"

	if (ColumnDistance == 0) {
		// horizontal line
		lineChar = '|';
	} else if (rowDistance == 0) {
		// vertical line
		lineChar = '-';
	} else if (rowDistance > 0 && ColumnDistance > 0) {
		lineChar = '/';
	} else if (rowDistance < 0 && ColumnDistance < 0) {
		lineChar = '/';
	} else if (rowDistance < 0 && ColumnDistance > 0) {
		lineChar = '\\';
	} else {
		lineChar = '\\';
	}
	return lineChar;
}

bool isLineStraight(int startRow, int startCol, int endRow, int endCol) {
	// if slope of line is 0, -1, 1, inf? -> return true
	double slope;
	slope = (double)(endCol - startCol) / (endRow - startRow);
	slope = abs(slope);

	if (slope == 1 || slope == 0 || slope == INT_MIN) {
		return true;
	}
	return false;
}

int getUserInput (BOARD* userBoard) {
	// scanf(" %s", string2);
	// if (strlen(string2) == 1){
	// 	if (string2[0] == 'h'){
	// 		print_help();
	// 		print_board(userBoard);
	// 	}
	// }


	// char commandWanted;
    int int1, int2, int3, int4;
	char fileName;
	char string1[100];
    char commandWanted[300];

	printf("Enter your command: ");
	
	scanf(" %s", commandWanted);
    if (strlen(commandWanted) > 1) {
        printf("Unrecognized command. Type h for help.\n");
		getUserInput(userBoard);
    }
    // char comWant = commandWanted[0];
	switch(commandWanted[0]) {
		case 'q':
            quit_funct(userBoard);
			break;
		case 'h':
			print_help();
			print_board(userBoard);
			break;
		case 'w':
    		scanf("%d %d %d %d", &int1, &int2, &int3, &int4);
			// checkValidInput(int1, int2, int3, int4, userBoard);
			if ((int2 >= userBoard->numCols) || int4 >= userBoard->numCols) {
				printf("Improper draw command.\n");
				print_board(userBoard);
			} else if ((int1 >= userBoard->numRows) || int3 >= userBoard->numRows) {
				printf("Improper draw command.\n");
				print_board(userBoard);
			} else if ((int1 < 0) || (int2 < 0) || (int3 < 0) || (int4 < 0)) {
				printf("Improper draw command.\n");
				print_board(userBoard);
			} else if (isLineStraight(int1, int2, int3, int4) == false) {
                printf("Cannot draw the line as it is not straight.\n");
                print_board(userBoard);
            } else{
			write_funct(userBoard, int1, int2, int3, int4);
            }
			break;
		case 'e':
			scanf("%d %d", &int1, &int2);
			if ((int1 >= userBoard->numRows) || int2 >= userBoard->numCols) {
				printf("Improper erase command.\n");
				print_board(userBoard);
			} else if ((int1 < 0) || int2 < 0) {
				// too small
				printf("Improper erase command.\n");
				print_board(userBoard);
			}
			erase_funct(userBoard, int1, int2);
			break;
		case 'r':
			scanf("%d %d", &int1, &int2);
			if (int1 < 1 || int2 < 1) {
				printf("Improper resize command.\n");
				print_board(userBoard);
			}
			resize_funct(userBoard, int1, int2);
			break;
		case 'a':
			scanf(" %s %d", string1, &int1);
			
			if (strlen(string1) == 1) {
				if (string1[0] == 'r') {
					if (int1 > userBoard->numRows || int1 < 0) {
						printf("Improper add command.\n");
						print_board(userBoard);
					} else {
						add_funct(userBoard, string1[0], int1);
					}
				} else if (string1[0] == 'c') {
					if(int1 > userBoard->numCols || int1 < 0) {
						printf("Improper add command.\n");
						print_board(userBoard);
					} else {
						add_funct(userBoard, string1[0], int1);
					}
				} else {
					printf("Improper add command.\n");
					print_board(userBoard);
				} 
			} else {
				printf("Improper add command.\n");
				print_board(userBoard);
			}
			break;
		case 'd':
			scanf(" %s %d", string1, &int1);
			if (strlen(string1) == 1) {
				if (string1[0] == 'r') {
					if (int1 >= userBoard->numRows || int1 < 0) {
						printf("Improper delete command.\n");
						print_board(userBoard);
					} else {
						delete_funct(userBoard, string1[0], int1);
					}
				} else if (string1[0] == 'c') {
					if(int1 >= userBoard->numCols || int1 < 0) {
						printf("Improper delete command.\n");
						print_board(userBoard);
					} else {
						delete_funct(userBoard, string1[0], int1);
					}
				} else {
					printf("Improper delete command.\n");
					print_board(userBoard);
				}
			} else {
				printf("Improper delete command.\n");
				print_board(userBoard);
			}
			break;
		case 's':
			scanf(" %s", &fileName);
			save_funct(userBoard, &fileName);
			break;
		case 'l':
			scanf(" %s", &fileName);
			load_funct(userBoard, &fileName);
			break;
		default:
			printf("Unrecognized command. Type h for help.\n");
			getUserInput(userBoard);			
			break;
	}
	return 0;
}

void save_funct(BOARD* userBoard, char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Failed to open file: %s\n", fileName);
		print_board(userBoard);
	}
	// first line includes numRows & numCols (for when person wants to load file)
	fprintf(fp, "%d %d\n", userBoard->numRows, userBoard->numCols);

	// file print rest of board to .txt file
	for(int i = 0; i < userBoard->numRows; ++i) {
        fprintf(fp, "%d ", userBoard->numRows - i -1);
        for(int j = 0; j < userBoard->numCols; ++j) {
            fprintf(fp, "%c ", userBoard->board[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "  ");
    for(int i = 0; i < userBoard->numCols; ++i){
        fprintf(fp, "%d ", i);
    }
    fprintf(fp, "\n");

	fclose(fp);
	print_board(userBoard);
}

void load_funct(BOARD* userBoard, char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Failed to open file: %s\n", fileName);
		print_board(userBoard);
	}
	// get # of rows and # cols from first line
	fscanf(fp, "%d %d\n", &userBoard->numRows, &userBoard->numCols);

	for(int i = 0; i < userBoard->numRows; ++i) {
        fscanf(fp, "%d ", &userBoard->numRows - i -1);
		printf("%d ", userBoard->numRows - i -1);
        for(int j = 0; j < userBoard->numCols; ++j) {
            fscanf(fp, "%c ", &userBoard->board[i][j]);
			printf("%c ", userBoard->board[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for(int i = 0; i < userBoard->numCols; ++i){
        fscanf(fp, "%d ", &i);
		printf("%d ", i);
    }
    printf("\n");

	fclose(fp);
	getUserInput(userBoard);

}

void quit_funct(BOARD* userBoard) {
	
	for (int row = 0; row < userBoard->numRows; ++row) {
		free(userBoard->board[row]);
	}
	free(userBoard->board);
	userBoard->board = NULL;
	exit(0);
}

void print_help() {

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

void resize_funct(BOARD* userBoard, int newRow, int newCol) {
	BOARD newBoard; // create a new board
	int rowDiff;
	int curRows = userBoard->numRows;
	int curCols = userBoard->numCols;
	newBoard.numRows = curRows; // set the size of it to numRow X numCol
	newBoard.numCols = curCols;
	create_empty_board(&newBoard);
	
	for (int i = 0; i < curRows; ++i){
	    for (int j = 0; j < curCols; ++j){
	        newBoard.board[i][j] = userBoard->board[i][j];
	    }
	}
	
	// first we do upsize
	if (newRow >= userBoard->numRows) {
	    rowDiff = newRow - userBoard->numRows;
	    userBoard->board = (char**)realloc(userBoard->board, newRow * sizeof(char*));
	    for (int i = userBoard->numRows; i < newRow; ++i){
	        userBoard->board[i] = (char*)malloc(newCol * sizeof(char));
	    }
	    
	    
	    for (int i = 0; i < newRow; ++i){
	        for (int j = 0; j < newCol; ++j){
	            userBoard->board[i][j] = '*';
	        }
	    }
	    
	    userBoard->numRows = newRow;
	    userBoard->numCols = newCol;
	    
	    for (int i = 0; i < curRows; ++i){
	        for (int j = 0; j < curCols; ++j){
	            userBoard->board[i + rowDiff][j] = newBoard.board[i][j];
	        }
	    }
	    
	    for(int i = 0; i < newBoard.numRows; ++i){
	        free(newBoard.board[i]);
	    }
	    free(newBoard.board);
	} else if (newRow < userBoard->numRows) { //then the downsize case
	    rowDiff = curRows - newRow;
	    userBoard->numRows = newRow;
	    userBoard->numCols = newCol;
	    
	    userBoard->board = (char**)realloc(userBoard->board, newRow * sizeof(char*));
	    for (int i = 0; i < newRow; ++i){
	        userBoard->board[i]= (char*)realloc(userBoard->board[i], newCol * sizeof(char));
	    }
	    
	    for (int i = 0; i < newRow; ++i){
	        for (int j = 0; j < newCol; ++j){
	            userBoard->board[i][j] = '*';
	        }
	    }
	    
	    for (int i = 0; i < newRow; ++i){
	        for (int j = 0; j < curCols; ++j){
	            userBoard->board[i][j] = newBoard.board[i + rowDiff][j];
	        }
	    }
	    
	    for (int i = 0; i < newBoard.numRows; ++i){
	        free(newBoard.board[i]);
	    }
	    free(newBoard.board);
	}
	
	print_board(userBoard);
	
	
	
// 	if (newRow <= userBoard->numRows) {
	    
// 	}

	// if(userBoard->numRows >= newRow){
	// 	curRows = newRow;
	// } else {
	// 	curRows = userBoard->numRows;
	// }

	// if(userBoard->numCols >= newCol){
	// 	curCols = newCol;
	// } else {
	// 	curCols = userBoard->numCols;
	// }

	// for (int i = 0; i < curRows; ++i){
	// 	for (int j = 0; j < curCols; ++j){
	// 		newBoard.board[i][j] = userBoard->board[i][j];
	// 	}
	// }
	// print_board(&newBoard);
	//after print the newBoard to user, we actually want to replace the old one with the new one
// 	int rowsToChange = abs(newRow - userBoard->numRows);
// 	int colsToChange = abs(newCol - userBoard->numCols);
// 	if(newRow >= userBoard->numRows){ // allocate more space if new row is greater than old one
// 		userBoard->board = (char**) realloc(userBoard->board, rowsToChange * sizeof(char*)); // allocate more space for rows
// 		for (int i = userBoard->numRows; i < newRow; ++i){ //for loop to allocate space for cols
// 			if(newCol >= userBoard->numCols){ // if new cols is greater than old one
// 				userBoard->board[i] = (char*)realloc(userBoard->board[i], colsToChange * sizeof(char)); // allocate more space for cols
// 				for(int j = userBoard->numCols; j < newCol; ++j){
// 					userBoard->board[i][j] = '*'; // fill those new space with star
// 				}
// 			} else if (newCol < userBoard->numCols) { // the case that new cols is less than old
// 					for(int j = newCol; j < userBoard->numCols; ++j){
// 						userBoard->board[i][j] = '*';
// 					}
// 				}
// 			}

// 	} else if (newRow < userBoard->numRows){ // the case that new rows is less than old
// 				for(int i = 0; i < newRow; ++i) {
// 					if (newCol >= userBoard->numCols){ // the case that new cols are greater than old
// 						for(int j = userBoard->numCols; j < newCol; ++j){
// 							userBoard->board[i] = (char*)realloc(userBoard->board[i], colsToChange * sizeof(char)); // allocate space for each row
// 							userBoard->board[i][j] = '*'; // fill those space with star
// 						}
// 					}
// 				}
// 				for(int i = newRow; i < userBoard->numRows; ++i){
// 					free(userBoard->board[i]);
// 				}
// 			}
// 	print_board(userBoard);
    
}

void add_funct(BOARD* userBoard, char char1, int num) {
	
	if (char1 == 'r') {
		// allocating mem for one more row, and n # of cols for that one row
		++userBoard->numRows;

		userBoard->board = (char**) realloc (userBoard->board, userBoard->numRows * sizeof(char*));
		userBoard->board[userBoard->numRows-1] = (char*) malloc(userBoard->numCols * sizeof(char));
		
	// // userBoard->numRows = 4

		for (int i = 0; i < userBoard->numCols; ++i) {
			userBoard->board[userBoard->numRows-1][i] = '*';
		}
    
		for (int curRow = userBoard->numRows-2; curRow >= userBoard->numRows - num - 1; --curRow) {
			for (int curCol = 0; curCol < userBoard->numCols; ++curCol){
				userBoard->board[curRow+1][curCol] = userBoard->board[curRow][curCol];
			}
		}
        
		for (int i = 0; i < userBoard->numCols; ++i){
			userBoard->board[userBoard->numRows - num - 1][i] = '*';
		}
	 } else {
		++userBoard->numCols; 

        int j = userBoard->numCols-1;
        for (int i = 0; i < userBoard->numRows; ++i) {
            // add 1 more col to end of each row (right side)
            userBoard->board[i] = (char*) realloc (userBoard->board[i], userBoard->numCols * sizeof(char));
            // initialize each one of those spaces with blank char *
            userBoard->board[i][j] = '*';
        }

        for (int curRow = 0; curRow < userBoard->numRows; ++curRow) {
            for (int curCol = userBoard->numCols-2; curCol >= num; --curCol) {
                userBoard->board[curRow][curCol+1] = userBoard->board[curRow][curCol];
            }
        }       

        for (int i = 0; i < userBoard->numRows; ++i) {
            userBoard->board[i][num] = '*';
        }

	}
	print_board(userBoard);		
}

void delete_funct(BOARD* userBoard, char char1, int num) {
    if (char1 == 'r') {
        // start at row below the row you wanna del, cont until at bottom of board
        for (int curRow = userBoard->numRows - num; curRow < userBoard->numRows; ++curRow) {
            for(int curCol = 0; curCol < userBoard->numCols; ++curCol) {
                userBoard->board[curRow-1][curCol] = userBoard->board[curRow][curCol];
            }
        }
        // free bottom row
        free(userBoard->board[userBoard->numRows-1]);
        --(userBoard->numRows);   
	} else {
        // start at 1 column after col u wanna del, continue until at end of row
        for (int curRow = 0; curRow < userBoard->numRows; ++curRow) {
            for(int curCol = num + 1; curCol < userBoard->numCols; ++curCol) {
                userBoard->board[curRow][curCol-1] = userBoard->board[curRow][curCol];
            }
        }
        // for (int curRow = 0; curRow < userBoard->numRows; ++curRow) {
            // free last col in each row
            // free(userBoard->board[curRow][userBoard->numCols-1]);
        // }
        --(userBoard->numCols);
    }
    
    
    
    print_board(userBoard);

}
