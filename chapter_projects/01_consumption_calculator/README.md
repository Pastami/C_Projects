# Consumption Calculator

The program calculates the fuel consumption for a trip.

Capstone project of Chapter 2, *C Fundamentals* (K.N. King, *C Programming: A Modern Approach*).

## INPUT

| Value | Unit |
|---|---|
| Total trip distance | km |
| Car fuel efficiency | km/liter |
| Fuel price | per liter |
| Number of trip days | days |

## OUTPUT

- Fuel needed (liters)
- Total fuel cost
- Average cost per day
- Average km per day

## CONCEPTS PUT INTO PRACTICE

- Header `<stdio.h>`
- Function `int main(void)` with `return 0`, indicating that the program finished successfully
- Variable declaration and initialization with `int` and `float`
- Formatted input/output: `%f` and `%d` placeholders, the `&` operator and the `\n` character
- Arithmetic operators: division `/` and multiplication `*`

## HOW TO COMPILE AND RUN

Inside the project folder:

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c -o consumption_calculator
./consumption_calculator
```

## EXAMPLE RUN

```text
============================================
           CONSUMPTION CALCULATOR
============================================

Enter total trip distance (km): 300
Enter car fuel efficiency (km/liter): 10
Enter fuel price per liter: 5
Enter number of trip days: 3

============Trip Summary============
Fuel needed (liters): 30.000000
Total fuel cost: 150.000000
Average cost per day: 50.000000
Average km per day: 100.000000
```

## KNOWN LIMITATIONS

- **Input is not validated.** The program does not check the values typed by the user.
- **Fuel efficiency equal to `0`.** The fuel needed, the total fuel cost and the average cost per day are printed as `inf`.
- **Number of days equal to `0`.** The average cost per day and the average km per day are printed as `inf`.
- **Non-numeric input.** If the user types letters instead of numbers, `scanf` fails and the variables keep unpredictable values, so the results are meaningless.
- **Six decimal places.** Values are printed with six decimal places, since the `%f` placeholder is used without a precision.
