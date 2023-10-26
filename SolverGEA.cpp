#include "SolverGEA.h"
#include <algorithm>
#include <numeric>
#include "RandomUtils.h"
#include <iostream>

SolverGEA::SolverGEA(KnapsackProblem problem, size_t popSize, size_t popSizeExtended, double survivorPart, double thresholdPart,
	int mutantWeight, int crossoverWeight, int mutantGuidedWeight, int crossoverGuidedWeight, int insertionWeight) :
	population(popSize, Chromosome(problem.getSize())),
	problem(problem),
	popSize(popSize),
	popSizeExtended(popSizeExtended),
	chromosomeSize(problem.getSize())
{
	survivorSize = popSize * survivorPart;
	threshold = survivorSize * thresholdPart;

	double weightSum = static_cast<double>(mutantWeight + mutantGuidedWeight + crossoverWeight + crossoverGuidedWeight + insertionWeight);

	size_t descendantSize = popSizeExtended - popSize;

	mutantSize = mutantWeight / weightSum * descendantSize;
	mutantGuidedSize = mutantGuidedWeight / weightSum * descendantSize;
	crossoverSize = crossoverWeight / weightSum * descendantSize;
	crossoverGuidedSize = crossoverGuidedWeight / weightSum * descendantSize;
	if (crossoverSize % 2) {
		--crossoverSize;
		++crossoverGuidedSize;
	}
	if (crossoverGuidedSize % 2) {
		--crossoverGuidedSize;
	}
	insertionSize = descendantSize - mutantSize - mutantGuidedSize - crossoverSize - crossoverGuidedSize;

	popNums = std::vector<size_t>(popSize);
	std::iota(popNums.begin(), popNums.end(), 0);

	randomise_population(population);
	std::sort(population.begin(), population.end(), [&problem](Chromosome a, Chromosome b) {return problem.assess(a) > problem.assess(b); });
}

void SolverGEA::randomise_population(std::vector<Chromosome>& solutions) {
	for (auto& c : solutions)
	{
		randomise_chromosome(c);
	}
}

void SolverGEA::randomise_chromosome(Chromosome& c) {
	for (auto i : c.genes)
	{
		if (rand() % 2) {
			i.flip();
		}
	}
}

Chromosome SolverGEA::mutate_reverse_guided(size_t chromosomeN) {
	auto chromosome = population[chromosomeN];
	size_t reverse_end = rand() % chromosomeSize;
	size_t reverse_begin = (rand() % (chromosomeSize - 1) + reverse_end) % chromosomeSize;
	if (reverse_begin > reverse_end) {
		std::swap(reverse_end, reverse_begin);
	}
	while (reverse_begin < reverse_end) {
		if (mask[chromosomeN].genes[reverse_begin]) {
			++reverse_begin;
		}
		else if (mask[chromosomeN].genes[reverse_end]) {
			--reverse_end;
		}
		else {
			std::vector<bool>::swap(chromosome.genes[reverse_end--], chromosome.genes[reverse_begin++]);
		}
	}
	return chromosome;
}
Chromosome SolverGEA::mutate_flip_guided(size_t chromosomeN) {
	auto chromosome = population[chromosomeN];
	std::vector<size_t> unfixed;
	for (size_t i = 0; i < chromosomeSize; i++)
	{
		if (!mask[chromosomeN].genes[i]) {
			unfixed.push_back(i);
		}
	}
	if (unfixed.empty()) {
		// better to just return a random chromosome than to add a copy to the population
		randomise_chromosome(chromosome);
		return chromosome;
	}
	size_t position = unfixed[rand() % unfixed.size()];
	chromosome.genes[position].flip();
	return chromosome;
}

void SolverGEA::mutate_reverse(Chromosome& chromosome) {
	size_t reverse_end = rand() % chromosomeSize;
	size_t reverse_begin = (rand() % (chromosomeSize - 1) + reverse_end) % chromosomeSize;
	if (reverse_begin > reverse_end) {
		std::swap(reverse_end, reverse_begin);
	}
	while (reverse_begin < reverse_end) {
		std::vector<bool>::swap(chromosome.genes[reverse_end--], chromosome.genes[reverse_begin++]);
	}
}
void SolverGEA::mutate_flip(Chromosome& chromosome) {
	size_t position = rand() % chromosomeSize;
	chromosome.genes[position].flip();
}

