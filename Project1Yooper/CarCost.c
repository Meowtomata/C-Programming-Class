#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc < 7)
    {
        printf("Usage: CarCost <name> <cost> <mpg> <gas price> <repair every> <total miles>");
    }


    char* vehicleName = argv[1]; 
    double vehicleCost = atof(argv[2]);
    double mpg = atof(argv[3]);
    double gasPrice = atof(argv[4]);
    int repairEvery = atoi(argv[5]);
    int totalMiles = atoi(argv[6]);

    if (vehicleCost < 0 || mpg < 0 || gasPrice < 0 || repairEvery < 0 || totalMiles < 0)
    {
        printf("ERROR: invalid input!\n");
        return 1;
    }

    double gallonsBurned = totalMiles / mpg;
    double gallonsCost = gasPrice * gallonsBurned;

    double timesRepaired = totalMiles / repairEvery;
    double repairCost = timesRepaired * 500;

    double ownershipCost = gallonsCost + repairCost + vehicleCost;
    double costPerMile = ownershipCost / totalMiles;

    printf("Buying %s for $%2.f getting %.1f mpg\n", vehicleName, vehicleCost, mpg);
    printf("Driving %d miles @ $%.2f/gallon\n", totalMiles, gasPrice);
    printf("Burned %1.f gallons costing $%.2f\n", gallonsBurned, gallonsCost);
    printf("Repaired %1.f times costing $%.2f\n", timesRepaired, repairCost);
    printf("Total cost of ownership: $%.2f\n", ownershipCost);
    printf("Cost per mile: $%.2f\n", costPerMile);

    return 0;
}
