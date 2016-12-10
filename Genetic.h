/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Genetic.h
 * Author: borapop
 *
 * Created on December 9, 2016, 1:32 AM
 */

#ifndef GENETIC_H
#define GENETIC_H



#endif /* GENETIC_H */
#include <functional>
#include <vector>

namespace Genetic
{
    template <typename T>
    struct solution {
        std::vector<T> chromosomes;
        int age;
        double fitnessResult;
        bool killed;
    };
    
    template <typename T>
    class Population {
        public:
            Population(
                    int populationSize,
                    int maxAge,
                    std::function<std::vector<T>()> generateChromosomes,
                    std::function<std::vector<T>(std::vector<T>)> mutate,
                    std::function<std::vector<T>(std::vector<T>, std::vector<T>)> crossover,
                    std::function<double(std::vector<T>)> fitness,
                    std::function<bool(double)> decide
                    );
            std::vector<solution<T>> getSolutions();
            int getKilledAmount();
            void generate();
            bool mutate();
            bool crossover();
            double doFitness();
    private:
        static std::function<std::vector<T>()> GenerateChromosomes;
        static std::function<std::vector<T>(std::vector<T>)> Mutate;
        static std::function<std::vector<T>(std::vector<T>, std::vector<T>)> Crossover;
        static std::function<double(std::vector<T>)> Fitness;
        static std::function<bool(double)> Decide;
        static int PopulationSize;
        static int MaxAge;
        static std::vector<solution<T>> Solutions;
    };
}