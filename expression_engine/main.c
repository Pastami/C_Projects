#include <stdio.h>

int main(void)
{
     // WARNING: Since Chapter 4 does not introduce the if/else statements, the
     // division by 0 is not handled here. This will be addressed in
     // future programs, once conditional statements are covered.

     printf("=================================\n");
     printf("        EXPRESSION ENGINE        \n");
     printf("=================================\n\n");

     int x, y;

     printf("---BASIC CALCULATOR---\n");
     printf("Insert integer values for x and y: ");
     scanf("%d %d", &x, &y);
     printf("Values: x = %d; y = %d\n", x, y);
     printf("___________________________________________\n\n");

     printf("OPERATION\t\t\tCALCULATION\n\n");
     printf("Addition:\t\t\t%d + %d = %d\n", x, y, (x + y));
     printf("Subtraction:\t\t\t%d - %d = %d\n", x, y, (x - y));
     printf("Multiplication:\t\t\t%d x %d = %d\n", x, y, (x * y));
     printf("Integer division:\t\t%d / %d = %d\n", x, y, (x / y));
     printf("Floating point division:\t%d / %d = %.2f\n", x, y, (x * 1.0 / y));
     printf("Remainder:\t\t\t%d %% %d = %d\n", x, y, (x % y));

     // The BASIC CALCULATOR session performs all four basic operations, distinguishing
     // between integer division, division with a decimal point and remainder.

     int a, b, c, d, e, f;

     printf("\n---PRECEDENCE AND ASSOCIATIVITY---\n");
     printf("Expression: a %% b + c x d - e / f\n\n");

     printf("Insert integer values for a, b, c, d, e and f: ");
     scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
     printf("Values: a = %d; b = %d; c = %d; d = %d; e = %d; f = %d\n", a, b, c, d, e, f);
     printf("___________________________________________\n\n");

     printf("STEP\t\t\t\tCALCULATION\n\n");

     int remainder = a % b;
     printf("Step 01:\t\t\t%d %% %d = %d\n", a, b, remainder);

     int product = c * d;
     printf("Step 02:\t\t\t%d x %d = %d\n", c, d, product);

     float quotient = e * 1.0f / f;
     printf("Step 03:\t\t\t%d / %d = %.2f\n", e, f, quotient);

     int addition = remainder + product;
     printf("Step 04:\t\t\t%d + %d = %d\n", remainder, product, addition);

     float subtraction = addition - quotient;
     printf("Step 05:\t\t\t%d - %.2f = %.2f\n\n", addition, quotient, subtraction);

     printf("Final result: %d %% %d + %d x %d - %d / %d = %.2f\n\n", a, b, c, d, e, f, subtraction );
     // The PRECEDENCE AND ASSOCIATIVITY session demonstrates the precedence and
     // associativity between the four basic operations, with remainder,
     // multiplication, and division having the highest precedence, addition and
     // subtraction the lowest precedence.
     // All of them are left-associative.

     int accumulator;
     printf("---COMPOUND ASSIGNMENT OPERATORS---\n");
     printf("Insert an integer value for the accumulator: ");
     scanf("%d", &accumulator);
     printf("Accumulator = %d\n", accumulator);
     printf("___________________________________________\n\n");

     printf("ASSIGNMENT\t\t\tNEW VALUE\n\n");
     printf("Accumulator += 5\t\t%d\n", (accumulator += 5));
     printf("Accumulator -= 3\t\t%d\n", (accumulator -= 3));
     printf("Accumulator *= 2\t\t%d\n", (accumulator *= 2));
     printf("Accumulator /= 4\t\t%d\n", (accumulator /= 4));
     printf("Accumulator %%= 4\t\t%d\n\n", (accumulator %= 4));

     // The COMPOUND ASSIGNMENT OPERATORS session demonstrates the five
     // compound assignment operators applied in sequence to the same
     // variable, printing the value returned by each assignment expression
     // directly inside printf.

     int i, total;
     printf("---INCREMENT AND DECREMENT---\n");
     printf("Insert an integer value to be incremented/decremented: ");
     scanf("%d", &i);
     int originalValue = i;
     // Stores the original value.
     printf("___________________________________________\n\n");

     printf("POSTFIX\t\t\t RESULT\n\n");
     printf("i = %d\n", i);
     printf("Total = %d++ + 2\n", i);

     total = i++ + 2;
     //Calculates the total;
     i = originalValue;
     // Resets the value of i after the calculation of total.

     printf("Value used: %d", i++);
     printf("\t\tTotal = %d\n", total);
     printf("Value of i afterwards:\ti = %d\n\n", i);

     i = originalValue;
     // Resets the value of i after the increment.
     printf("i = %d\n", i);
     printf("Total = %d-- +2\n", i);

     total = i-- + 2;
     //Calculates the total;
     i = originalValue;
     // Resets the value of i after the calculation of total.

     printf("Value used: %d", i--);
     printf("\t\tTotal = %d\n", total);
     printf("Value of i afterwards:\ti = %d\n", i);
     printf("*******************************************\n\n");

     printf("PREFIX\t\t\t RESULT\n\n");

     i = originalValue;
     // Resets the value of i after the decrement.
     printf("i = %d\n", i);
     printf("Total = ++%d + 2\n", i);

     total = ++i + 2;
     //Calculates the total;
     i = originalValue;
     // Resets the value of i after the calculation of total.

     printf("Value used: %d", ++i);
     printf("\t\tTotal = %d\n", (i + 2));
     printf("Value of i afterwards:\ti = %d\n\n", i);

     i = originalValue;
     // Resets the value of i after the increment.
     printf("i = %d\n", i);
     printf("Total = --%d + 2\n", i);

     total = --i + 2;
     //Calculates the total;
     i = originalValue;
     // Resets the value of i after the calculation of total.

     printf("Value used: %d", --i);
     printf("\t\tTotal = %d\n", (i + 2));
     printf("Value of i afterwards:\ti = %d\n\n", i);

     // The INCREMENT AND DECREMENT session demonstrates the increment
     // and decrement operator, either postfix and prefix, using printf
     // to demonstrate its behavior.

     int value;
     printf("---CHAINED ASSIGNMENTS---\n");
     printf("Expression: a = b = c = value\n\n");

     printf("Insert an integer value to be assigned: ");
     scanf("%d", &value);
     printf("***OBS: The assignment operator is right associative***\n");
     printf("___________________________________________\n\n");

     printf("STEP\t\t\tRESULT\n\n");

     printf("Step 01: c = %d\t\tc = %d\n", value, (c = value));
     printf("Step 02: b = c\t\tb = %d\n", (b = c));
     printf("Step 03: a = b\t\ta = %d\n\n", (a = b));

     a = b = c = value;
     printf("Chained assignment final result: a = %d, b = %d, c = %d\n\n", a, b, c);

     // The CHAINED ASSIGNMENTS session demonstrates the right-to-left
     // associativity of the assignment operator, showing that the same
     // value propagates through all three variables in a single statement.

     int j, result;
     printf("---UNDEFINED BEHAVIOR WARNING---\n");
     printf("Expression: result = j++ + j++ + j++\n\n");

     printf("Insert an integer value for j: ");
     scanf("%d", &j);
     printf("___________________________________________\n\n");

     result = j++ + j++ + j++;
     printf("Result obtained on this compiler: %d\n", result);
     printf("Value of j afterwards: %d\n", j);
     printf("*******************************************\n\n");

     printf("WARNING: the C standard does not guarantee the order in which\n");
     printf("the operands of \"+\" are evaluated. Modifying \"j\" more than once\n");
     printf("in the same expression is undefined behavior - the result may vary\n");
     printf("between different compilers.\n");
     printf("This block exists only to warn about what to AVOID writing,\n");
     printf("not to demonstrate a reliable result.\n");

     // The UNDEFINED BEHAVIOR WARNING session intentionally executes an
     // expression that modifies the same variable more than once within
     // the same expression, to show what NOT to write. The printed result
     // reflects only this specific compiler's behavior and is not
     // guaranteed by the C standard.

     return 0;
}
