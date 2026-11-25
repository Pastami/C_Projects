#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// Board-related macros
#define BOARD_SIDE_LENGTH 3
#define TOTAL_BOARD_LENGTH (BOARD_SIDE_LENGTH * BOARD_SIDE_LENGTH)

// Define the number of divisions in each direction of the board
#define BOARD_DIVISIONS (BOARD_SIDE_LENGTH - 1)

// Define the min and max indexes of the valid rows
#define ROW_MIN_INDEX 'A'
#define ROW_MAX_INDEX 'C'

// Define the min and max indexes of the valid columns
#define COL_MIN_INDEX '1'
#define COL_MAX_INDEX '3'

// Define the min and max digit characters, used to check whether
// the second character is a number, regardless of the valid columns
#define DIGIT_CHAR_MIN '0'
#define DIGIT_CHAR_MAX '9'

// Define the number of marks necessary to win the game
#define MARKS_TO_WIN BOARD_SIDE_LENGTH

// Define the character that replaces the characters in the winning line
#define WIN_LINE_CHAR '*'

int main(void) {
	printf("=======================\n");
	printf("      TIC-TAC-TOE      \n");
	printf("=======================\n");

	int x_wins = 0;
	int o_wins = 0;
	int draws = 0;

	bool play_again = false;

	do {
		// Initialize the two arrays
		char board[BOARD_SIDE_LENGTH][BOARD_SIDE_LENGTH];
		for (int i = 0; i < BOARD_SIDE_LENGTH; i++) {
			for (int j = 0; j < BOARD_SIDE_LENGTH; j++) {
				board[i][j] = ' ';
			}
		}
		bool is_move_blocked[BOARD_SIDE_LENGTH][BOARD_SIDE_LENGTH] = {{false}};

		// Store the last character read to check whether the newline
		// is still in the buffer
		char ch = 0;

		char first_turn;
		do {
			ch = 0;

			printf("Select the player who will start (X or O): ");

			// Skip blank spaces and store the first
			// non-blank or newline character in first_turn
			while (ch != '\n' && (ch = getchar()) == ' ') {
				;
			}

			first_turn = toupper((unsigned char) ch);

			// Skip all the remaining characters of the line
			while (ch != '\n') {
				ch = getchar();
			}

			if (first_turn == '\n') {
				printf("Invalid player: empty. Enter X or O.\n");
				continue;
			}

			if (first_turn != 'X' && first_turn != 'O') {
				printf("Invalid player: %c. Enter X or O.\n", first_turn);
				continue;
			}

		} while (first_turn != 'X' && first_turn != 'O');

		// Initialize the variable with a sentinel value,
		// indicating that a winner has not yet been found
		char winner = 0;
		char current_turn = first_turn;
		int move_counter = 0;
		for (;;) {
			putchar('\n');

			printf("   ");
			for (int i = 0; i < BOARD_SIDE_LENGTH; i++) {
				// Subtract DIGIT_CHAR_MIN from COL_MIN_INDEX and
				// then add i to match the number index
				printf(" %d  ", COL_MIN_INDEX - DIGIT_CHAR_MIN + i);
			}
			printf("\n\n");

			// Print the tic-tac-toe board
			for (int i = 0; i < BOARD_SIDE_LENGTH; i++) {
				printf("%c  ", ROW_MIN_INDEX + i);
				for (int j = 0; j < BOARD_SIDE_LENGTH; j++) {
					printf(" %c ", board[i][j]);

					// Print the vertical division between the columns
					if (j < BOARD_DIVISIONS) {
						putchar('|');
					}
				}
				putchar('\n');
				// Print the horizontal division between the rows
				if (i < BOARD_DIVISIONS) {
					printf("   ---+---+---\n");
				}
			}
			putchar('\n');

			// Win condition
			if (winner != 0) {
				break;
			}

			// Draw condition
			if (move_counter == TOTAL_BOARD_LENGTH) {
				break;
			}

			// Store the move in the row and col variables
			char row = 0;
			char col = 0;
			for (;;) {
				ch = 0;

				printf("\nPlayer %c, enter a square (for example, B2): ", current_turn);

				while (ch != '\n' && (ch = getchar()) == ' ') {
					;
				}
				row = toupper((unsigned char) ch);

				while (ch != '\n' && ((ch = getchar()) == ' ')) {
					;
				}
				col = ch;

				while (ch != '\n') {
					ch = getchar();
				}

				// ***START OF INPUT CHECK***
				// The tests are listed starting with the most common errors
				if (row == '\n') {
					printf("Invalid row: empty. Enter a letter between %c and %c.", ROW_MIN_INDEX, ROW_MAX_INDEX);

					// Skip the rest of the loop body and ask the same player again
					continue;
				}

				if (col == '\n') {
					printf("Invalid column: empty. Enter a number between %c and %c.", COL_MIN_INDEX, COL_MAX_INDEX);
					continue;
				}

				if (!isalpha((unsigned char) row)) {
					printf("Invalid row: %c. The first character must be a letter.", row);
					continue;
				}

				if (col < DIGIT_CHAR_MIN || col > DIGIT_CHAR_MAX) {
					printf("Invalid column: %c. The second character must be a number.", col);
					continue;
				}

				if (row < ROW_MIN_INDEX || row > ROW_MAX_INDEX) {
					printf("Invalid row: %c. Enter a letter between %c and %c.", row, ROW_MIN_INDEX, ROW_MAX_INDEX);
					continue;
				}

				if (col < COL_MIN_INDEX || col > COL_MAX_INDEX) {
					printf("Invalid column: %c. Enter a number between %c and %c.", col, COL_MIN_INDEX, COL_MAX_INDEX);
					continue;
				}

				if (is_move_blocked[row - ROW_MIN_INDEX][col - COL_MIN_INDEX]) {
					printf("%c%c is already taken.", row, col);
					continue;
				}
				// ***END OF INPUT CHECK***

				break;
			}

			// Subtract ROW_MIN_INDEX from row and COL_MIN_INDEX from col to
			// match the indexes in the array
			board[row - ROW_MIN_INDEX][col - COL_MIN_INDEX] = current_turn;
			is_move_blocked[row - ROW_MIN_INDEX][col - COL_MIN_INDEX] = true;
			move_counter++;

			// ***START OF WINNER SEARCH***
			int marks_counter = 0;

			// Search each row of the array to find the winner
			for (int i = 0; i < BOARD_SIDE_LENGTH; i++) {
				marks_counter = 0;
				for (int j = 0; j < BOARD_SIDE_LENGTH; j++) {
					if (board[i][j] == current_turn) {
						marks_counter++;
					}
				}

				// If marks_counter reaches MARKS_TO_WIN, assign the winner
				// and highlight the line
				if (marks_counter == MARKS_TO_WIN) {
					winner = current_turn;

					for (int k = 0; k < MARKS_TO_WIN; k++) {
						board[i][k] = WIN_LINE_CHAR;
					}

					break;
				}
			}

			// Skip the rest of the loop and print the board again,
			// replacing the winning line with WIN_LINE_CHAR
			if (winner != 0) {
				continue;
			}

			// Search each column of the array to find the winner
			for (int i = 0; i < BOARD_SIDE_LENGTH; i++) {
				marks_counter = 0;
				for (int j = 0; j < BOARD_SIDE_LENGTH; j++) {
					if (board[j][i] == current_turn) {
						marks_counter++;
					}
				}

				if (marks_counter == MARKS_TO_WIN) {
					winner = current_turn;

					for (int k = 0; k < MARKS_TO_WIN; k++) {
						board[k][i] = WIN_LINE_CHAR;
					}

					break;
				}
			}
			if (winner != 0) {
				continue;
			}

			marks_counter = 0;
			// Search the principal diagonal of the array to find the winner
			for (int i = 0, j = i; i < BOARD_SIDE_LENGTH && j < BOARD_SIDE_LENGTH; i++, j++) {
				if (board[i][j] == current_turn) {
					marks_counter++;
				}

				if (marks_counter == MARKS_TO_WIN) {
					winner = current_turn;

					for (int k = 0; k < MARKS_TO_WIN; k++) {
						board[k][k] = WIN_LINE_CHAR;
					}

					break;
				}
			}
			if (winner != 0) {
				continue;
			}

			marks_counter = 0;
			// Search the antidiagonal of the array to find the winner
			for (int i = 0, j = BOARD_SIDE_LENGTH - 1; i < BOARD_SIDE_LENGTH && j >= 0; i++, j--) {
				if (board[i][j] == current_turn) {
					marks_counter++;
				}

				if (marks_counter == MARKS_TO_WIN) {
					winner = current_turn;

					for (int k = 0, l = BOARD_SIDE_LENGTH - 1; k < MARKS_TO_WIN && l >= 0; k++, l--) {
						board[k][l] = WIN_LINE_CHAR;
					}

					break;
				}
			}
			if (winner != 0) {
				continue;
			}
			// ***END OF WINNER SEARCH***

			if (current_turn == 'X') {
				current_turn = 'O';
			} else {
				current_turn = 'X';
			}
		}

		if (winner != 0) {
			printf("THE WINNER IS %c!\n", winner);

			if (winner == 'X') {
				x_wins++;
			} else {
				o_wins++;
			}
		} else {
			printf("THE GAME ENDED IN A DRAW!\n");

			draws++;
		}

		printf("%c started the game.\n", first_turn);
		printf("The game lasted %d moves.\n", move_counter);

		char ch_play_again = 0;
		do {
			printf("\nPlay again (Y/N)? ");

			while ((ch = getchar()) == ' ') {
				;
			}

			ch_play_again = toupper((unsigned char) ch);

			if (ch_play_again == 'Y') {
				play_again = true;
			} else if (ch_play_again == 'N') {
				play_again = false;
			} else {
				printf("Enter Y to play again or N to stop.\n");
			}

			while (ch != '\n') {
				ch = getchar();
			}

		} while (ch_play_again != 'Y' && ch_play_again != 'N');
		putchar('\n');

	} while (play_again);

	printf("\nFINAL SCORE\n");
	printf("-----------\n");
	printf("X: %d win(s)\n", x_wins);
	printf("O: %d win(s)\n", o_wins);
	printf("Draw(s): %d\n", draws);

	return 0;
}
