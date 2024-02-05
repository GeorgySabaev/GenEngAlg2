#pragma once
#include "SolverGA.h"

namespace GenAlg {
class SolverFactory {
  public:
    SolverFactory(size_t popSize, size_t extendedPopSize);

    SolverGA get_GA(SolverGA::assesser_type problem,
                                size_t variable_count,
                                std::mt19937_64::result_type rand_seed);
    SolverGA get_GEA1(SolverGA::assesser_type problem,
                                  size_t variable_count,
                                  std::mt19937_64::result_type rand_seed);
    SolverGA get_GEA2(SolverGA::assesser_type problem,
                                  size_t variable_count,
                                  std::mt19937_64::result_type rand_seed);
    SolverGA get_GEA3(SolverGA::assesser_type problem,
                                  size_t variable_count,
                                  std::mt19937_64::result_type rand_seed);
    SolverGA get_GEA(SolverGA::assesser_type problem,
                                 size_t variable_count,
                                 std::mt19937_64::result_type rand_seed);
    std::vector<SolverGA> get_solvers(SolverGA::assesser_type problem,
                                      size_t variable_count,
                                      std::mt19937_64::result_type rand_seed);

  private:
    const size_t popSize_;
    const size_t extendedPopSize_;
};
}  // namespace GenAlg