# Invoice Generator

A console program that reads a customer code, three purchase items and the date and time of the purchase, and prints a formatted invoice with the subtotal of each item, the overall subtotal, a 10% tax and the final total.

Capstone project of Chapter 3, *Formatted Input/Output* (K.N. King, *C Programming: A Modern Approach*).

## INPUT

The program asks for the following values, in this order:

| Prompt | Values | Type |
|---|---|---|
| Customer code | one value | `int` |
| Item 1, 2 and 3 | product code, unit price and quantity, separated by spaces | `int`, `float`, `int` |
| Purchase date | `mm/dd/yyyy` (with the slashes) | `int`, `int`, `int` |
| Purchase time | `hh:mm` (with the colon) | `int`, `int` |

## OUTPUT

An invoice containing:

- Customer code, padded with zeros to at least 4 digits (`0007`)
- Purchase date and time, with zero-padded fields (`10/05/2026   14:30`)
- A table with product code, unit price, quantity and subtotal of each item
- Subtotal (sum of the three items), tax (10%) and TOTAL, all with 2 decimal places

## CONCEPTS PUT INTO PRACTICE

- Formatted output with `printf`: field width (`%4d`, `%10.2f`), precision on integers for zero padding (`%.4d`, `%.2d`) and the literal percent sign (`%%`)
- Escape sequences (`\t`, `\n`) for aligning columns
- Formatted input with `scanf`, including literal characters in the format string (`/` and `:`) to read a date and a time
- Reading several values of different types in a single `scanf`
- Arithmetic with `int` and `float`, and the implicit conversion between them
- Percentage calculation

## HOW TO COMPILE AND RUN

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o invoice_generator
./invoice_generator
```

## EXAMPLE RUN

```text
=================================
        INVOICE GENERATOR
=================================

Enter customer code: 7

Enter product code, unit price and quantity for item 1: 101 12.50 3
Enter product code, unit price and quantity for item 2: 205 4.99 10
Enter product code, unit price and quantity for item 3: 310 100.00 1

Enter purchase date (mm/dd/yyyy): 10/05/2026
Enter purchase time (hh:mm): 14:30

---INVOICE---
Customer: 0007
Date: 10/05/2026   Time: 14:30

Item    Unit Price      Qty     Subtotal
 101         12.50        3        37.50
 205          4.99       10        49.90
 310        100.00        1       100.00

Subtotal:                         187.40
Tax (10%):                         18.74
----------------------------------------
TOTAL:                            206.14
```

## KNOWN LIMITATIONS

- **Input is not validated.** The return value of `scanf` is not checked, and dates and times are not verified, so values such as `13/45/2026` or `25:99` are accepted.
- **The input format must match exactly.** If the date is typed as `10-05-2026` or the time as `14.30`, `scanf` stops reading and the remaining variables are left uninitialized, producing wrong output.
- **Negative or zero prices and quantities are accepted.** Rejecting them requires conditional statements.
- **Fixed number of items.** The invoice always has exactly three items.
- **Fixed tax rate.** The 10% tax is hard-coded.
- **Monetary values use `float`.** This type has limited precision, so small rounding differences can appear with large values.
- **Fixed column widths.** Very large codes, prices or quantities exceed the field widths and misalign the table.
