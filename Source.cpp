
#include <vector>
#include <stdio.h>
#include <iostream>
using namespace std;

class Chromosome {
public:
	Chromosome() {
		value = rand() % 2;
	}

	Chromosome(bool chromosomeValue) {
		value = chromosomeValue;
	}

	void mutate() {
		value = rand() % 2;
	}

	bool getValue() {
		return value;
	}

private:
	bool value;

};

class Species {
public:
	Species(int chromosomeAmount) {
		for (int i = 0; i < chromosomeAmount; i++) {
			Chromosome chromosome;
			Chromosomes.push_back(chromosome);
		}
	}
	Species(vector<Chromosome> chromosomes) {
		for (int i = 0; i < chromosomes.size(); i++) {
			Chromosomes.push_back(chromosomes[i]);
		}
	}
	Species(Species parentA, Species parentB) {
		vector<Chromosome> chromosomesA = parentA.getChromosomes();
		vector<Chromosome> chromosomesB = parentB.getChromosomes();
		vector<Chromosome> childChromosomes;
		bool temp;
		// TODO: check vectors lengths;
		for (int i = 0; i < chromosomesA.size(); i++) {
			if (rand() % 2 == 0) {
				temp = true;
			}
			else {
				temp = false;
			}
			Chromosome childChromosome(temp);
			Chromosomes.push_back(childChromosome);
		}
	}
	void mutate(int fraction) {
		for (Chromosome chromosome : Chromosomes) {
			if (rand() % fraction == 0) {
				chromosome.mutate();
			}
		}
	}
	vector<Chromosome> getChromosomes() {
		return Chromosomes;
	}
	void setAge(int age) {
		Age = age;
	}
	int getAge() {
		return Age;
	}
	void grow() {
		Age++;
	}
private:
	vector<Chromosome> Chromosomes;
	int Age;
};

class Population {
public:
	Population(int speciemensAmount, int chromosomeAmount, int maxAge) {
		ChromosomeAmount = chromosomeAmount;
		Amount = speciemensAmount;
		MaxAge = maxAge;
		for (int i = 0; i < speciemensAmount; i++) {
			Species species(chromosomeAmount);
			Speciemens.push_back(species);
		}
	}
	void select(int(*fitness)(vector<Species>)) {
		int best = fitness(Speciemens);
		for (int i = 0; i < Speciemens.size(); i++) {
			if (i != best) {
				Speciemens.erase(Speciemens.begin() + i);
			}
			else {

				Speciemens[i].grow();
				if (Speciemens[i].getAge() > MaxAge) {
					Speciemens.erase(Speciemens.begin() + i);
				}
			}
		}
	}
	void mutate(int fraction) {
		for (int i = 0; i < Speciemens.size(); i++) {
			Speciemens[i].mutate(fraction);
		}
	}
	void crossover() {
		int indexA, indexB;
		int speciemensAmount = Speciemens.size();
		while (Speciemens.size() < Amount) {


			indexA = rand() % speciemensAmount;

			indexB = indexA;

			while (indexA == indexB) {
				indexB = rand() % speciemensAmount;
			}

			Species speciemen(Speciemens[indexA], Speciemens[indexB]);
			Speciemens.push_back(speciemen);
		}
	}
	void show() {
		for (int i = 0; i < Speciemens.size(); i++) {
			for (int j = 0; j < ChromosomeAmount; j++) {
				bool chromosome = Speciemens[i].getChromosomes()[j].getValue();
				cout << chromosome;
			}
			cout << endl;
		}
		cout << endl;
	}

private:
	vector<Species> Speciemens;
	int MaxAge;
	int Amount;
	int ChromosomeAmount;
};

vector<int> Goods;
void generateGoods() {
	for (int i = 0; i < 1000; i++) {
		int value = rand() % 1000;
		cout << value << " ";
		Goods.push_back(value);
	}
}

int fitness(vector<Species> species) {

	int Sum = 0;
	for (int i = 0; i < sizeof(Goods) / sizeof(Goods[0]); i++) {
		Sum += Goods[i];
	}
	int sum;
	int best = Sum;
	int indexBest = 0;
	int prevSum = 0;

	for (int i = 0; i < species.size(); i++) {

		sum = 0;
		for (int j = 0; j < species[i].getChromosomes().size(); j++) {



			if (species[i].getChromosomes()[j].getValue()) {
				sum += Goods[i];
			}
		}

		if (abs(Sum - sum) < best) {
			best = abs(Sum - sum);
			indexBest = i;
		}
	}
	cout << endl << "best: " << best << endl;
	return indexBest;
}

void genetic(Population population, int N, int fraction) {
	for (int i = 0; i < N; i++) {

		cout << " " << i << ": ";
		population.select(*fitness);
		population.crossover();
		population.mutate(fraction);
	}
}

int main() {

	generateGoods();
	Population population(100, 100, 5);

	genetic(population, 1000, 1);


	int ex;
	cin >> ex;
	return 0;
}

