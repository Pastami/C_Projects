# Tic-Tac-Toe

An interactive command-line program for exploring the use of arrays. It is a game written entirely inside `main`, in C99, without functions or pointers. The game repeats until the user chooses not to continue.

Capstone project of Chapter 8, Arrays (K.N. King, C Programming: A Modern Approach).

## INPUT

| Input | Valid values |
|---|---|
| Starting player | X or O, either lowercase or uppercase |
| Square of the board | A letter, either lowercase or uppercase, followed by a number, from A1 to C3 |
| Play again? | Y or N, either lowercase or uppercase |

Invalid values are rejected with a message and requested again.

## OUTPUT

- At the start of the program: the `TIC-TAC-TOE` banner between two lines of `=`.
- Before each move: the board, with the column numbers `1` to `3` on top, the row letters `A` to `C` on the left, the marks separated by `|` and the rows separated by `---+---+---`.
- After an invalid entry: a message saying what is wrong, and the same prompt again.
- When a player wins: the board is printed again with the winning line replaced by `*` (the `WIN_LINE_CHAR` macro), followed by `THE WINNER IS X!` or `THE WINNER IS O!`.
- When the board is full and there is no winner: `THE GAME ENDED IN A DRAW!`.
- At the end of each game: `X started the game.` (or `O`) and `The game lasted N moves.`
- When the user chooses not to play again: `FINAL SCORE`, with the number of wins of `X`, the number of wins of `O` and the number of draws.

## CONCEPTS PUT INTO PRACTICE

- Two-dimensional arrays: `char` for the state of the board and `bool` for the occupied squares.
- Array initialization with nested loops and with an initializer (`{{false}}`).
- Array subscripts computed from `char` values, such as `row - ROW_MIN_INDEX`.
- Nested loops.
- `do`, `while` and `for (;;)` loops, with `break` and `continue`.
- Constants with calculations defined with `#define`.
- Sentinel value: `winner` is `0` until a winner is found.
- Character arithmetic.
- Input read character by character with `getchar`, skipping blank spaces and discarding the rest of the line.
- `toupper` and `isalpha` with `<ctype.h>`, and casts to `unsigned char`.
- `bool` with `<stdbool.h>`.

## HOW TO COMPILE AND RUN

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o tic_tac_toe
./tic_tac_toe
```

## EXAMPLE RUN

The session below shows a game won by X in 5 moves, with one invalid entry from O.

```text
$ ./tic_tac_toe
=======================
      TIC-TAC-TOE      
=======================
Select the player who will start (X or O): x

    1   2   3  

A     |   |   
   ---+---+---
B     |   |   
   ---+---+---
C     |   |   


Player X, enter a square (for example, B2): A1

    1   2   3  

A   X |   |   
   ---+---+---
B     |   |   
   ---+---+---
C     |   |   


Player O, enter a square (for example, B2): D1
Invalid row: D. Enter a letter between A and C.
Player O, enter a square (for example, B2): B1

    1   2   3  

A   X |   |   
   ---+---+---
B   O |   |   
   ---+---+---
C     |   |   


Player X, enter a square (for example, B2): A2

    1   2   3  

A   X | X |   
   ---+---+---
B   O |   |   
   ---+---+---
C     |   |   


Player O, enter a square (for example, B2): B2

    1   2   3  

A   X | X |   
   ---+---+---
B   O | O |   
   ---+---+---
C     |   |   


Player X, enter a square (for example, B2): A3

    1   2   3  

A   * | * | * 
   ---+---+---
B   O | O |   
   ---+---+---
C     |   |   

THE WINNER IS X!
X started the game.
The game lasted 5 moves.

Play again (Y/N)? n


FINAL SCORE
-----------
X: 1 win(s)
O: 0 win(s)
Draw(s): 0
```

## KNOWN LIMITATIONS

The program was written and tested on x86-64, GCC, Linux.

- **Fixed players.** `X` and `O` are written directly in the code: in the input check, in the turn change, in the score and in the messages. Adding a third player requires changing all of these places.
- **Winning line equal to the board side.** `MARKS_TO_WIN` is equal to `BOARD_SIDE_LENGTH`, so a win requires a complete row, column or diagonal. The counter sums all the marks of the current player in the line instead of counting consecutive marks, so changing only `MARKS_TO_WIN` does not give an "N in a row" rule.
- **Board size not fully configurable.** The horizontal division text `---+---+---` and the macros `ROW_MAX_INDEX` and `COL_MAX_INDEX` do not follow `BOARD_SIDE_LENGTH`. If the side changes, they must be adjusted by hand. Otherwise, the board is misaligned and the program accepts or rejects the wrong squares (on a smaller board, it could access positions outside the arrays).
- **Only one winning line highlighted.** When a move completes two lines at once, the program searches the rows, then the columns, then the principal diagonal and then the antidiagonal, and stops at the first line found. Only that line is replaced by `WIN_LINE_CHAR`, and the other keeps its marks. The winner shown is still correct.
- **Non-ASCII characters.** `getchar` reads byte by byte. A character such as `ç` in UTF-8 takes 2 bytes, so the error message shows only its first byte, which appears as a broken character.
- **Repeated input reading.** The code that skips blank spaces, stores the character and discards the rest of the line appears in three places: the starting player, the move and the play-again answer. The program has no functions to share it.