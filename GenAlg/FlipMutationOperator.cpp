#include "FlipMutationOperator.h"
#include "RandFunctions.h"

namespace GenAlg {

FlipMutationOperator::FlipMutationOperator(size_t mutation_count,
                                           bool is_guided)
    : mutation_count_(mutation_count), is_guided_(is_guided) {}

void FlipMutationOperator::operator()(
    std::vector<SolverGA::chromosome_type>& population, SolverGA& solver) {

    auto& engine = solver.get_rand_engine();

    for (auto i : RandFunctions<size_t>::sample(
             engine, solver.get_survivor_size(), mutation_count_)) {

        SolverGA::chromosome_type descendant = population[i];
        size_t flipped_pos;
        if (is_guided_) {
            std::vector<size_t> unfixed;
            for (size_t j = 0; j < descendant.size(); j++) {
                if (!solver.get_mask()[i][j]) {
                    unfixed.push_back(j);
                }
            }
            if (unfixed.empty()) {
                continue;
            }
            flipped_pos = unfixed[RandFunctions<size_t>::rand_int(
                engine, unfixed.size())];
        } else {
            flipped_pos = RandFunctions<size_t>::rand_int(
                engine, solver.get_chromosome_size());
        }
        descendant[flipped_pos] = 1 - descendant[flipped_pos];
        population.push_back(std::move(descendant));
    }
}
}  // namespace GenAlg