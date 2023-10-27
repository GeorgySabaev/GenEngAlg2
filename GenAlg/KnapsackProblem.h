#pragma once
#include "gatypes.h"
#include "Chromosome.h"
#include <vector>
class KnapsackProblem
{
	std::vector<score_t> scores;
	int capacity;
public:
	size_t getSize();
	score_t assess(Chromosome chromosome);
	KnapsackProblem(std::vector<score_t> scores, int capacity);
};

