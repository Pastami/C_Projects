# Numeric Lab

A menu-driven console program with seven small numeric exercises built around loops: primes up to N, GCD and LCM, Fibonacci sequence, approximation of *e*, grade statistics, drawings and Pythagorean triples. The menu repeats until the user chooses to exit, and the program reports how many operations were performed.

Capstone project of Chapter 6, *Loops* (K.N. King, *C Programming: A Modern Approach*).

## INPUT

| Menu option | Input | Valid values |
|---|---|---|
| 1 - Primes up to N | `N` | integer, `N >= 2` |
| 2 - GCD and LCM | two integers | each from 1 to 10000 |
| 3 - Fibonacci sequence | `N` | integer from 1 to 40 |
| 4 - Approximate e | `ε` (epsilon) | `float`, `ε > 0` |
| 5 - Grade statistics | grades, one at a time | integers from 0 to 100, `-1` to stop |
| 6 - Drawings | triangle height, then table size | 1 to 15, then 1 to 12 |
| 7 - Pythagorean triple | perimeter | integer from 1 to 500 |
| 0 - Exit | none | |

Invalid values are rejected and asked again.

## OUTPUT

- **Option 1:** the prime numbers up to `N`, five per line and aligned in columns, and the total of primes found.
- **Option 2:** the GCD (Euclidean algorithm) and the LCM of the two numbers.
- **Option 3:** the first `N` Fibonacci numbers (`F1`, `F2`, ...).
- **Option 4:** the approximate value of *e* (sum of `1/n!`), the number of terms added and the last term added. The sum stops when a term is smaller than `ε`.
- **Option 5:** number of grades entered, sum, average, highest, lowest and how many grades are `>= 60`.
- **Option 6:** a right triangle of asterisks and a multiplication table.
- **Option 7:** the first Pythagorean triple `a b c` (with `a < b < c`) whose sum is the perimeter, or a message if there is none.
- **Option 0:** the number of operations performed. Only completed operations are counted (an invalid menu option is not).

## CONCEPTS PUT INTO PRACTICE

- `for`, `while` and `do-while` loops, including the infinite loop `for ( ; ; )` used as the menu
- Nested loops (triangle, multiplication table and triple search)
- `break` and `continue`
- `goto` to leave nested loops and the menu
- Comma operator in the control expression of a `for` (Fibonacci)
- `switch` statement inside a loop
- Input validation with loops
- Counters, accumulators and tracking of the highest and lowest values
- Euclidean algorithm (GCD) and the relation between GCD and LCM
- Series approximation with a stopping tolerance (`ε`)
- `bool` with `<stdbool.h>`
- Formatted output with width (`%4d`, `%.6f`, `%g`) and column alignment

## HOW TO COMPILE AND RUN

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o numeric_lab
./numeric_lab
```

## EXAMPLE RUN

```text
=========================
       NUMERIC LAB
=========================

---MENU---

1 - Primes up to N
2 - GCD and LCM
3 - Fibonacci sequence
4 - Approximate e
5 - Grade statistics
6 - Drawings
7 - Pythagorean triple
0 - Exit

Choose an option: 1

---PRIMES UP TO N---

Enter N (N >= 2): 30

  2  3  5  7 11
 13 17 19 23 29
Total: 10 primes

---MENU---

1 - Primes up to N
2 - GCD and LCM
3 - Fibonacci sequence
4 - Approximate e
5 - Grade statistics
6 - Drawings
7 - Pythagorean triple
0 - Exit

Choose an option: 7

---PYTHAGOREAN TRIPLE---

Enter the perimeter (1 to 500): 30

First triple found: 5 12 13

---MENU---

1 - Primes up to N
2 - GCD and LCM
3 - Fibonacci sequence
4 - Approximate e
5 - Grade statistics
6 - Drawings
7 - Pythagorean triple
0 - Exit

Choose an option: 0

Operations performed: 2
```

## KNOWN LIMITATIONS

- **Non-numeric input causes an infinite loop.** The return value of `scanf` is not checked and the invalid text is never removed from the input, so the menu and the validation loops keep failing forever (the same happens at the end of the input). Press `Ctrl+C` to stop the program.
- **No upper limit for `N` in option 1.** Every possible divisor is tested, so very large values take a long time (`N = 100000` takes about one second).
- **Limited precision in option 4.** The calculation uses `float`, so a very small `ε` does not make the result more accurate.
- **Only the first triple in option 7.** The search stops at the first triple found, the one with the smallest `a`.
- **UTF-8 terminal required.** The `ε` character may not display correctly in terminals that do not use UTF-8.
