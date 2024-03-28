#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* Name: Anatoliy Lynevych
* Username: alynevyc
* Description: Program 5 implements a genetic algorithm and outputs the 
*   best solution for a linear equation after some number of steps or
*   if the solution is perfect
*/
int main(int argc, char** argv) 
{

    // 5 arguments are enough to run the program
    if (argc < 5) 
    {
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
        printf("%d*x_%d", weights[i], i);
        if (i < N - 1)
        {
            printf(" + ");
        }
    }
    printf(" = %d\n", C);


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

    FILE * outfp = NULL;
    if (argc > 5) 
    {
        char* outFile = argv[5];
        outfp = fopen(outFile, "w");
        if (outfp == NULL)
        {
            printf("ERROR: failed to open log file!\n");
            return 1;
        }
    }

    // keep track of generation to be used outside of loop
    int generation = 0;
    for (int step = 0; step < maxSteps; step++)
    {   
        int mutatedIndividual[N];
        
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

        // used for finding min in generation output file
        // used for mutating worst fit individual with mutated individual
        int worstFitnessIndex = 0;
        for (int i = 1; i < P; i++) 
        {
            if (fitness[i] > fitness[worstFitnessIndex])
            {
                worstFitnessIndex = i;
            }
        }

        if (outfp != NULL)
        {
            fprintf(outfp, "*** Generation %d ***\n", step);
            // print however many individuals there are with their genes
            for (int i = 0; i < P; i++)
            {
                // print the index
                fprintf(outfp, "%d: ", i);
                // print each of the gene values in sequential order
                for (int j = 0; j < N; j++)
                {
                    fprintf(outfp, "%d", population[i][j]);
                }
                fprintf(outfp, ", fitness=%d\n", fitness[i]);
            }

            int bestFit = fitness[0];
            double fitnessSum = fitness[0];
            for (int i = 1; i < P; i++) 
            {
                if (fitness[i] < bestFit)
                {
                    bestFit = fitness[i];
                }
                fitnessSum += fitness[i];
            }
            fprintf(outfp, "avg=%.4f, min=%d, max=%d\n", fitnessSum / P, bestFit, fitness[worstFitnessIndex]);
        }


        // sum to calculate fitness of newly mutated individual
        int sum = 0;
        // Mutation: replace genes of individual with worst fitness with mutated individual
        for (int i = 0; i < N; i++)
        {   
            population[worstFitnessIndex][i] = mutatedIndividual[i];
            sum += population[worstFitnessIndex][i] * weights[i];
        }
        fitness[worstFitnessIndex] = abs(sum - C);

        // keep track of generation outside of current loop
        generation = step + 1;

        // output gene changes to output file if there is one
        if (outfp != NULL)
        {
            fprintf(outfp, "Mutated individual %d -> %d, changed gene %d to %d\n", randomIndividual, worstFitnessIndex, randomGene, newGeneValue);
        }

        // stop loop early if individual with best fitness found
        if (fitness[worstFitnessIndex] == 0)
        {
            break;
        }
    }

    // get index of individual with best fitness
    // used to print max fitness in output file
    // used to print best fitness in console
    int bestFitIndex = 0;
    for (int i = 1; i < P; i++)
    {
        if (fitness[i] < fitness[bestFitIndex])
        {
            bestFitIndex = i;
        }
    }

    if (outfp != NULL)
    {
        fprintf(outfp, "*** Generation %d ***\n", generation);
        // print however many individuals there are with their genes
        for (int i = 0; i < P; i++)
        {
            // print the index
            fprintf(outfp, "%d: ", i);
            // print each of the gene values in sequential order
            for (int j = 0; j < N; j++)
            {
                fprintf(outfp, "%d", population[i][j]);
            }
            fprintf(outfp, ", fitness=%d\n", fitness[i]);
        }

        // get index of individual with worst fitness
        int worstFit = fitness[0];
        double fitnessSum = fitness[0];
        for (int i = 1; i < P; i++) 
        {
            if (fitness[i] > worstFit)
            {
                worstFit = fitness[i];
            }
            fitnessSum += fitness[i];
        }
        fprintf(outfp, "avg=%.4f, min=%d, max=%d\n", fitnessSum / P, fitness[bestFitIndex], worstFit);

        // close file to prevent memory leak
        fclose(outfp);
    }

    // print BEST (index of best fit individual), fitness=..., steps=...
    printf("BEST %d: ", bestFitIndex);
    for (int i = 0; i < N; i++)
    {
        printf("%d", population[bestFitIndex][i]);
    }
    printf(", fitness=%d, steps=%d\n", fitness[bestFitIndex], generation);

    // close file to prevent memory leak
    fclose(fp);
    return 0;
} 
