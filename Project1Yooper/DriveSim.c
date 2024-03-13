#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Name: Anatoliy Lynevych
* Username: alynevyc
* Description: 
* Program DriveSim
*/

/*
* returns whether 2D matrix is a valid distance matrix for program
*/
bool validDistanceMatrix(int size, int dist[size][size]);

int main(int argc, char** argv)
{
    if (argc < 5)
    {
        printf("Usage: DriveSim <mpg> <gas price> <max passengers> <distance file>\n");
        return 1;
    }

    double mpg = atof(argv[1]);
    double gasPrice = atof(argv[2]);
    int maxPassengers = atoi(argv[3]);
    char* distanceFile = argv[4];

    if (mpg <= 0 || gasPrice <= 0 || maxPassengers <= 0)
    {
        printf("ERROR: invalid input!\n");
        return 1;
    }

    int dimension = 0;

    FILE* fp = fopen(distanceFile, "r");

    // if file can't be opened
    if (fp == NULL)
    {
        printf("ERROR: failed to open distance file!\n");
        return 1;
    }

    // first line in file determines size of 2D matrix
    fscanf(fp, "%d", &dimension);

    // set 2D matrix to values from file
    int distances[dimension][dimension];
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            fscanf(fp, "%d", &distances[i][j]);
        }
    }

    fclose(fp);

    printf("Read %d distances from '%s'\n", dimension * dimension, distanceFile);

    // exit program if distance matrix is invalid
    if (validDistanceMatrix(dimension, distances) == false)
    {
        printf("ERROR: invalid distance matrix!\n");
        return 1;
    }

    // values to be initialized by scanf
    int pickupLocation = 0;
    int dropOffLocation = 0;
    int numberOfPassengers = 0;
    int isSurgeTrip = 0;

    // keeps track of which trip we're on
    int tripNumber = 0;

    // total values to keep track of and print outside of loop
    int totalFareMiles = 0;
    int totalTransitMiles = 0;
    double totalProfit = 0;

    int previousLocation = 0;
    
    printf("Trip #0: ");
    while (scanf("%d %d %d %d", &pickupLocation, &dropOffLocation, &numberOfPassengers, &isSurgeTrip) == 4)
    {  
        if (pickupLocation < 0 || pickupLocation >= dimension 
        || dropOffLocation < 0 || dropOffLocation >= dimension
        || dropOffLocation == pickupLocation
        || numberOfPassengers <= 0)
        {
            printf("Invalid input!\n");
        }

        // can't have more passengers than car can fit
        else if (numberOfPassengers > maxPassengers)
        {
            printf("Car too small!\n");

        }

        else {

            // determine and keep track of transit miles
            int transitMiles = distances[previousLocation][pickupLocation];
            if (tripNumber == 0) transitMiles = 0;

            // calculate fare, expense, and profit
            double fare = (5 + 0.1 * distances[pickupLocation][dropOffLocation]);
            if (isSurgeTrip != 0)
            {
                fare *= 1.5;
            }
            double expense = distances[pickupLocation][dropOffLocation] / mpg * gasPrice;
            // add the cost of transmit miles to expenses
            expense += transitMiles / mpg * gasPrice;
            double profit = fare - expense;
            
            // keep track of total values to be printed outside of loop
            totalFareMiles += distances[pickupLocation][dropOffLocation];
            totalTransitMiles += transitMiles;
            totalProfit += profit;

            printf("%d -> %d, transit %d, trip %d, fare $%.2f, profit $%.2f\n", 
            pickupLocation, dropOffLocation, transitMiles, distances[pickupLocation][dropOffLocation], fare, profit);

            // keep track of where we parked to determine transit miles for nex trip
            previousLocation = dropOffLocation;
        }

        tripNumber++;
        printf("Trip #%d: ", tripNumber);
    }
    printf("\n");

    printf("Total fare miles %d\n", totalFareMiles);
    printf("Total transit miles %d\n", totalTransitMiles);
    printf("Total profit $%.2f\n", totalProfit);


    return 0;
}

/*
* returns whether 2D matrix is a valid distance matrix for program
*/
bool validDistanceMatrix(int size, int dist[size][size])
{
    // matrix is invalid if smaller than 2x2
    if (size < 2)
    {
        return false;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // matrix is invalid if it is not symmetric
            if (dist[i][j] != dist[j][i])
            {
                return false;
            }

            // distances between different locations are 1+ miles
            if (j != i && dist[i][j] == 0)
            {
                return false;
            }

            // distance between location and itself must be 0
            if (i == j && dist[i][j] != 0)
            {
                return false;
            }
        }
    }

    // matrix is valid
    return true;
}
