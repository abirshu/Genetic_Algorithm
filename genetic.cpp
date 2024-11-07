/*
Abir hasan
Netrokona University
11 November 2024
  */
#include <bits/stdc++.h>
using namespace std;
#define POPULATION_SIZE 100
// Valid Genes
const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP"
                     "QRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";

// Target string to be generated
string TARGET;
// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
    int len = GENES.size();
    int r = random_num(0, len - 1);
    return GENES[r];
}

// Create chromosome or string of genes
string create_gnome()
{
    int len = TARGET.size();
    string gnome = "";
    for (int i = 0; i < len; i++)
    {
        gnome += mutated_genes();
    }
    return gnome;
}
// Class representing individual in population
class Individual
{
public:
    string chromosome;
    int fitness;
    Individual(string chromosome);
    Individual mate(Individual parent2);
    int cal_fitness();
};

Individual::Individual(string chromosome)
{
    //this-> use When local variable’s name is same as member’s name
    this->chromosome = chromosome;
    fitness = cal_fitness();
}

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2)
{
    // Chromosome for offspring
    string child_chromosome = "";

    int len = chromosome.size();
    for (int i = 0; i < len; i++)
    {
        // Random probability
        float p = random_num(0, 100) / 100.0;

        // If prob is less than 0.45, insert gene from parent 1
        if (p < 0.45)
            child_chromosome += chromosome[i];
        // If prob is between 0.45 and 0.90, insert gene from parent 2
        else if (p < 0.90)
            child_chromosome += par2.chromosome[i];
        // Otherwise insert random gene (mutate), for maintaining diversity
        else
            child_chromosome += mutated_genes();
    }

    // Create new Individual (offspring) using generated chromosome
    return Individual(child_chromosome);
}

// Calculate fitness score, it is the number of characters in the string
// that differ from the target string.
int Individual::cal_fitness()
{
    int len = TARGET.size();
    int fitness = 0;
    for (int i = 0; i < len; i++)
    {
        if (chromosome[i] != TARGET[i])
        {
             fitness++;
        }
    }
    return fitness;
}

// Overloading < operator for sorting individuals by fitness
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}

// Driver code
int main()
{
    cout << "Enter target string: ";
    getline(cin, TARGET);

    //srand() initializes the random number generator with the given seed.
    srand((unsigned)(time(0)));

    // Current generation
    int generation = 1;
    vector<Individual> population;
    bool found = false;

    // Create initial population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        string gnome = create_gnome();
        population.push_back(Individual(gnome));
    }

    while (!found)
    {
        // Sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        // If the individual with lowest fitness score is 0, target is reached
        if (population[0].fitness <= 0)
        {
            found = true;
            break;
        }

        // Otherwise, generate new offspring for the next generation
        vector<Individual> new_generation;

        // Perform elitism: 10% of the fittest population goes to the next generation
        int s = (10 * POPULATION_SIZE) / 100;
        for (int i = 0; i < s; i++)
            new_generation.push_back(population[i]);

        // From the 50% of the fittest population, individuals will mate to produce offspring
        s = (90 * POPULATION_SIZE) / 100;
        for (int i = 0; i < s; i++)
        {
            int len = population.size();
            int r = random_num(0, 50);
            Individual parent1 = population[r];
            r = random_num(0, 50);
            Individual parent2 = population[r];
            Individual offspring = parent1.mate(parent2);
            new_generation.push_back(offspring);
        }
        population = new_generation;

        cout << "Generation: " << generation << "\t";
        cout << "String: " << population[0].chromosome << "\t";
        cout << "Fitness: " << population[0].fitness << "\n";

        generation++;
    }
    cout << "Generation: " << generation << "\t";
    cout << "String: " << population[0].chromosome << "\t";
    cout << "Fitness: " << population[0].fitness << "\n";
    cout<<endl<<"Reached target value";
}
