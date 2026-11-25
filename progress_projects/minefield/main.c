#include <stdio.h>
#include <stdbool.h>

#define BEGINNER_DIFF 1
#define INTERMEDIARY_DIFF 2
#define SPECIALIST_DIFF 3

#define BEGINNER_ROWS 9
#define BEGINNER_COLS 9
#define BEGINNER_MINES 10

#define INTERMEDIARY_ROWS 16
#define INTERMEDIARY_COLS 16
#define INTERMEDIARY_MINES 40

#define SPECIALIST_ROWS 16
#define SPECIALIST_COLS 25
#define SPECIALIST_MINES 84

#define CELL_HIDDEN '#'

void initialize_arrays(int rows, int cols, char board[rows][cols], bool is_mine[rows][cols]);

int main(void) {
	int difficulty = 2;
	int rows = 0;
	int cols = 0;
	int mines = 0;
	do {
		switch (difficulty) {
			case BEGINNER_DIFF:
				rows = BEGINNER_ROWS;
				cols = BEGINNER_COLS;
				mines = BEGINNER_MINES;
				break;
			case INTERMEDIARY_DIFF:
				rows = INTERMEDIARY_ROWS;
				cols = INTERMEDIARY_COLS;
				mines = INTERMEDIARY_MINES;
				break;
			case SPECIALIST_DIFF:
				rows = SPECIALIST_ROWS;
				cols = SPECIALIST_COLS;
				mines = SPECIALIST_MINES;
				break;
			default:
				printf("Invalid difficulty!\n");
		}
	} while (difficulty != BEGINNER_DIFF && difficulty != INTERMEDIARY_DIFF && difficulty != SPECIALIST_DIFF);

	char board[rows][cols];
	bool is_mine[rows][cols];
	initialize_arrays(rows, cols, board, is_mine);

	return 0;
}

void initialize_arrays(int rows, int cols, char board[rows][cols], bool is_mine[rows][cols]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = CELL_HIDDEN;
			is_mine[i][j] = false;
		}
	}
}
