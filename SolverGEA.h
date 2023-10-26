#pragma once
#include <vector>
#include "KnapsackProblem.h"
#include "gatypes.h"
#include "Chromosome.h"
class SolverGEA
{

	KnapsackProblem problem;

	size_t popSize;
	size_t popSizeExtended;

	size_t survivorSize;

	size_t mutantSize;
	size_t mutantGuidedSize;
	size_t crossoverSize;
	size_t crossoverGuidedSize;
	size_t insertionSize;
	size_t threshold;

	size_t chromosomeSize;

public:
	size_t generateMask();
	void randomise_population(std::vector<Chromosome>& solutions);

	void randomise_chromosome(Chromosome& c);

	std::vector<Chromosome> population;
	std::vector<Chromosome> mask;
	std::vector<size_t> popNums;
	SolverGEA(KnapsackProblem problem, size_t popSize, size_t popSizeExtended, double survivorPart, double thresholdPart,
		int mutantWeight,  int crossoverWeight, int mutantGuidedWeight, int crossoverGuidedWeight, int insertionWeight);
	Chromosome mutate_reverse_guided(size_t chromosomeN);
	Chromosome mutate_flip_guided(size_t chromosomeN);
	void mutate_reverse(Chromosome& chromosome);
	void mutate_flip(Chromosome& chromosome);
	void crossover_single(Chromosome& chromosome1, Chromosome& chromosome2);
	void crossover_double(Chromosome& chromosome1, Chromosome& chromosome2);
	Chromosome insert(size_t dominantN, size_t chromosomeN);
	score_t solver_iteration();
	Chromosome bestResult();
};

