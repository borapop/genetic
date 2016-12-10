/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: borapop
 *
 * Created on December 9, 2016, 1:50 AM
 */

#include <stdlib.h>
#include <iostream>
#include <Genetic.cpp>
#include <vector>
#include <cmath>
    std::vector<bool> generate() {
        std::vector<bool> result = {};
        for(int i = 0; i < 100000; i++) {
            if (rand() % 2 == 1) {
                result.push_back(true);
            } else {
                result.push_back(false);
            }
        }
        return result;
    }
    std::vector<bool> mutate(std::vector<bool> solution) {
        for(int i = 0; i < solution.size(); i++) {
            if (rand() % 10 == 1) {
                solution[i] = !solution[i];
            } 
        }
        return solution;
    }
    std::vector<bool> crossover(std::vector<bool> parentA, std::vector<bool> parentB) {
        std::vector<bool> child = {};
        for(int i = 0; i < parentA.size(); i++) {
            if (rand() % 2 == 1) {
                child.push_back(parentA[i]);
            } else {
                child.push_back(parentB[i]);
            }
        }
        return child;
    }
    
    std::vector<int> generateGoods(int amount, int min, int max) {
        std::vector<int> result = {};
        int value;
        for (int i = 0; i < amount; i ++) {
            value = rand() % max + min;
            //cout << value << ", ";
            result.push_back(value);
        }
        return result;
    }
    std::vector<int> goods = generateGoods(100000, 1, 1000);
    
    double fitness (std::vector<bool> solution) {
        int leftSum = 0;
        int rightSum = 0;
        int i = 0;
        for (bool s : solution) {
            if (s) {
                leftSum = leftSum + goods[i];
            } else {
                rightSum = rightSum + goods[i];
            }
            i++;
        }
        int result = std::abs(leftSum - rightSum);
        return result;
    }
    bool decideToKill(double fit) {
        if (fit > 100000) {
            return true;
        } else {
            return false;
        }
    }
    void printSolutions(std::vector<Genetic::solution<bool>> solutions) {
        double best = solutions[0].fitnessResult;
        double worst = solutions[0].fitnessResult;
        for (Genetic::solution<bool> s : solutions) {
            if (best > s.fitnessResult) {
                best = s.fitnessResult;
            }
            if (worst < s.fitnessResult) {
                worst = s.fitnessResult;
            }
        }
        cout << "best:" << best << "\n";
        cout << "worst:" << worst << "\n";
    }


int main(int argc, char** argv) {
    Genetic::Population<bool> population(100, 10, generate, mutate, crossover, fitness, decideToKill);
    population.generate();
    double best;
    for (int i = 1; i < 30; i++) {
        cout << "\nGeneration #" << i << "\n";
        
        population.mutate();
        
        population.doFitness();
        
        printSolutions(population.getSolutions());
        cout << "killed: " << population.getKilledAmount() << "\n";
        population.crossover();
        
        
        
    }
    
    return (EXIT_SUCCESS);
}

