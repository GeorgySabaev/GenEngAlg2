#pragma once
#include "SolverGA.h"

namespace GenAlg {
class SolverFactory {
  public:
    SolverFactory(size_t popSize, size_t extendedPopSize);

    SolverGA getSolverGA(SolverGA::assesser_type problem,
                                size_t variable_count,
                                std::mt19937_64::result_type rand_seed);
    SolverGA getSolverGEA1(SolverGA::assesser_type problem,
                                  size_t variable_count,
                                  std::mt19937_64::result_type rand_seed);
    SolverGA getSolverGEA2(SolverGA::assesser_type problem,
                                  size_t variable_count,
                                  std::mt19937_64::result_type rand_seed);
    SolverGA getSolverGEA3(SolverGA::assesser_type problem,
                                  size_t variable_count,
                                  std::mt19937_64::result_type rand_seed);
    SolverGA getSolverGEA(SolverGA::assesser_type problem,
                                 size_t variable_count,
                                 std::mt19937_64::result_type rand_seed);

  private:
    const size_t popSize_;
    const size_t extendedPopSize_;
};
}  // namespace GenAlg