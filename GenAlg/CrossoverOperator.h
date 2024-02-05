#pragma once
#include <vector>
#include "SolverGA.h"

namespace GenAlg {
class CrossoverOperator {
  public:
    CrossoverOperator(size_t pair_count, bool is_double_point = false,
                     bool is_guided = false);
    void operator()(std::vector<SolverGA::chromosome_type>& mutable_population,
                    SolverGA& solver);

  private:
    size_t pair_count_;
    bool is_guided_;
    bool is_double_point_;
};
}  // namespace GenAlg