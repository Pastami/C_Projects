#include <stdio.h>

int main(void)
{
     float distance, fuelEfficiency, fuelPrice;
     int days;

     printf("============================================\n");
     printf("           CONSUMPTION CALCULATOR           \n");
     printf("============================================\n\n");

     printf("Enter total trip distance (km): ");
     scanf("%f", &distance);
     printf("Enter car fuel efficiency (km/liter): ");
     scanf("%f", &fuelEfficiency);
     printf("Enter fuel price per liter: ");
     scanf("%f", &fuelPrice);
     printf("Enter number of trip days: ");
     scanf("%d", &days);

     float fuelSpent = distance / fuelEfficiency; // Calculate the total of liters spent on the trip
     float fuelCost = fuelPrice * fuelSpent; // Calculate the total cost of the fuel
     float averageDailyCost = fuelCost / days; // Calculate the average fuel cost per day
     float averageDailyKm = distance / days; // Calculate the average km driven per day

     printf("\n---Trip Summary---\n\n");
     printf("Fuel needed (liters): %f\n", fuelSpent);
     printf("Total fuel cost: %f\n", fuelCost);
     printf("Average cost per day: %f\n", averageDailyCost);
     printf("Average km per day: %f\n", averageDailyKm);

     return 0;
}
