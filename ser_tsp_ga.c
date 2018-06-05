#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <math.h>

// Check whether there is a logger for C
// Or define own logger with var args to printf
#define DEBUG 1

int CHROMOSOME_LENGTH; // cities number
int POPULATION_SIZE; // nb of chromosomes
int MAX_NB_GENERATIONS;

char cities_file[255];

typedef struct {
    int id;
    float x;
    float y;
} City;
City *cities;

float **distances_matrix;

typedef struct {
    // genes represent a sequence of cities, i.e. a path
    int * genes;
    float fitness;
} Chromosome;

typedef struct {
    Chromosome * population;
} Generation;

void parse_arguments(int argc, char **argv);
void init_distances_matrix();
void fill_sample_chromosome(Chromosome *ptr_chromosome);
void print_chromosome(Chromosome *ptr_chromosome);

void main(int argc, char **argv) {
    // TODO read parameters from configuration file
    POPULATION_SIZE = 1000;
    MAX_NB_GENERATIONS = 500;

    parse_arguments(argc, argv);
    init_distances_matrix();

    Chromosome sample_chromosome;
    fill_sample_chromosome(&sample_chromosome);
    print_chromosome(&sample_chromosome);
    
    getchar();
}

void parse_arguments(int argc, char **argv) {
    // can be made more elegant, namely by using getopt.h
    if (argc != 2) {
        printf("Must submit TSP locations test file name as argument.\n");
        exit(0);
    } else {
        strcpy(cities_file, argv[1]);
        printf("Given TSP locations test file is %s\n", cities_file);
    }
}

void read_cities_from_file() {
    int nb_cities;
    FILE *fp;
    int i, line;
    char buffer[1024];
    float x, y;

    fp = fopen(cities_file, "r");

    for (i = 0; i < 4; i++) {
        fgets(buffer, 1024, fp);
    }

    if (fscanf(fp, "DIMENSION : %d", &nb_cities) == 0) {
        printf("Illegal TSP locations file format. Expecting the DIMENSION at line 5.\n");
        exit(0);
    }

    CHROMOSOME_LENGTH = nb_cities;

    for (i = 0; i < 2; i++) {
        fgets(buffer, 1024, fp);
    }

    cities = (City *) malloc(sizeof (City) * nb_cities);
    rewind(fp);

    for (i = 0; i < 7; i++) {
        fgets(buffer, 1024, fp);
    }

    while (fscanf(fp, "%d %f %f", &line, &x, &y) > 0 && line <= nb_cities) {
        cities[line - 1].id = line;
        cities[line - 1].x = x;
        cities[line - 1].y = y;
#ifdef DEBUG
        printf("City %d %.4f %.4f\n", cities[line - 1].id, cities[line - 1].x, cities[line - 1].y);
#endif
    }

    fclose(fp);
}

float get_distance(City city1, City city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

void print_distances_matrix() {
    printf("\n\t");
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        printf("|%d|\t\t", i);
    }
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        printf("\n");
        printf("|%d|\t", i);
        for (int j = 0; j < CHROMOSOME_LENGTH; j++) {
            printf("d(%d,%d)=%.4f\t", i, j, distances_matrix[i][j]);
        }
    }
}

/** 
 * Initialize the distances between the cities of the given TSP file
 */
void init_distances_matrix() {
    read_cities_from_file();
    distances_matrix = malloc(sizeof (float *) * CHROMOSOME_LENGTH);
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        distances_matrix[i] = calloc(CHROMOSOME_LENGTH, sizeof (float));
    }
#ifdef DEBUG
    print_distances_matrix();
#endif
    for (int i = 0; i < CHROMOSOME_LENGTH - 1; i++) {
        for (int j = i + 1; j < CHROMOSOME_LENGTH; j++) {
            float distance = get_distance(cities[i], cities[j]);
            distances_matrix[i][j] = distances_matrix[j][i] = distance;
        }
    }
    free(cities);
#ifdef DEBUG
    print_distances_matrix();
#endif
}

void fill_sample_chromosome(Chromosome *ptr_chromosome) {
    // TODO fill it in randomly
    ptr_chromosome->genes = malloc(CHROMOSOME_LENGTH * sizeof (int));
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        ptr_chromosome->genes[i] = i + 1;
    }
    ptr_chromosome->fitness = 0.0;
}

void print_chromosome(Chromosome *ptr_chromosome) {
    printf("Fitness = %f\t, Genes = ", ptr_chromosome->fitness);
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        printf("%d_", ptr_chromosome->genes[i]);
    }
    printf("\n");
}
