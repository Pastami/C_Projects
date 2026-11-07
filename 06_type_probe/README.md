# Type Probe

An interactive command-line program for exploring the basic types of C:
their sizes, ranges, precision, conversions and behavior at the limits.
It is a menu-driven program written entirely inside `main`, in C99, with
no functions, arrays or pointers. Limits and constants are computed by the
program itself instead of being read from `limits.h`, `float.h` or
`stdint.h`. The menu repeats until the user chooses to exit.

Capstone project of Chapter 7, Basic Types (K.N. King, C Programming: A Modern Approach).

## INPUT

| Menu option | Input | Valid values |
|---|---|---|
| 1 - Integer type sizes | none | |
| 2 - Base converter | a non-negative number | decimal, octal (prefix `0`) or hexadecimal (prefix `0x` or `0X`) |
| 3 - Unsigned wraparound | none | |
| 4 - Floating-point precision | none | |
| 5 - Text analyzer | `c`, `s` or `e`, then a line of text | upper or lower case option, any text on one line |
| 6 - Conversion lab | none | |
| 0 - Exit | none | |

Invalid values are rejected with a message, and the program returns to the menu.

## OUTPUT

- Option 1: the size of each integer type and the minimum and maximum values of each one on the user's machine.
- Option 2: the entered number in decimal, octal and hexadecimal forms.
- Option 3: for each unsigned type, the maximum value, the size of the operation, the result of adding 1 to the maximum and the result of subtracting 1 from 0. For `unsigned char` and `unsigned short`, it also shows the value stored back, because of the promotion to `int`.
- Option 4: the size of each floating-point type, the format specifiers `%f`, `%e` and `%g`, the significant digits of 0.1, and the epsilon (the difference between 1 and the next representable value), the largest finite value and the smallest normalized value of each type.
- Option 5: with `c`, the number of characters, letters, digits and others (spaces, punctuation, etc.). With `s`, the entered text with the case of the letters swapped. With `e`, the entered text encrypted with the Caesar cipher (with a shift of 3 by default).
- Option 6: examples of casts, promotion, assignment truncation, out-of-range values in `signed char` and `unsigned char`, and comparisons between signed and unsigned values.
- Option 0: ends the program.

## CONCEPTS PUT INTO PRACTICE

- Integer types, signed and unsigned: `char`, `short`, `int`, `long` and `long long`.
- Floating types: `float`, `double` and `long double`.
- The `sizeof` operator.
- `printf` conversion specifiers and length modifiers (`%zu`, `%hhd`, `%lld`, `%Lf`, `%e`, `%g`).
- Integer promotion, usual arithmetic conversions and assignment truncation.
- Casts.
- Unsigned wraparound and implementation-defined conversions of out-of-range values.
- Octal and hexadecimal numbers.
- Character arithmetic, `getchar`, `putchar` and `toupper`.
- Escape sequences (`\t`, `\n`).
- Type definitions with `typedef`.
- Constants defined with `#define`.
- `switch` statement inside a loop.
- The infinite loop `for ( ; ; )` used as the menu and `goto` to return to it.
- `bool` with `<stdbool.h>`.

## HOW TO COMPILE AND RUN

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o type_probe
./type_probe
```

The compiler prints the `-Woverflow` and `-Wsign-compare` warnings. The `-Woverflow` belongs to the lines `signed char char_example = 300;` and `signed char char_signed = 200;`, and the `-Wsign-compare` belongs to the line `is_smaller = -1 < 1u;`, because they are the intentional examples of overflow and comparison between signed and unsigned values.

## EXAMPLE RUN

The session below shows module 1 and module 2 on x86-64, GCC, Linux. The sizes and ranges in module 1 depend on the platform.

```text
$ ./type_probe
====================
     TYPE PROBE     
====================

---MENU---

1 - Integer type sizes
2 - Base converter
3 - Unsigned wraparound
4 - Floating-point precision
5 - Text analyzer
6 - Conversion lab
0 - Exit

Choose an option: 1


---INTEGER TYPE SIZES---

>> Sizes

Char:                   1 byte(s)
Short:                  2 byte(s)
Int:                    4 byte(s)
Long:                   8 byte(s)
Long long:              8 byte(s)

