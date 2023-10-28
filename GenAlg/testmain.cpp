#include <random>
#include "KnapsackProblemAssesser.h"
#include "RandFunctions.h"
#include "ReverseMutationOperator.h"
#include "SolverGA.h"
#include <iostream>

int main() {
    using score_t = GenAlg::SolverGA::score_type;
    size_t weight_count = 100;
    std::vector<score_t> weights(weight_count);
    std::mt19937_64 gen_engine(42);
    for (auto& weight : weights) {
        weight = GenAlg::RandFunctions<score_t>::rand_int(gen_engine, 100);
    }
    score_t capacity = weight_count * 100 / 2;
    GenAlg::KnapsackProblemAssesser assesser(capacity, weights);
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers.push_back(GenAlg::ReverseMutationOperator(100));
    GenAlg::SolverGA solver(assesser, gen_engine, weight_count, 200, 100, 100,
                            solvers);
    for (size_t i = 0; i < 1000; i++) {
        solver.iterate();
        std::cout << solver.get_best_score() << std::endl;
    }
}