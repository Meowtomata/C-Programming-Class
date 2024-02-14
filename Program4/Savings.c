#include <stdio.h>
#include <stdlib.h>

/*
 * Name: Anatoliy Lynevych
 * Username: alynevyc
 * Description: Program outputs savings stuff
*/
int main(int argc, char** argv) 
{
    // check if there are enough arguments
    if (argc < 5) 
    {
        printf("Usage: Savings <account> <amount> <rate> <months>");
        return 1;
    }

    // initialize variables using command line arguments
    char* account = argv[1];
    float initialAmount = atof(argv[2]);
    float rate = atof(argv[3]);
    int months = atoi(argv[4]);

    // only positive amounts allowed
    if (initialAmount <= 0) 
    {
        printf("ERROR: amount must be positive!\n");
        return 1;
    }

    // starting information
    printf("Deposited $%.2f into %s\n", initialAmount, account);
    
    double interest = 0;
    double finalAmount = initialAmount;

    // print interest and amount over time
    for (int i = 1; i <= months; i++) 
    {
        interest = finalAmount * rate / 100 / 12;
        finalAmount += interest;
        printf("Month %i, $%.2f change, new total $%.2f\n", i, interest, finalAmount);
    }

    // print final relative change
    float relativeChange = ((finalAmount - initialAmount) / initialAmount) * 100;
    printf("Relative change: %.2f%%", relativeChange);
    
    return 0;
}
