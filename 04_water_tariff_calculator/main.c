#include <stdio.h>

int main(void)
{
     printf("===========================================\n");
     printf("          WATER TARIFF CALCULATOR          \n");
     printf("===========================================\n\n");

     int option;
     printf("1 - Calculate residential tariff\n");
     printf("2 - Calculate commercial tariff\n");
     printf("3 - Check tariff list\n");
     printf("4 - Quit\n");
     printf("Choose an option: ");
     scanf("%d", &option);

     printf("\n");
     float bill = 0.0;
     switch (option) {
          case 1:{
               int consumption;
               printf("Enter the consumption in m³: ");
               scanf("%d", &consumption);

               // Define the bracket where the consumption fits in
               int bracket;
               if (consumption > 30) {
                    bracket = 1;
               } else if (consumption >= 26) {
                    bracket = 2;
               } else if (consumption >= 21) {
                    bracket = 3;
               } else if (consumption >= 16) {
                    bracket = 4;
               } else if (consumption >= 11) {
                    bracket = 5;
               } else if (consumption >= 1) {
                    bracket = 6;
               } else {
                    printf("Invalid consumption value. Enter a consumption value GREATER than 0!\n");
                    break;
               }

               int isLowIncome;
               printf("1 - The customer IS low-income\n");
               printf("2 - The customer IS NOT low-income\n");
               printf("Choose an option: ");
               scanf("%d", &isLowIncome);

               // Validate the input
               if (isLowIncome != 1 && isLowIncome != 2) {
                    printf("Invalid option. Enter 1 or 2!\n");
                    break;
               }

               printf("\n");
               // Calculate the subtotal using switch fallthrough
               float subtotal = 0.0;
               switch (bracket) {
                    case 1:
                         subtotal = (consumption - 30) * 11.00;

                         printf("Bracket above 30: %dm³ x $11.00 = $%.2f\n", (consumption - 30), subtotal);

                         consumption = 30;
                    case 2:
                         subtotal += (consumption - 25) * 9.00;

                         printf("Bracket 26-30: %dm³ x $9.00 = $%.2f\n", (consumption - 25), ((consumption - 25) * 9.00));

                         consumption = 25;
                    case 3:
                         subtotal += (consumption - 20) * 7.50;

                         printf("Bracket 21-25: %dm³ x $7.50 = $%.2f\n", (consumption - 20), ((consumption - 20) * 7.50));

                         consumption = 20;
                    case 4:
                         subtotal += (consumption - 15) * 6.00;

                         printf("Bracket 16-20: %dm³ x $6.00 = $%.2f\n", (consumption - 15), ((consumption - 15) * 6.00));

                         consumption = 15;
                    case 5:
                         subtotal += (consumption - 10) * 4.50;

                         printf("Bracket 11-15: %dm³ x $4.50 = $%.2f\n", (consumption - 10), ((consumption - 10) * 4.50));

                         consumption = 10;
                    case 6:
                         subtotal += consumption * 3.00;

                         printf("Bracket 1-10: %dm³ x $3.00 = $%.2f\n", (consumption), (consumption * 3.00));

                         break;
               }

               // Apply the 50% discount if the customer is low-income
               bill = isLowIncome == 1 ? subtotal * 0.5 : subtotal;

               if (isLowIncome == 1) {
                    printf("\nSubtotal: $%.2f\n", subtotal);
                    printf("Low-income discount (50%%): -$%.2f\n", subtotal * 0.5);
               }
               printf("\nBill amount: $%.2f\n", bill);

               break;
          }

          case 2:{
               int consumption;
               printf("Enter the consumption in m³: ");
               scanf("%d", &consumption);

               // Define the bracket where the consumption fits in
               int bracket;
               if (consumption > 30) {
                    bracket = 1;
               } else if (consumption >= 21) {
                    bracket = 2;
               } else if (consumption >= 11) {
                    bracket = 3;
               } else if (consumption >= 1) {
                    bracket = 4;
               } else {
                    printf("Invalid consumption value. Enter a consumption value GREATER than 0!\n");
                    break;
               }

               // Calculate the bill using switch fallthrough
               switch (bracket) {
                    case 1:
                         bill = (consumption - 30) * 12.00;

                         printf("Bracket above 30: %dm³ x $12.00 = $%.2f\n", (consumption - 30), ((consumption - 30) * 12.00));

                         consumption = 30;
                    case 2:
                         bill += (consumption - 20) * 9.00;

                         printf("Bracket 21-30: %dm³ x $9.00 = $%.2f\n", (consumption - 20), ((consumption - 20) * 9.00));

                         consumption = 20;
                    case 3:
                         bill += (consumption - 10) * 7.00;

                         printf("Bracket 11-20: %dm³ x $7.00 = $%.2f\n", (consumption - 10), ((consumption - 10) * 7.00));

                         consumption = 10;
                    case 4:
                         bill += consumption * 5.00;

                         printf("Bracket 1-10: %dm³ x $5.00 = $%.2f\n", consumption, (consumption * 5.00));

                         break;
               }

               printf("\nBill amount: $%.2f\n", bill);

               break;
          }

          case 3:
               printf("---RESIDENTIAL TARIFFS/m³---\n\n");
               printf("BRACKET\t\tTARIFF\n");
               printf("1-10\t\t$3.00\n");
               printf("11-15\t\t$4.50\n");
               printf("16-20\t\t$6.00\n");
               printf("21-25\t\t$7.50\n");
               printf("26-30\t\t$9.00\n");
               printf("Above 30\t$11.00\n\n");

               printf("---COMMERCIAL TARIFFS/m³---\n\n");
               printf("BRACKET\t\tTARIFF\n");
               printf("1-10\t\t$5.00\n");
               printf("11-20\t\t$7.00\n");
               printf("21-30\t\t$9.00\n");
               printf("Above 30\t$12.00\n");

               break;

          case 4:
               printf("Closing the program...\n");
               break;

          default:
               printf("Invalid option. Choose an option between 1 and 4!\n");
               break;
     }

     return 0;
}