void SolverGEA::crossover_single(Chromosome& chromosome1, Chromosome& chromosome2) {
	size_t position = rand() % chromosomeSize;
	for (size_t i = position; i < chromosomeSize; i++)
	{
		std::vector<bool>::swap(chromosome1.genes[i], chromosome2.genes[i]);
	}
}
void SolverGEA::crossover_double(Chromosome& chromosome1, Chromosome& chromosome2) {
	size_t cross_end = rand() % chromosomeSize;
	size_t cross_begin = (rand() % (chromosomeSize - 1) + cross_end) % chromosomeSize;
	if (cross_begin > cross_end) {
		std::swap(cross_end, cross_begin);
	}
	for (size_t i = cross_begin; i <= cross_end; i++)
	{
		std::vector<bool>::swap(chromosome1.genes[i], chromosome2.genes[i]);
	}
}

Chromosome SolverGEA::insert(size_t dominantN, size_t chromosomeN) {
	auto chromosome = population[chromosomeN];
	for (size_t i = 0; i < chromosomeSize; i++)
	{
		if (mask[dominantN].genes[i])
		{
			chromosome.genes[i] = population[dominantN].genes[i];
		}
	}
	return chromosome;
}

size_t SolverGEA::generateMask() {
	mask = std::vector<Chromosome>(population.size(), Chromosome(chromosomeSize));
	size_t repeats[2][2];
	std::vector<size_t> lockedNum(population.size());
	for (size_t i = 0; i < chromosomeSize - 1; i++)
	{
		memset(repeats, 0, sizeof(repeats));
		for (size_t j = 0; j < population.size(); j++)
		{
			++repeats[population[j].genes[i]][population[j].genes[i + 1]];
		}
		for (size_t j = 0; j < population.size(); j++)
		{
			if (mask[j].genes[i]) {
				continue;
			}
			if (repeats[population[j].genes[i]][population[j].genes[i + 1]] >= threshold) {
				mask[j].genes[i].flip();
				mask[j].genes[i + 1].flip();
				lockedNum[j] += 2;
			}
		}
	}
	return std::distance(lockedNum.begin(), std::max_element(lockedNum.begin(), lockedNum.end()));
}



score_t SolverGEA::solver_iteration()
{
	population.reserve(popSizeExtended);

	size_t dominantN = generateMask();

	// guided mutation
	std::vector<size_t> mutantNums;
	std::sample(popNums.begin(), popNums.begin() + survivorSize, std::back_inserter(mutantNums), mutantSize,
		randenginefixed);
	for (size_t i : mutantNums)
	{
		if (rand() % 2) {
			population.push_back(std::move(mutate_reverse_guided(i)));
		}
		else {
			population.push_back(std::move(mutate_flip_guided(i)));
		}
	}
	// regular mutation
	auto mutStart = population.size();
	std::sample(population.begin(), population.begin() + survivorSize, std::back_inserter(population), mutantGuidedSize,
		randenginefixed);
	for (auto i = population.begin() + mutStart; i < population.end(); i += 2)
	{
		if (rand() % 2) {
			mutate_reverse(*i);
		}
		else {
			mutate_flip(*i);
		}
	}
	// regular crossover
	auto crossStart = population.size();
	std::sample(population.begin(), population.begin() + survivorSize, std::back_inserter(population), crossoverSize,
		randenginefixed);
	for (auto i = population.begin() + crossStart; i < population.end(); i += 2)
	{
		if (rand() % 2) {
			crossover_double(*i, *(i + 1));
		}
		else {
			crossover_single(*i, *(i + 1));
		}
	}
	// guided crossover
	std::vector<size_t> crossedNums;
	std::sample(popNums.begin(), popNums.begin() + popSize, std::back_inserter(crossedNums), crossoverGuidedSize / 2,
		randenginefixed);
	for (size_t i : crossedNums)
	{
		population.push_back(population[dominantN]);
		population.push_back(population[i]);
		if (rand() % 2) {
			crossover_double(population.back(), *(population.end() - 2));
		}
		else {
			crossover_single(population.back(), *(population.end() - 2));
		}
	}
	// insertion
	std::vector<size_t> insertedNums;
	std::sample(popNums.begin() + survivorSize, popNums.begin() + popSize, std::back_inserter(insertedNums), insertionSize,
		randenginefixed);
	for (auto i : insertedNums)
	{
		population.push_back(insert(dominantN, i));
	}

	// sort & cleanup
	std::sort(population.begin(), population.end(), [this](Chromosome a, Chromosome b) {return problem.assess(a) > problem.assess(b); });
	population.resize(popSize);
	return problem.assess(population.front());
}

Chromosome SolverGEA::bestResult()
{
	return population.front();
}
