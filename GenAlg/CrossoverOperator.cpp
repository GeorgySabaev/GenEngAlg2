#include "CrossoverOperator.h"
#include "RandFunctions.h"

namespace GenAlg {

CrossoverOperator::CrossoverOperator(size_t pair_count, bool is_double_point,
                                     bool is_guided)
    : pair_count_(pair_count),
      is_double_point_(is_double_point),
      is_guided_(is_guided) {}

void CrossoverOperator::operator()(
    std::vector<SolverGA::chromosome_type>& population, SolverGA& solver) {

    auto engine = solver.get_rand_engine();
    std::vector<size_t> selected;
    if (is_guided_) {
        selected = RandFunctions<size_t>::sample(
            engine, solver.get_survivor_size(), pair_count_);
    } else {
        selected = RandFunctions<size_t>::sample(
            engine, solver.get_survivor_size(), pair_count_ * 2);
    }

    for (size_t i = 0; i < pair_count_; i++) {
        SolverGA::chromosome_type descendant1;
        SolverGA::chromosome_type descendant2;
        if (is_guided_) {
            descendant1 = population[solver.get_dom_chromosome()];
            descendant2 = population[selected[i]];
        } else {
            descendant1 = population[selected[i * 2]];
            descendant2 = population[selected[i * 2 + 1]];
        }

        std::vector<size_t> bounds;
        if (is_double_point_) {
            bounds = RandFunctions<size_t>::sample(
                engine, solver.get_chromosome_size(), 2);
            ++bounds[1];
        } else {
            auto top_bound = RandFunctions<size_t>::rand_int(
                engine, 1, solver.get_chromosome_size() + 1);
            bounds = {0, top_bound};
        }

        for (size_t j = bounds[0]; j < bounds[1]; j++) {
            std::swap(descendant1[j], descendant2[j]);
        }

        population.push_back(std::move(descendant1));
        population.push_back(std::move(descendant2));
    }
}
}  // namespace GenAlg