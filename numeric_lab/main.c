#include <stdio.h>
#include <stdbool.h>

int main(void)
{
     printf("=========================\n");
     printf("       NUMERIC LAB       \n");
     printf("=========================\n\n");

     int operations = 0; // Count the operations performed
     for ( ; ; ) {
          printf("---MENU---\n\n");

          printf("1 - Primes up to N\n");
          printf("2 - GCD and LCM\n");
          printf("3 - Fibonacci sequence\n");
          printf("4 - Approximate e\n");
          printf("5 - Grade statistics\n");
          printf("6 - Drawings\n");
          printf("7 - Pythagorean triple\n");
          printf("0 - Exit\n\n");

          int option;
          printf("Choose an option: ");
          scanf("%d", &option);
          printf("\n");
          switch (option) {
               case 1: {
                    printf("---PRIMES UP TO N---\n\n");

                    int n;
                    printf("Enter N (N >= 2): ");
                    scanf("%d", &n);

                    // Validate the input
                    while (n < 2) {
                         printf("Invalid value for N! Enter N (N >= 2): ");
                         scanf("%d", &n);
                    }

                    // Calculate the width of the column to be printed
                    int remaining = n, columnWidth = 0;
                    do {
                         remaining /= 10;
                         columnWidth++;
                    } while (remaining > 0);

                    printf("\n");
                    int totalPrimes = 0;
                    for (int candidate = 2; candidate <= n; candidate++) {
                         // Try to find a divisor for candidate
                         int divisor = 2;
                         for ( ; divisor < candidate; divisor++) {
                              if (candidate % divisor == 0) {
                                   break;
                              }
                         }

                         // Define whether the number is prime
                         if (divisor == candidate) {
                              totalPrimes++;

                              // Calculate the width of the candidate number
                              remaining = candidate;
                              int candidateWidth = 0;
                              do {
                                   remaining /= 10;
                                   candidateWidth++;
                              } while (remaining > 0);

                              // Align the numbers
                              for (int width = 0; width < columnWidth - candidateWidth + 1; width++) {
                                   printf(" ");
                              }
                              printf("%d", candidate);
                              // End the current line if it has 5 numbers
                              if (totalPrimes % 5 == 0) {
                                   printf("\n");
                              }
                         }
                    }
                    // End the current line if it has fewer than 5 numbers
                    if (totalPrimes % 5 != 0) {
                         printf("\n");
                    }
                    printf("Total: %d primes\n\n", totalPrimes);

                    operations++;
                    break;
               }

               case 2: {
                    printf("---GCD AND LCM---\n\n");

                    int n1, n2;
                    printf("Enter two positive integers (1 to 10000): ");
                    scanf("%d %d", &n1, &n2);

                    // Validate the input
                    while (n1 < 1 || n1 > 10000 || n2 < 1 || n2 > 10000) {
                         printf("Invalid value(s)! Enter two positive integers (1 to 10000): ");
                         scanf("%d %d", &n1, &n2);
                    }

                    // Calculate the GCD
                    int element1 = n1, element2 = n2;
                    while (element2 != 0) {
                         int remainder = element1 % element2;
                         element1 = element2;
                         element2 = remainder;
                    }
                    int gcd = element1;

                    // Calculate the LCM
                    int lcm = n1 * n2 / gcd;

                    printf("\nGCD: %d\n", gcd);
                    printf("LCM: %d\n\n", lcm);

                    operations++;
                    break;
               }

               case 3: {
                    printf("---FIBONACCI SEQUENCE---\n\n");

                    int n;
                    printf("Enter N (1 to 40): ");
                    scanf("%d", &n);

                    // Validate the input
                    while (n < 1 || n > 40) {
                         printf("Invalid value for N! Enter N (1 to 40): ");
                         scanf("%d", &n);
                    }

                    // Calculate and print the Fibonacci numbers
                    int n1 = 1, n2 = 1;
                    printf("F1: %d\n", n1);
                    if (n >= 2) {
                         printf("F2: %d\n", n2);
                         for (int i = 2, sum = n1 + n2; i < n; i++, n1 = n2, n2 = sum, sum = n1 + n2) {
                              printf("F%d: %d\n", (i + 1), sum);
                         }
                    }
                    printf("\n");

                    operations++;
                    break;
               }

               case 4: {
                    printf("---APPROXIMATE e---\n\n");

                    float epsilon;
                    printf("Enter the value of ε (ε > 0): ");
                    scanf("%g", &epsilon);

                    // Validate the input
                    while (epsilon <= 0) {
                         printf("Invalid value for ε! Enter the value of ε (ε > 0): ");
                         scanf("%g", &epsilon);
                    }

                    float term = 1.0;
                    float e = 1.0 + term;
                    float fac = 1.0;
                    int termsAdded = 2;
                    // Add terms until the current term is less than ε
                    while (term >= epsilon) {
                         fac *= termsAdded;
                         term = 1.0 / fac;
                         e += term;
                         termsAdded++;
                    }

                    printf("\nThe approximate value of e is: %.6f\n", e);
                    printf("Terms added: %d\n", termsAdded);
                    printf("Last term: %g\n\n", term);

                    operations++;
                    break;
               }

               case 5: {
                    printf("---GRADE STATISTICS---\n\n");

                    printf("Enter a grade from 0 to 100 (-1 to stop):\n");
                    int grade, lowest = 101, highest = -1, gradesCounter = 0, sum = 0, goodGradesCounter = 0;
                    for ( ; ; ) {
                         printf("Grade: ");
                         scanf("%d", &grade);

                         // Stop condition
                         if (grade == -1) {
                              break;
                         }

                         // Validate the input
                         if (grade < 0 || grade > 100) {
                              printf("Invalid grade! Enter a grade from 0 to 100 (-1 to stop):\n");
                              continue;
                         }

                         gradesCounter++;
                         sum += grade;

                         if (grade > highest) {
                              highest = grade;
                         }

                         if (grade < lowest) {
                              lowest = grade;
                         }

                         // Count the good grades
                         if (grade >= 60) {
                              goodGradesCounter++;
                         }
                    }

                    if (gradesCounter == 0) {
                         printf("\nNo grades were entered\n\n");
                    } else {
                         printf("\nGrades entered: %d\n", gradesCounter);
                         printf("Sum: %d\n", sum);
                         printf("Average: %.2f\n", (1.0 * sum / gradesCounter));
                         printf("Highest: %d\n", highest);
                         printf("Lowest: %d\n", lowest);
                         printf("Grades >= 60: %d\n\n", goodGradesCounter);
                    }

                    operations++;
                    break;
               }

               case 6: {
                    printf("---DRAWINGS---\n\n");

                    int h;
                    printf("Enter the triangle height (1 to 15): ");
                    scanf("%d", &h);

                    // Validate the input
                    while (h < 1 || h > 15) {
                         printf("Invalid height! Enter the triangle height (1 to 15): ");
                         scanf("%d", &h);
                    }

                    // Print the triangle
                    printf("\n");
                    for (int i = 0; i < h; i++) {
                         for (int j = 0; j <= i; j++) {
                              printf("*");
                         }
                         printf("\n");
                    }

                    int n;
                    printf("\nEnter the table size (1 to 12): ");
                    scanf("%d", &n);

                    // Validate the input
                    while (n < 1 || n > 12) {
                         printf("Invalid size! Enter the table size (1 to 12): ");
                         scanf("%d", &n);
                    }

                    // Print the multiplication table
                    printf("\n");
                    for (int i = 1; i <= n; i++) {
                         for (int j = 1; j <= n; j++) {
                              printf("%4d", (j * i));
                         }
                         printf("\n");
                    }
                    printf("\n");

                    operations++;
                    break;
               }

               case 7: {
                    printf("---PYTHAGOREAN TRIPLE---\n\n");

                    int p;
                    printf("Enter the perimeter (1 to 500): ");
                    scanf("%d", &p);

                    // Validate the input
                    while (p < 1 || p > 500) {
                         printf("Invalid perimeter! Enter the perimeter (1 to 500): ");
                         scanf("%d", &p);
                    }

                    // Find the first Pythagorean triple
                    int a, b, c;
                    bool tripleIsFound = false;
                    for (a = 3; a <= (p - 3) / 3; a++) {
                         for (b = a + 1; b <= (p - a - 1) / 2; b++) {
                              for (c = b + 1; c < p / 2; c++) {
                                   if (a + b + c == p && a * a + b * b == c * c) {
                                        tripleIsFound = true;
                                        goto triple_found; // Exit all three loops
                                   }
                              }
                         }
                    }
                    triple_found:

                    printf("\n");
                    if (tripleIsFound) {
                         printf("First triple found: %d %d %d\n\n", a, b, c);
                    } else {
                         printf("No triple found for perimeter %d\n\n", p);
                    }

                    operations++;
                    break;
               }

               case 0: goto exit_menu;

               default:
                    printf("Invalid option!\n\n");
          }
     }
     exit_menu:

     printf("Operations performed: %d\n", operations);

     return 0;
}
