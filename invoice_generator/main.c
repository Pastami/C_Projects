#include <stdio.h>

int main(void)
{
     int customerCode;

     int productCode1, productCode2, productCode3, quantity1, quantity2, quantity3;

     float price1, price2, price3;

     int month, day, year, hours, minutes;

     printf("=================================\n");
     printf("        INVOICE GENERATOR        \n");
     printf("=================================\n\n");

     printf("Enter customer code: ");
     scanf("%d", &customerCode);

     printf("\nEnter product code, unit price and quantity for item 1: ");
     scanf("%d %f %d", &productCode1, &price1, &quantity1);
     printf("Enter product code, unit price and quantity for item 2: ");
     scanf("%d %f %d", &productCode2, &price2, &quantity2);
     printf("Enter product code, unit price and quantity for item 3: ");
     scanf("%d %f %d", &productCode3, &price3, &quantity3);

     printf("\nEnter purchase date (mm/dd/yyyy): ");
     scanf("%d/%d/%d", &month, &day, &year);
     printf("Enter purchase time (hh:mm): ");
     scanf("%d:%d", &hours, &minutes);

     printf("\n---INVOICE---\n");
     printf("Customer: %.4d\n", customerCode);
     printf("Date: %.2d/%.2d/%.4d   Time: %.2d:%.2d\n\n", month, day, year, hours, minutes);

     float subtotal1 = price1 * quantity1;//
     float subtotal2 = price2 * quantity2;// Calculates the subtotal of each item.
     float subtotal3 = price3 * quantity3;//

     printf("Item\tUnit Price\tQty\tSubtotal\n");
     printf("%4d\t%10.2f\t%3d\t%8.2f\n", productCode1, price1, quantity1, subtotal1);
     printf("%4d\t%10.2f\t%3d\t%8.2f\n", productCode2, price2, quantity2, subtotal2);
     printf("%4d\t%10.2f\t%3d\t%8.2f\n\n", productCode3, price3, quantity3, subtotal3);

     float sumSubtotal = subtotal1 + subtotal2 + subtotal3;
     //Sums all three subtotals.
     float tax = sumSubtotal * 10.0 / 100.0f;
     //Calculates the value on 10% tax based on the subtotal.
     float total = sumSubtotal + tax;

     printf("Subtotal:\t\t\t%8.2f\n", sumSubtotal);
     printf("Tax (10%%):\t\t\t%8.2f\n", tax);
     printf("----------------------------------------\n");
     printf("TOTAL:\t\t\t\t%8.2f\n",total);

     return 0;
}
