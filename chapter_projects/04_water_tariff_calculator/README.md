# Water Tariff Calculator

A console program that calculates a water bill from the monthly consumption, using a progressive tariff: each bracket of consumption is charged at its own price per m³. It has a menu with residential and commercial calculation, a tariff list and an option to quit.

Capstone project of Chapter 5, *Selection Statements* (K.N. King, *C Programming: A Modern Approach*).

## INPUT

| Step | Value | Type |
|---|---|---|
| Main menu | option from 1 to 4 | `int` |
| Options 1 and 2 | consumption in m³ (whole number greater than 0) | `int` |
| Option 1 only | `1` if the customer is low-income, `2` if not | `int` |

## OUTPUT

- **Option 1 (residential):** the amount charged in each bracket reached, the subtotal and the 50% low-income discount (only for low-income customers), and the final bill amount.
- **Option 2 (commercial):** the amount charged in each bracket reached and the final bill amount. There is no social discount.
- **Option 3:** the residential and commercial tariff tables.
- **Option 4:** a closing message.
- Error messages for an invalid menu option, an invalid consumption (not greater than 0) and an invalid low-income option.

### Tariffs ($/m³)

| Bracket | Residential | Commercial |
|---|---|---|
| 1-10 | 3.00 | 5.00 |
| 11-15 | 4.50 | 7.00 (11-20) |
| 16-20 | 6.00 | 7.00 (11-20) |
| 21-25 | 7.50 | 9.00 (21-30) |
| 26-30 | 9.00 | 9.00 (21-30) |
| Above 30 | 11.00 | 12.00 |

## CONCEPTS PUT INTO PRACTICE

- `if`, `else if` and `else` chains to find the bracket of the consumption
- `switch` statement for the main menu, with `default` for invalid options
- Intentional `switch` fall-through (omitting `break`) to accumulate the brackets from the highest one down to the first
- `break` to leave a `switch` early on invalid input
- Braces inside a `case` to declare variables local to that option
- Relational operators (`>`, `>=`, `!=`) and logical operators (`&&`) for validation
- Ternary operator to apply the low-income discount
- Formatted output with `printf` (`%d`, `%.2f`, `%%`) and escape sequences (`\t`, `\n`)
- Formatted input with `scanf`
- Arithmetic with `int` and `float`

## HOW TO COMPILE AND RUN

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o water_tariff_calculator
./water_tariff_calculator
```

The compiler prints several `-Wimplicit-fallthrough` warnings. This is expected: the fall-through between the `case` labels is intentional.

## EXAMPLE RUN

```text
===========================================
          WATER TARIFF CALCULATOR
===========================================

1 - Calculate residential tariff
2 - Calculate commercial tariff
3 - Check tariff list
4 - Quit
Choose an option: 1

Enter the consumption in m³: 28
1 - The customer IS low-income
2 - The customer IS NOT low-income
Choose an option: 1

Bracket 26-30: 3m³ x $9.00 = $27.00
Bracket 21-25: 5m³ x $7.50 = $37.50
Bracket 16-20: 5m³ x $6.00 = $30.00
Bracket 11-15: 5m³ x $4.50 = $22.50
Bracket 1-10: 10m³ x $3.00 = $30.00

Subtotal: $147.00
Low-income discount (50%): -$73.50

Bill amount: $73.50
```

## KNOWN LIMITATIONS

- **Single calculation per run.** The program ends after one operation, since loops are only introduced in Chapter 6. To calculate another bill, run it again.
- **Input is not validated.** The return value of `scanf` is not checked, so non-numeric input leaves variables uninitialized and the behavior is unpredictable.
- **Whole numbers only.** The consumption is read as an `int`, so decimal values such as `12.5` are not supported.
- **Intentional fall-through.** The `-Wimplicit-fallthrough` compiler warnings come from the `switch` statements that accumulate the brackets.
- **Hard-coded tariffs.** The brackets and prices are fixed in the code, and the currency symbol is `$`.
- **Social discount only for residential.** The commercial option has no discount.
- **UTF-8 terminal required.** The `³` character in `m³` may not display correctly in terminals that do not use UTF-8.
