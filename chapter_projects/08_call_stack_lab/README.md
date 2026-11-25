# Call Stack Lab

A menu-driven C program with three modules that explore recursion and the call stack: Fibonacci sequence, binary search and sum and reverse of a number's digits. All modules use only recursive functions.

## INPUT

All numbers are read by the same function, which reads one full line per number. A number is valid if it has an optional '-' sign at the beginning followed by one or more digits. Leading zeros are accepted (`007` is read as 7) and `-0` is read as 0. Empty lines, a lone '-', letters, spaces, the '+' sign and any extra character are invalid.

- **Menu:** one option from 1 to 4. Since the menu uses the same function, `01` is accepted as option 1. Any other input shows "Invalid option!" and the menu is shown again.
- **Fibonacci sequence:** the desired term, from 0 to 23.
- **Binary search:**
     - The quantity of elements, from 1 to 10.
     - The value of each element, from -20000 to 20000. Negative and repeated values are accepted.
     - The value to be searched, from -20000 to 20000.
- **Sum and reverse:** one number, from -9999 to 9999. Negative numbers and zero are accepted.

If a value is outside its range, the program shows an error message ("Invalid term!", "Invalid quantity!" or "Invalid value!") and requests the input again.

## OUTPUT

The program starts with the program title, followed by the menu. After each module ends, the menu is shown again until the user chooses to exit. When the user exits, the program prints "Closing...".

- **Fibonacci sequence:** prints the title `---FIBONACCI SEQUENCE---` and then each term from 0 up to the desired term, one per line, in the format `F(n) = value`. The sequence starts at term 0, so F(0) = 0 and F(1) = 1.
- **Binary search:**
     - Prints the title `---BINARY SEARCH---`.
     - Prints the sorted array after `Sorted: `, with each number followed by a space.
     - If the searched value is in the array, prints `Position: N`, where N is counted from 1. If the array has repeated values, the position shown is the one of an occurrence found by the search, not necessarily the first.
     - If the searched value is not in the array, prints "The number is not in the current input!". The search ends and the program returns to the menu.
- **Sum and reverse:**
     - Prints the title `---SUM AND REVERSE---`, then the labels `Sum:` and `Reversed:`. The number entered is not repeated.
     - If the number is negative, the sum is also negative and the reversed number keeps the sign. Example: -472 prints `Sum: -13` and `Reversed: -274`.
     - Leading zeros of the reversed number are kept. Example: 1200 prints `Reversed: 0021`.
     - Zero prints `Sum: 0` and `Reversed: 0`.

## CONCEPTS PUT INTO PRACTICE

- **Recursion:** every module uses recursive functions only, each one with a base case that ends the recursion.
     - `calculate_term()` makes two recursive calls and adds the results on the way back.
     - `find_index()` makes one recursive call per step and does no calculation on the way back.
     - `sum_digits()` adds the last digit on the way back, while `reverse_digits()` prints the last digit before the recursive call, so the digits come out reversed.
     - `quicksort()` and `split()` sort the array with recursion.
- **Call stack:** pending calls wait on the stack until the base case is reached, and each call has its own copy of its parameters.
- **Functions:** one function per task, with prototypes before `main`, and the same function (`read_number()`) shared by the menu and all modules.
- **Variable-length arrays:** the array of the binary search is declared with the length chosen by the user.
- **Arrays as parameters:** the array is passed to `quicksort()`, `split()` and `find_index()` together with the `low` and `high` limits of the range being processed.
- **Input validation:** `read_number()` reads the input with `getchar()`, checks each character and checks for overflow before each calculation. Validation loops request the input again until the value is in range.
- **Characters and digits:** a digit character is converted to its value with `ch - '0'`.
- **Control flow:** `do`/`while` for the menu, `switch` for the options and `for` loops for the output.
- **Macros:** every limit, menu option and special value has a name, and the messages use `%d` with the macros instead of repeating the numbers.

## HOW TO COMPILE AND RUN

Compile with GCC using the C99 standard:

```
gcc -std=c99 -Wall -Wextra -pedantic call_stack_lab.c -o call_stack_lab
```

Run the program:

```
./call_stack_lab
```

## EXAMPLE RUN

**Fibonacci sequence:**

```
============================
       CALL STACK LAB       
============================

Choose an option:
1 - Fibonacci sequence
2 - Binary search
3 - Sum and reverse
4 - Exit

Option: 1

---FIBONACCI SEQUENCE---

Enter the desired term of the Fibonacci sequence (0 to 23): 5

F(0) = 0
F(1) = 1
F(2) = 1
F(3) = 2
F(4) = 3
F(5) = 5
```

**Binary search:**

```
============================
       CALL STACK LAB       
============================

Choose an option:
1 - Fibonacci sequence
2 - Binary search
3 - Sum and reverse
4 - Exit

Option: 2

---BINARY SEARCH---

Enter the quantity of elements (1 to 10): 5
Enter the value of the 1 element (-20000 to 20000): 9
Enter the value of the 2 element (-20000 to 20000): -3
Enter the value of the 3 element (-20000 to 20000): 7
Enter the value of the 4 element (-20000 to 20000): 1
Enter the value of the 5 element (-20000 to 20000): 5

Sorted: -3 1 5 7 9 
Enter the value of the element to be searched (-20000 to 20000): 7
Position: 4
```

**Sum and reverse:**

```
============================
       CALL STACK LAB       
============================

Choose an option:
1 - Fibonacci sequence
2 - Binary search
3 - Sum and reverse
4 - Exit

Option: 3

---SUM AND REVERSE---

Enter a number to sum and reverse its digits (-9999 to 9999): -472
Sum: -13
Reversed: -274
```

## KNOWN LIMITATIONS

- **16-bit limits:** the program works with the smallest `int` guaranteed by the C standard (16 bits, maximum 32767) to be more portable. The limits (23 for the Fibonacci term, 9999 for sum and reverse, 20000 for binary search and 30000 for the number reading) are rules of the program, not of the type, and are checked explicitly, because on x86-64 with GCC the `int` has 32 bits.
- **Fibonacci recalculation:** each term is calculated from zero by `calculate_term()`, without reusing the previous terms.
- **Repeated values in binary search:** if the array has repeated values, the position shown is the one of an occurrence found by the search, not necessarily the first.
- **Searching another value:** the program searches only one value per array. To search another value, the user returns to the menu and enters the array again.
- **Leading zeros in the menu:** since the menu uses the same function as the other inputs, `01` is accepted as option 1.
- **End of input:** if the input ends (Ctrl+D), the program stops responding in the menu and in the reading loops. This behavior was observed on x86-64 with GCC on Linux.