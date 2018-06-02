#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <math.h>

int CHROMOSOME_LENGTH; // cities number
int POPULATION_SIZE; // nb of chromosomes
int MAX_NB_GENERATIONS;

// genese represent a sequence cities or path
typedef struct {
	int * genes; 
	float fitness;
} Chromosome;
typedef struct {
	Chromosome * population;
} Generation;

Chromosome get_sample_chromosome();
void print_chromosome(Chromosome c);

void main()
{
	CHROMOSOME_LENGTH = 29;
	POPULATION_SIZE = 1000; 
	MAX_NB_GENERATIONS = 500;
	
	Chromosome sample_individual = get_sample_chromosome();
	print_chromosome(sample_individual);
}

Chromosome get_sample_chromosome()
{
	Chromosome sample_individual;
	sample_individual.genes = malloc(CHROMOSOME_LENGTH * sizeof (int));
	for(int i=0; i<CHROMOSOME_LENGTH; i++)
	{
		sample_individual.genes[i] = i + 1;
	}
	sample_individual.fitness = 0.0;
	return sample_individual;
}

void print_chromosome(Chromosome c)
{
	printf("Fitness = %f\t, Genese = ",c.fitness);
	for(int i=0; i<CHROMOSOME_LENGTH; i++)
	{
		printf("%d_",c.genes[i]);
	}
	printf("\n");
}