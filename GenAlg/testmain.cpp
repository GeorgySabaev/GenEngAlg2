#include <iostream>
#include <random>
#include "CrossoverOperator.h"
#include "KnapsackProblemAssesser.h"
#include "RandFunctions.h"
#include "ReverseMutationOperator.h"
#include "FlipMutationOperator.h"
#include "SolverGA.h"

int main() {
    // defining problem
    using score_t = GenAlg::SolverGA::score_type;
    size_t weight_count = 200;
    std::vector<score_t> weights(weight_count);
    std::mt19937_64 gen_engine(42);
    for (auto& weight : weights) {
        weight = GenAlg::RandFunctions<score_t>::rand_int(gen_engine, 100);
    }
    score_t capacity = weight_count * 100 / 2;


    // building solver
    GenAlg::KnapsackProblemAssesser assesser(capacity, weights);
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers = {
        GenAlg::FlipMutationOperator(50),
        GenAlg::FlipMutationOperator(50, true),
        GenAlg::ReverseMutationOperator(50),
        GenAlg::ReverseMutationOperator(50, true),
        GenAlg::CrossoverOperator(30, false),
        GenAlg::CrossoverOperator(30, true),
        GenAlg::CrossoverOperator(30, true, true),
    };
    GenAlg::SolverGA solver(assesser, gen_engine, weight_count, 400, 300, 200,
                            solvers);


    // running solver
    for (size_t i = 0; i < 1000; i++) {
        solver.iterate();
        std::cout << solver.get_best_score() << std::endl;
    }
}