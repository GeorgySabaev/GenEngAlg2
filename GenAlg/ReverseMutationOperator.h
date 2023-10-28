#pragma once
#include <vector>
#include "SolverGA.h"

namespace GenAlg {
class ReverseMutationOperator {
  public:
    ReverseMutationOperator(size_t mutation_count, bool guided = false);
    void operator()(std::vector<SolverGA::chromosome_type>& mutable_population,
                    SolverGA& solver);
  private:
    size_t mutation_count_;
    bool guided_;
};
}  // namespace GenAlg