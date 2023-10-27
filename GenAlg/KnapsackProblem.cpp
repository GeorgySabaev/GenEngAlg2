#include "KnapsackProblem.h"

size_t KnapsackProblem::getSize()
{
	return scores.size();
}

score_t KnapsackProblem::assess(Chromosome chromosome)
{
	score_t score = 0;
	for (size_t i = 0; i < getSize(); i++)
	{
		if (chromosome.genes[i]) {
			score += scores[i];
		}
	}
	if (score > capacity) {
		return -score;
	}
	else {
		return score;
	}
}

KnapsackProblem::KnapsackProblem(std::vector<score_t> scores, int capacity) : scores(scores), capacity(capacity) {}
