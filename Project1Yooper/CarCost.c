#include <stdio.h>
#include <stdlib.h>

/*
* Name: Anatoliy Lynevych
* Username: alynevyc
* Description: 
* Program CarCost
*/
int main(int argc, char** argv)
{
    if (argc < 7)
    {
        printf("Usage: CarCost <name> <cost> <mpg> <gas price> <repair every> <total miles>");
        return 1;
    }

    char* vehicleName = argv[1]; 
    double vehicleCost = atof(argv[2]);
    double mpg = atof(argv[3]);
    double gasPrice = atof(argv[4]);
    int repairEvery = atoi(argv[5]);
    int totalMiles = atoi(argv[6]);

    // values must be positive integer
    if (vehicleCost <= 0 || mpg <= 0 || gasPrice <= 0 || repairEvery <= 0 || totalMiles <= 0)
    {
        printf("ERROR: invalid input!\n");
        return 1;
    }

    // determine values for Burned x gallons costing $x
    double gallonsBurned = totalMiles / mpg;
    double gallonsCost = gasPrice * gallonsBurned;

    // determine values for repaired x times costing $x
    double timesRepaired = totalMiles / repairEvery * 1.0;
    double repairCost = timesRepaired * 500;

    // determine values for Total cost of ownership: $x and Cost per mile: $x
    double ownershipCost = gallonsCost + repairCost + vehicleCost;
    double costPerMile = ownershipCost / totalMiles;

    printf("Buying %s for $%1.f getting %.1f mpg\n", vehicleName, vehicleCost, mpg);
    printf("Driving %d miles @ $%.2f/gallon\n", totalMiles, gasPrice);
    printf("Burned %1.f gallons costing $%.2f\n", gallonsBurned, gallonsCost);
    printf("Repaired %1.f times costing $%.2f\n", timesRepaired, repairCost);
    printf("Total cost of ownership: $%.2f\n", ownershipCost);
    printf("Cost per mile: $%.2f\n", costPerMile);

    return 0;
}
