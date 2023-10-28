#include "ReverseMutationOperator.h"
#include "RandFunctions.h"

namespace GenAlg {

ReverseMutationOperator::ReverseMutationOperator(size_t mutation_count,
                                                 bool is_guided)
    : mutation_count_(mutation_count), is_guided_(is_guided) {}

void ReverseMutationOperator::operator()(
    std::vector<SolverGA::chromosome_type>& population, SolverGA& solver) {

    auto engine = solver.get_rand_engine();

    for (auto i : RandFunctions<size_t>::sample(
             engine, solver.get_survivor_size(), mutation_count_)) {

        SolverGA::chromosome_type descendant = population[i];

        auto bounds = RandFunctions<size_t>::sample(
            engine, solver.get_chromosome_size(), 2);
        while (bounds[0] < bounds[1]) {
            if (is_guided_) {
                if (solver.get_mask()[i][bounds[0]]) {
                    ++bounds[0];
                    continue;
                }
                if (is_guided_ && solver.get_mask()[i][bounds[1]]) {
                    --bounds[1];
                    continue;
                }
            }
            std::swap(descendant[bounds[1]], descendant[bounds[0]]);
            --bounds[1];
            ++bounds[0];
        }

        population.push_back(std::move(descendant));
    }
}
}  // namespace GenAlg