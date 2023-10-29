#pragma once
#include "SolverGA.h"

namespace GenAlg {

class KnapsackProblemAssesser {
  public:
    KnapsackProblemAssesser(SolverGA::score_type capacity,
                            const std::vector<SolverGA::score_type>& scores);

    SolverGA::score_type operator()(SolverGA::chromosome_type chromosome);

  private:
    size_t capacity_;
    std::vector<SolverGA::score_type> scores_;
};

}  // namespace GenAlg