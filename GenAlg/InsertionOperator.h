#pragma once
#include <vector>
#include "SolverGA.h"

namespace GenAlg {
class InsertionOperator {
  public:
    InsertionOperator(size_t descendant_count_);
    void operator()(std::vector<SolverGA::chromosome_type>& mutable_population,
                    SolverGA& solver);

  private:
    size_t descendant_count_;
};
}  // namespace GenAlg