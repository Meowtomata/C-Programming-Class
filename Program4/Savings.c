#include <stdio.h>
#include <stdlib.h>

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

    // depositing a negative amount is not allowed
    if (initialAmount < 0) 
    {
        printf("ERROR: amount must be positive!\n");
    }

    // starting information
    printf("Deposited $%.2f into %s\n", initialAmount, account);
    
    float interest = 0;
    float finalAmount = initialAmount;

    // print interest and amount over time
    for (int i = 1; i <= months; i++) 
    {
        interest = finalAmount * rate / 100 / 12;
        finalAmount += interest;
        printf("Month %i, %.2f change, new total $%.2f\n", i, interest, finalAmount);
    }

    // print final relative change
    float relativeChange = ((finalAmount - initialAmount) / initialAmount) * 100;
    printf("Relative change: %.2f%%", relativeChange);
    
    return 0;
}
