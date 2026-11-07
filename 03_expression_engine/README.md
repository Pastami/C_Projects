# Expression Engine

A console program that walks through the arithmetic expressions of C, one section at a time: basic operations, operator precedence and associativity, compound assignment, increment/decrement, chained assignment and undefined behavior. Every section reads its own input and prints the intermediate steps, so the behavior of each operator can be seen directly.

Capstone project of Chapter 4, *Expressions* (K.N. King, *C Programming: A Modern Approach*).

## INPUT

The program asks for the values section by section, always integers (`int`):

| Section | Input |
|---|---|
| BASIC CALCULATOR | `x` and `y` |
| PRECEDENCE AND ASSOCIATIVITY | `a`, `b`, `c`, `d`, `e` and `f` |
| COMPOUND ASSIGNMENT OPERATORS | initial value of the accumulator |
| INCREMENT AND DECREMENT | value of `i` |
| CHAINED ASSIGNMENTS | value to be assigned |
| UNDEFINED BEHAVIOR WARNING | value of `j` |

## OUTPUT

- **BASIC CALCULATOR:** addition, subtraction, multiplication, integer division, floating point division (2 decimal places) and remainder of `x` and `y`.
- **PRECEDENCE AND ASSOCIATIVITY:** the expression `a % b + c x d - e / f` solved step by step, following the precedence and left-to-right associativity rules, followed by the final result.
- **COMPOUND ASSIGNMENT OPERATORS:** the new value of the accumulator after `+= 5`, `-= 3`, `*= 2`, `/= 4` and `%= 4`, applied in sequence.
- **INCREMENT AND DECREMENT:** postfix and prefix versions of `++` and `--`, showing the value used in the expression, the total and the final value of `i`.
- **CHAINED ASSIGNMENTS:** `a = b = c = value` broken down into three steps, from right to left.
- **UNDEFINED BEHAVIOR WARNING:** the result of `j++ + j++ + j++` on the current compiler, followed by a warning about why it must not be trusted.

## CONCEPTS PUT INTO PRACTICE

- Arithmetic operators (`+`, `-`, `*`, `/`, `%`)
- Integer division vs. floating point division (the precedence section uses integer division, as C does for `int` operands)
- Operator precedence and associativity (left-associative arithmetic operators)
- Compound assignment operators (`+=`, `-=`, `*=`, `/=`, `%=`)
- Assignment as an expression (the value of `(accumulator += 5)` used inside `printf`)
- Postfix and prefix increment/decrement
- Right-associativity of the assignment operator (chained assignments)
- Undefined behavior (modifying the same variable more than once in an expression)
- `printf` with format specifiers (`%d`, `%.2f`, `%%`) and escape sequences (`\t`, `\n`)
- `scanf` for reading integers

## HOW TO COMPILE AND RUN

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o expression_engine
./expression_engine
```

The compiler prints a `-Wsequence-point` warning for the line `result = j++ + j++ + j++;`. This is expected: that line is the intentional undefined behavior example.

## EXAMPLE RUN

```text
=================================
        EXPRESSION ENGINE
=================================

---BASIC CALCULATOR---
Insert integer values for x and y: 17 5
Values: x = 17; y = 5
___________________________________________

OPERATION                       CALCULATION

Addition:                       17 + 5 = 22
Subtraction:                    17 - 5 = 12
Multiplication:                 17 x 5 = 85
Integer division:               17 / 5 = 3
Floating point division:        17 / 5 = 3.40
Remainder:                      17 % 5 = 2

---PRECEDENCE AND ASSOCIATIVITY---
Expression: a % b + c x d - e / f

Insert integer values for a, b, c, d, e and f: 17 5 3 4 7 2
Values: a = 17; b = 5; c = 3; d = 4; e = 7; f = 2
___________________________________________

STEP                            CALCULATION

Step 01:                        17 % 5 = 2
Step 02:                        3 x 4 = 12
Step 03:                        7 / 2 = 3
Step 04:                        2 + 12 = 14
Step 05:                        14 - 3 = 11

Final result: 17 % 5 + 3 x 4 - 7 / 2 = 11

---COMPOUND ASSIGNMENT OPERATORS---
Insert an integer value for the accumulator: 10
Accumulator = 10
___________________________________________

ASSIGNMENT                      NEW VALUE

Accumulator += 5                15
Accumulator -= 3                12
Accumulator *= 2                24
Accumulator /= 4                6
Accumulator %= 4                2

---INCREMENT AND DECREMENT---
Insert an integer value to be incremented/decremented: 5
___________________________________________

POSTFIX                  RESULT

i = 5
Total = 5++ + 2
Value used: 5           Total = 7
Value of i afterwards:  i = 6

i = 5
Total = 5-- + 2
Value used: 5           Total = 7
Value of i afterwards:  i = 4
*******************************************

PREFIX                   RESULT

i = 5
Total = ++5 + 2
Value used: 6           Total = 8
Value of i afterwards:  i = 6

i = 5
Total = --5 + 2
Value used: 4           Total = 6
Value of i afterwards:  i = 4

---CHAINED ASSIGNMENTS---
Expression: a = b = c = value

Insert an integer value to be assigned: 7
***NOTE: The assignment operator is right associative***
___________________________________________

STEP                    RESULT

Step 01: c = 7          c = 7
Step 02: b = c          b = 7
Step 03: a = b          a = 7

Chained assignment final result: a = 7, b = 7, c = 7

---UNDEFINED BEHAVIOR WARNING---
Expression: result = j++ + j++ + j++

Insert an integer value for j: 4
___________________________________________

Result obtained on this compiler: 15
Value of j afterwards: 7
*******************************************

WARNING: the C standard does not guarantee the order in which
the operands of "+" are evaluated. Modifying "j" more than once
in the same expression is undefined behavior - the result may vary
between different compilers.
This block exists only to warn about what to AVOID writing,
not to demonstrate a reliable result.
```

The result of the last section (`15`) may be different on another compiler.

## KNOWN LIMITATIONS

- **Division by zero is not handled.** If `y` is `0`, the integer division and the remainder crash the program. The same applies to `b` in `a % b` and `f` in `e / f`. Conditional statements are only introduced in Chapter 5.
- **Input is not validated.** The return value of `scanf` is not checked, so non-numeric input leaves variables uninitialized.
- **No overflow protection.** Very large values can overflow `int` (for example, in `x * y` or in `accumulator *= 2`).
- **Negative operands are printed without parentheses.** The calculations are correct, but the output can look odd, for example `10 - -3 = 13` in Step 05. Printing parentheses only when needed requires conditional statements, which are introduced in Chapter 5.
- **Undefined behavior on purpose.** The result of `j++ + j++ + j++` depends on the compiler and is not guaranteed by the C standard.
