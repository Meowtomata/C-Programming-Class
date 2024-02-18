#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) 
{

    if (argc < 5) 
    {
        // is it bad to put \n at end of error messages
        // is it bad to return 1?
        printf("Usage: GA <individuals> <max steps> <seed> <in file> [out file]\n");
        return 1;
    }

    int P = atoi(argv[1]);
    int maxSteps = atoi(argv[2]);
    int seed = atoi(argv[3]);
    char* inFile = argv[4];

    srand(seed);

    if (P <= 0) 
    {
        printf("ERROR: individuals must be positive!\n");
        return 1;
    }

    FILE * fp = fopen(inFile, "r");
    if (fp == NULL) 
    {
        printf("ERROR: failed to open in file!\n");
        return 1;
    }

    // iniitalize N & C values
    int C = 0;
    int N = 0;
    fscanf(fp, "%d", &C);
    fscanf(fp, "%d", &N);

    // initialize and print out weights (i.e. a0, a1, ..., aN-1)
    int weights[N];
    for (int i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &weights[i]);
        printf("%d+x_%d ", weights[i], i);
    }
    printf("= %d\n", C);


    // initialize population and initial fitness values
    int population[P][N];
    int fitness[P];

    for (int i = 0; i < P; i++) 
    {
        int fitnessSum = 0;
        for (int j = 0; j < N; j++)
        {
            int value = rand() % 10;
            population[i][j] = value;
            fitnessSum += value * weights[j];
        }
        // calculate fitness
        fitness[i] = abs(fitnessSum - C);
    }


    int mutatedIndividual[N];
    for (int step = 0; step < maxSteps; step++)
    {
        // select the first individual from the population at random
        int randomIndividual = rand() % P;

        // create a duplicate individual to mutate
        
        for (int i = 0; i < N; i++) 
        {
            mutatedIndividual[i] = population[randomIndividual][i];
        }

        // select a random gene & new gene value
        int randomGene = rand() % N;
        int newGeneValue = rand() % 10;

        // update gene
        mutatedIndividual[randomGene] = newGeneValue;


        // replace worst individual with mutated
        int worstFitnessIndex = 0;
        for (int i = 1; i < P; i++) 
        {
            if (fitness[i] > fitness[worstFitnessIndex])
            {
                worstFitnessIndex = i;
            }
        }

        // replace genes of teh worst individual in the population with
        // mutated individual (im guessing through fitness)
        int sum = 0;
        for (int i = 0; i < N; i++)
        {   
            population[worstFitnessIndex][i] = mutatedIndividual[i];
            sum += population[worstFitnessIndex][i] * weights[i];
        }
        fitness[worstFitnessIndex] = abs(sum - C);

        if (fitness[worstFitnessIndex] == 0)
        {
            break;
        }

    }


    int bestFitIndex = 0;
    for (int i = 1; i < P; i++)
    {
        if (fitness[i] < fitness[bestFitIndex])
        {
            bestFitIndex = i;
        }
    }
    
    printf("BEST %d: ", bestFitIndex);
    for (int i = 0; i < N; i++)
    {
        printf("%d", population[bestFitIndex][i]);
    }
    printf(", fitness=%d, steps=%d", fitness[bestFitIndex], maxSteps);


    fclose(fp);
    return 0;
} 
