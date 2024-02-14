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
    
    if (minMaxAvg(stocks, numOfDays) == 1) return 1;
    bestCase(stocks, numOfDays);

    return 0;
}

int minMaxAvg(double* stocks, int numOfDays) 
{
    double min = __DBL_MAX__; 
    double max = 0;
    int minDay = 0;
    int maxDay = 0;

    double sum = 0;
    int i = 0;
    while (scanf("%lf", &stocks[i]) > 0) 
    {
        if (stocks[i] <= 0) 
        {
            printf("ERROR: prices must be positive!\n");
            return 1;
        }
        if (stocks[i] < min) 
        {
            min = stocks[i];
            minDay = i + 1;
        }
        if (stocks[i] > max) 
        {
            max = stocks[i];
            maxDay = i + 1;
        }
        sum += stocks[i];
        i+=1;
    }

    printf("Read %i days\n", numOfDays);
    printf("Min price $%.2lf on day %i\n", min, minDay);
    printf("Max price $%.2lf on day %i\n", max, maxDay);
    printf("Avg price $%.2lf\n", sum / numOfDays);

    return 0;
}

void bestCase(double* stocks, int numOfDays) 
{
    int simulatedTradeCount = 0;
    double maxRelativeChange = 0;
    double minRelativeChange = __DBL_MAX__;
    double relativeChangeSum = 0;

    int bestBuyDay = 0;
    int bestSellDay = 0;
    int worstSellDay = 0;
    int worstBuyDay = 0;
    for (int i = 0; i < numOfDays; i++) 
    {
        for (int j = i + 1; j < numOfDays; j++) 
        {
            double relativeChange = ((stocks[j] - stocks[i]) / stocks[i]) * 100;
            if (relativeChange > maxRelativeChange) 
            {
                maxRelativeChange = relativeChange;
                bestBuyDay = i + 1;
                bestSellDay = j + 1;
            }
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
