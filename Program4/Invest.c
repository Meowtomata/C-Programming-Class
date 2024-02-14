#include <stdio.h>
#include <stdlib.h>

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
    printf("Average price $%.2lf\n", sum / numOfDays);

    return 0;
}
