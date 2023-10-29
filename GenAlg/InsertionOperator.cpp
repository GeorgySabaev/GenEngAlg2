#include "InsertionOperator.h"
#include "RandFunctions.h"

namespace GenAlg {

InsertionOperator::InsertionOperator(size_t descendant_count)
    : descendant_count_(descendant_count) {}

void InsertionOperator::operator()(
    std::vector<SolverGA::chromosome_type>& population, SolverGA& solver) {

    auto& engine = solver.get_rand_engine();

    for (auto i : RandFunctions<size_t>::sample(
             engine, solver.get_survivor_size(), descendant_count_)) {

        SolverGA::chromosome_type descendant = population[i];
        
        for (size_t i = 0; i < descendant.size(); i++) {
            if (solver.get_mask()[solver.get_dom_chromosome()][i]) {
                descendant[i] = population[solver.get_dom_chromosome()][i];
            }
        }
        population.push_back(std::move(descendant));
    }
}
}  // namespace GenAlg