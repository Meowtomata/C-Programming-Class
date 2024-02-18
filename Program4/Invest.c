#include <stdio.h>
#include <stdlib.h>

/*
 * Name: Anatoliy Lynevych
 * Username: alynevyc
 * Description: Program outputs investment stuff
*/
int minMaxAvg(double*, int);
void bestCase(double*, int);

int main(void) 
{
    // read first line of file
    int numOfDays = 0;
    scanf("%i", &numOfDays);

    if (numOfDays < 2) 
    {
        printf("ERROR: requires at least 2 days of data!\n");
        return 1;
    }

    double stocks[numOfDays];
    
    // minMaxAvg returns the number of Stocks initialized in array
    int numStocks = minMaxAvg(stocks, numOfDays);
    // minmaxAvg returns -1 if a stock price is 0 or negative
    if (numStocks == -1) return 1;

    bestCase(stocks, numStocks);

    return 0;
}

/*
    Calculate and otuput the min, average, and max stock price
    Populate the stocks array
    Return the number of stocks populated in array
    Return -1 if error
*/
int minMaxAvg(double* stocks, int numOfDays) 
{
    double min = __DBL_MAX__; 
    double max = 0;
    int minDay = 0;
    int maxDay = 0;

    double sum = 0;
    int i = 0;

    // scan until blank input or specified number of days reached
    while (i < numOfDays && scanf("%lf", &stocks[i]) > 0) 
    {
        if (stocks[i] <= 0) 
        {
            printf("ERROR: prices must be positive!\n");
            return -1;
        }
        // find minimum stock price and day
        if (stocks[i] < min) 
        {
            min = stocks[i];
            minDay = i + 1;
        }
        // find maximum stock price and day
        if (stocks[i] > max) 
        {
            max = stocks[i];
            maxDay = i + 1;
        }
        sum += stocks[i];
        i += 1;
    }

    printf("Read %i days\n", numOfDays);
    printf("Min price $%.2lf on day %i\n", min, minDay);
    printf("Max price $%.2lf on day %i\n", max, maxDay);
    printf("Avg price $%.2lf\n", sum / i);

    return i;
}

/*
    Calculate and output the best and worst buy and sell days
    Also find and output the average relative change between buy and sell days
*/
void bestCase(double* stocks, int numStocks) 
{
    int simulatedTradeCount = 0;
    double maxRelativeChange = 0;
    double minRelativeChange = __DBL_MAX__;
    double relativeChangeSum = 0;

    int bestBuyDay = 0;
    int bestSellDay = 0;
    int worstSellDay = 0;
    int worstBuyDay = 0;
    // starting at some buy day, go through each proceeding stock to find sell day
    for (int i = 0; i < numStocks; i++) 
    {
        for (int j = i + 1; j < numStocks; j++) 
        {
            double relativeChange = ((stocks[j] - stocks[i]) / stocks[i]) * 100;
            // find best buy and sell day
            if (relativeChange > maxRelativeChange) 
            {
                maxRelativeChange = relativeChange;
                bestBuyDay = i + 1;
                bestSellDay = j + 1;
            }
            // find worst buy and sell day
            if (relativeChange < minRelativeChange) 
            {
                minRelativeChange = relativeChange;
                worstBuyDay = i + 1;
                worstSellDay = j + 1;
            }
            relativeChangeSum += relativeChange;
            simulatedTradeCount++;
        }
    }

    printf("Simulated %i possible trades\n", simulatedTradeCount);
    printf("Average case, %.2f%%\n", relativeChangeSum / simulatedTradeCount);
    printf("Best case, buy day %i, sell day %i, %.2f%%\n", bestBuyDay, bestSellDay, maxRelativeChange);
    printf("Worst case, buy day %i, sell day %i, %.2f%%\n", worstBuyDay, worstSellDay, minRelativeChange);
}
