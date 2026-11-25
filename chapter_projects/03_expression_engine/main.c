#include <stdio.h>

int main(void)
{
     // WARNING: Since Chapter 4 does not introduce if/else statements, division
     // by zero ("/" and "%") is not handled here. This will be addressed in
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

     int a, b, c, d, e, f;

     printf("\n---PRECEDENCE AND ASSOCIATIVITY---\n");
     printf("Expression: a %% b + c x d - e / f\n\n");

     printf("Insert integer values for a, b, c, d, e and f: ");
     scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
     printf("Values: a = %d; b = %d; c = %d; d = %d; e = %d; f = %d\n", a, b, c, d, e, f);
     printf("___________________________________________\n\n");

     // "%", "*" and "/" have higher precedence than "+" and "-".
     // All of them are left-associative.
     printf("STEP\t\t\t\tCALCULATION\n\n");

     int remainder = a % b;
     printf("Step 01:\t\t\t%d %% %d = %d\n", a, b, remainder);

     int product = c * d;
     printf("Step 02:\t\t\t%d x %d = %d\n", c, d, product);

     int quotient = e / f;
     printf("Step 03:\t\t\t%d / %d = %d\n", e, f, quotient);

     int addition = remainder + product;
     printf("Step 04:\t\t\t%d + %d = %d\n", remainder, product, addition);

     int subtraction = addition - quotient;
     printf("Step 05:\t\t\t%d - %d = %d\n\n", addition, quotient, subtraction);

     printf("Final result: %d %% %d + %d x %d - %d / %d = %d\n\n", a, b, c, d, e, f, subtraction);

     int accumulator;
     printf("---COMPOUND ASSIGNMENT OPERATORS---\n");
     printf("Insert an integer value for the accumulator: ");
     scanf("%d", &accumulator);
     printf("Accumulator = %d\n", accumulator);
     printf("___________________________________________\n\n");

     // Each assignment expression returns the new value of the accumulator,
     // so it is printed directly inside printf.
     printf("ASSIGNMENT\t\t\tNEW VALUE\n\n");
     printf("Accumulator += 5\t\t%d\n", (accumulator += 5));
     printf("Accumulator -= 3\t\t%d\n", (accumulator -= 3));
     printf("Accumulator *= 2\t\t%d\n", (accumulator *= 2));
     printf("Accumulator /= 4\t\t%d\n", (accumulator /= 4));
     printf("Accumulator %%= 4\t\t%d\n\n", (accumulator %= 4));

     int i, total;
     printf("---INCREMENT AND DECREMENT---\n");
     printf("Insert an integer value to be incremented/decremented: ");
     scanf("%d", &i);
     int originalValue = i;
     printf("___________________________________________\n\n");

     printf("POSTFIX\t\t\t RESULT\n\n");
     printf("i = %d\n", i);
     printf("Total = %d++ + 2\n", i);

     total = i++ + 2;
     i = originalValue;

     printf("Value used: %d", i++);
     printf("\t\tTotal = %d\n", total);
     printf("Value of i afterwards:\ti = %d\n\n", i);

     i = originalValue;
     printf("i = %d\n", i);
     printf("Total = %d-- + 2\n", i);

     total = i-- + 2;
     i = originalValue;

     printf("Value used: %d", i--);
     printf("\t\tTotal = %d\n", total);
     printf("Value of i afterwards:\ti = %d\n", i);
     printf("*******************************************\n\n");

     printf("PREFIX\t\t\t RESULT\n\n");

     i = originalValue;
     printf("i = %d\n", i);
     printf("Total = ++%d + 2\n", i);

     total = ++i + 2;
     i = originalValue;

     printf("Value used: %d", ++i);
     printf("\t\tTotal = %d\n", total);
     printf("Value of i afterwards:\ti = %d\n\n", i);

     i = originalValue;
     printf("i = %d\n", i);
     printf("Total = --%d + 2\n", i);

     total = --i + 2;
     i = originalValue;

     printf("Value used: %d", --i);
     printf("\t\tTotal = %d\n", total);
     printf("Value of i afterwards:\ti = %d\n\n", i);

     int value;
     printf("---CHAINED ASSIGNMENTS---\n");
     printf("Expression: a = b = c = value\n\n");

     printf("Insert an integer value to be assigned: ");
     scanf("%d", &value);
     printf("***NOTE: The assignment operator is right associative***\n");
     printf("___________________________________________\n\n");

     printf("STEP\t\t\tRESULT\n\n");

     printf("Step 01: c = %d\t\tc = %d\n", value, (c = value));
     printf("Step 02: b = c\t\tb = %d\n", (b = c));
     printf("Step 03: a = b\t\ta = %d\n\n", (a = b));

     a = b = c = value;
     printf("Chained assignment final result: a = %d, b = %d, c = %d\n\n", a, b, c);

     int j, result;
     printf("---UNDEFINED BEHAVIOR WARNING---\n");
     printf("Expression: result = j++ + j++ + j++\n\n");

     printf("Insert an integer value for j: ");
     scanf("%d", &j);
     printf("___________________________________________\n\n");

     // Intentional undefined behavior: j is modified more than once in the
     // same expression. The result is specific to this compiler.
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

     return 0;
}
