#include "KnapsackProblemAssesser.h"
#include <cassert>

namespace GenAlg {

KnapsackProblemAssesser::KnapsackProblemAssesser(
    SolverGA::score_type capacity,
    const std::vector<SolverGA::score_type>& scores)
    : capacity_(capacity), scores_(scores) {}

SolverGA::score_type KnapsackProblemAssesser::operator()(
    SolverGA::chromosome_type chromosome) {
    assert((scores_.size() == chromosome.size()) && "Size must match the number of weights.");
    SolverGA::score_type score = 0;
    for (size_t i = 0; i < scores_.size(); i++) {
        if (chromosome[i]) {
            score += scores_[i];
        }
    }
    if (score > capacity_) {
        return -score;
    } else {
        return score;
    }
}
}  // namespace GenAlg