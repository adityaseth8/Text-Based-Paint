#ifndef BOARD_H
	#define BOARD_H
		typedef struct board_struct {
		int numRows, numCols;
		char** board;
	}BOARD;
	#include <string.h>
	#include <stdbool.h>
	#include <limits.h>
	char** create_empty_board(BOARD* userBoard);
	void print_board(BOARD* userBoard);
	void write_funct(BOARD* userBoard, int startRow, int startCol, int endRow, int endCol);
	int paintChar (int rowDistance, int ColumnDistance);
	int getUserInput (BOARD* userBoard);
	void print_help();
	void erase_funct(BOARD* userBoard, int row, int col);
	void quit_funct(BOARD* userBoard);
	void resize_funct(BOARD* userBoard, int newRow, int newCol);
	void save_funct(BOARD* userBoard, char* fileName);
	void load_funct(BOARD* userBoard, char* fileName);
	void add_funct(BOARD* userBoard, char char1, int num);
	void delete_funct(BOARD* userBoard, char char1, int num);
	bool isLineStraight(int startRow, int startCol, int endRow, int endCol);
#endif




