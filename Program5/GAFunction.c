#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getBestFitIndex(int *fitness, int fitnessSize);
int getWorstFitIndex(int *fitness, int fitnessSize);
double getAvgFitness(int *fitness, int fitnessSize);
void printGeneration(FILE* outfp, int **population, int*fitness, int P, int N, int generation);


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


    // initialize and store population and fitness values
    int population[P][N];
    int fitness[P];

    for (int i = 0; i < P; i++) 
    {
        int fitnessSum = 0;
        for (int j = 0; j < N; j++)
        {   
            // store a random value [0-9] as a gene in some individual in population
            int value = rand() % 10;
            population[i][j] = value;
            fitnessSum += value * weights[j];
        }
        // calculate fitness
        fitness[i] = abs(fitnessSum - C);
    }

    // check if output file provided (6th optional argument)
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

    int generation = 0;
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

        generation = step;
        if (outfp != NULL)
        {
            printGeneration(outfp, population, fitness, P, N, step);
        }
        
        // Mutation: replace genes of the worst individual in the population with mutated individual
        int worstFitIndex = getWorstFitIndex(fitness, P);
        int sum = 0;
        for (int i = 0; i < N; i++)
        {   
            population[worstFitIndex][i] = mutatedIndividual[i];
            sum += population[worstFitIndex][i] * weights[i];
        }
        fitness[worstFitIndex] = abs(sum - C);

        if (outfp != NULL)
        {
            fprintf(outfp, "Mutated individual %d -> %d, changed gene %d to %d\n", randomIndividual, worstFitIndex, randomGene, newGeneValue);
        }
        if (fitness[worstFitIndex] == 0)
        {
            break;
        }
    }

    // print the final mutated generation to output file
    if (outfp != NULL)
    {
        printGeneration(outfp, population, fitness, P, N, generation + 1);
        fclose(outfp);
    }

    // print BEST: (Index with best fitness), fitness= ..., steps= ...
    int bestFitIndex = getBestFitIndex(fitness, P);
    printf("BEST %d: ", bestFitIndex);
    for (int i = 0; i < N; i++)
    {
        printf("%d", population[bestFitIndex][i]);
    }
    printf(", fitness=%d, steps=%d\n", fitness[bestFitIndex], generation + 1);

    fclose(fp);
    return 0;
} 

int getBestFitIndex(int *fitness, int fitnessSize)
{
    // find best fit index
    int bestFitIndex = 0;
    for (int i = 1; i < fitnessSize; i++)
    {
        if (fitness[i] < fitness[bestFitIndex])
        {
            bestFitIndex = i;
        }
    }
    return bestFitIndex;
}

int getWorstFitIndex(int *fitness, int fitnessSize)
{
    int worstFitnessIndex = 0;
    for (int i = 1; i < fitnessSize; i++) 
    {
        if (fitness[i] > fitness[worstFitnessIndex])
        {
            worstFitnessIndex = i;
        }
    }

    return worstFitnessIndex;
}

double getAvgFitness(int *fitness, int fitnessSize)
{
    double fitnessSum = fitness[0];
    for (int i = 1; i < fitnessSize; i++) 
    {
        fitnessSum += fitness[i];
    }

    return fitnessSum / fitnessSize;
}

void printGeneration(FILE* outfp, int **population, int*fitness, int P, int N, int generation)
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

    // find worst and sum of fitnesses to output avg and min fitness
    int worstFitIndex = getWorstFitIndex(fitness, P);
    int bestFitIndex = getBestFitIndex(fitness, P);
    double avgFit = getAvgFitness(fitness, P);

    int bestFit = fitness[bestFitIndex];
    int worstFit = fitness[worstFitIndex];

    fprintf(outfp, "avg=%.4f, min=%d, max=%d\n", avgFit, bestFit, worstFit);
}