>> Value Ranges

Char:                   -128 to 127
Signed char:            -128 to 127
Unsigned char:          0 to 255
Short:                  -32768 to 32767
Unsigned short:         0 to 65535
Int:                    -2147483648 to 2147483647
Unsigned int:           0 to 4294967295
Long:                   -9223372036854775808 to 9223372036854775807
Unsigned long:          0 to 18446744073709551615
Long long:              -9223372036854775808 to 9223372036854775807
Unsigned long long:     0 to 18446744073709551615

---MENU---

1 - Integer type sizes
2 - Base converter
3 - Unsigned wraparound
4 - Floating-point precision
5 - Text analyzer
6 - Conversion lab
0 - Exit

Choose an option: 2


---BASE CONVERTER---

Enter a non-negative number: 0xFF

Decimal:        255
Octal:          377
Hexadecimal:    FF

---MENU---

1 - Integer type sizes
2 - Base converter
3 - Unsigned wraparound
4 - Floating-point precision
5 - Text analyzer
6 - Conversion lab
0 - Exit

Choose an option: 0
```

## KNOWN LIMITATIONS

The program was written and tested on x86-64, GCC, Linux.

- **Byte size fixed at 8 bits.** The `BITS` macro is 8, and the number of value bits of each integer type is computed from it. On a platform with another byte size, the ranges shown in module 1 are wrong.
- **Two's complement assumed.** The minimum of each signed type is computed as `-max - 1`. With another representation, such as sign and magnitude, the minimum shown is wrong.
- **IEEE 754 assumed.** The maximum and minimum exponents are fixed in the code: 127 and -126 for `float`, 1023 and -1022 for `double`, 16383 and -16382 for `long double` (the x87 80-bit format). With other formats, the largest finite and smallest normalized values shown are wrong.
- **Expressions evaluated in their own type.** The epsilon loops assume that each `float` and `double` expression is evaluated in its own precision. On targets that use the x87 unit, intermediate results may carry extra precision. The epsilon and the values calculated from it can then differ.
- **Signedness of `char` depends on the platform.** Plain `char` is signed on x86-64, GCC, Linux. Where it is unsigned, the `Char` range in module 1 is 0 to 255, and the compiler may emit different `-Woverflow` or `-Wtype-limits` warnings.
- **Out-of-range conversions to signed types.** Module 6 stores `300` and `200` in a `signed char`, and the sum `100 + 100` back in one. The program assumes that the compiler keeps only the bits that fit in the type, as GCC does. The C standard leaves this result to the implementation (or allows a signal). On another compiler, the values shown for these lines may be different.
- **Type sizes depend on the platform.** The program prints the sizes it finds, so the values in modules 1, 3, 4 and 6 may differ from the example run. In module 3, the maximum values and the operation sizes follow the sizes of the types and of `int`. In module 6, the expression size follows the size of `int`. For instance, `long` has 4 bytes on 64-bit Windows.
- **Tab stops of 8 columns assumed.** The output is aligned with `\t`. With a different tab width, the columns do not line up.
- **No overflow check in module 2.** The number is stored in an `unsigned long long`, in decimal, octal and hexadecimal input. A value above the maximum of the type (18446744073709551615 on x86-64, GCC, Linux) wraps around without any warning. The result shown is then not the number that was typed.
- **Contiguous letters assumed.** Module 5 assumes that the codes of the letters `A` to `Z` are contiguous, which holds for ASCII. In other character sets, such as EBCDIC, the letter count, the case swap and the cipher give wrong results.
- **Text read byte by byte.** Accented letters in UTF-8 take 2 bytes, so each one counts as 2 characters and 2 others in `c`. They pass through `s` and `e` unchanged.
- **Negative `char` values passed to `toupper`.** Modules 2 and 5 call `toupper` with a plain `char`. On x86-64, GCC, Linux, `char` is signed, so the bytes of accented letters in UTF-8 become negative values. The C standard only allows `toupper` to receive values of `unsigned char` or `EOF`, so this works because the glibc implementation accepts negative values. On another library, the results may be wrong.