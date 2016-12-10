#include "Genetic.h"
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

namespace Genetic {
    template<typename T>
    Population<T>::Population(
            int populationSize,
            int maxAge,
            std::function<std::vector<T>()> generateChromosomes,
            std::function<std::vector<T>(std::vector<T>)> mutate,
            std::function<std::vector<T>(std::vector<T>, std::vector<T>)> crossover,
            std::function<double(std::vector<T>)> fitness,
            std::function<bool(double)> decide
            
    )
    {
        PopulationSize = populationSize;
        MaxAge = maxAge;
        GenerateChromosomes = generateChromosomes;
        Mutate = mutate;
        Crossover = crossover;
        Fitness = fitness;
        Decide = decide;
    }
    
    template<typename T>        
    int Population<T>::getKilledAmount() {
        int result = 0;
        for (solution<T> s : Solutions) {
            if (s.killed) {
                result++;
            }
        }
        return result;
    }
    
    template<typename T>    
    std::vector<solution<T>> Population<T>::getSolutions() {
        return Solutions;
    }
    
    template<typename T>    
    void Population<T>::generate() {
        for (int i; i < PopulationSize; i++) {
            solution<T> s;
            s.chromosomes = GenerateChromosomes();
            s.age = 0;
            s.killed = false;
            Solutions.push_back(s);
        }
    }
    
    template<typename T>
    bool Population<T>::mutate() {
        for (int i = 0; i < Solutions.size(); i++) {
            Solutions[i].chromosomes = Mutate(Solutions[i].chromosomes);
            Solutions[i].age++;
        }
        return true;
    }
    
    template<typename T>
    bool Population<T>::crossover() {
        std::vector<solution<T>> NewSolutions = {};
        for (solution<T> s : Solutions) {
            if (!s.killed) {
                NewSolutions.push_back(s);
            }
        }
        int parentsBorder = NewSolutions.size();
        if (parentsBorder > 1) {
            for (int i = parentsBorder; i < PopulationSize; i++) {
                int parentAIndex = rand() % parentsBorder;
                int parentBIndex;
                for (int k = 0; k < parentsBorder; k++) {
                    parentBIndex = rand() % parentsBorder;
                    if (parentBIndex == parentAIndex) {
                        if (parentBIndex == parentsBorder) {
                            parentBIndex--;
                        }
                        if (parentBIndex == 0) {
                            parentBIndex++;
                        }
                    }
                }
                std::vector<T> chromosomes = Crossover(NewSolutions[parentAIndex].chromosomes, NewSolutions[parentBIndex].chromosomes);
                solution<T> child;
                child.chromosomes = chromosomes;
                child.age = 0;
                child.killed = false;
                NewSolutions.push_back(child);
            }
            Solutions = NewSolutions;
            return true;
        } else {
            Solutions.clear();
            for (int i; i < PopulationSize; i++) {
                solution<T> s;
                s.chromosomes = GenerateChromosomes();
                s.age = 0;
                s.killed = false;
                Solutions.push_back(s);
            }
            return false;
        }
        
    }
    
    template<typename T>
    double Population<T>::doFitness() {
        double fitnessResult;
        for (int i = 0; i < Solutions.size(); i++) {
            fitnessResult = Fitness(Solutions[i].chromosomes);
            Solutions[i].fitnessResult = fitnessResult;
            
            if (Decide(fitnessResult)) {
                Solutions[i].killed = true;
            } else if (Solutions[i].age > MaxAge) {
                Solutions[i].killed = true;
            }
        }
        return 0.0;
    }

    
    template<typename T>
    std::function<std::vector<T>()> Population<T>::GenerateChromosomes;
    
    template<typename T>
    std::function<std::vector<T>(std::vector<T>)> Population<T>::Mutate;
    
    template<typename T>
    std::function<std::vector<T>(std::vector<T>, std::vector<T>)> Population<T>::Crossover;
    
    template<typename T>
    std::function<double(std::vector<T>)> Population<T>::Fitness;
    
    template<typename T>
    std::function<bool(double)> Population<T>::Decide;
    
    template<typename T>
    std::vector<solution<T>> Population<T>::Solutions = {};
    
    template<typename T>
    int Population<T>::PopulationSize = 0;
    
    template<typename T>
    int Population<T>::MaxAge = 0;
}
