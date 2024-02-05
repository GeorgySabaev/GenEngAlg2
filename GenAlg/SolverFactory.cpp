#include "SolverFactory.h"
#include <random>
#include "CrossoverOperator.h"
#include "FlipMutationOperator.h"
#include "InsertionOperator.h"
#include "ReverseMutationOperator.h"

namespace GenAlg {
SolverFactory::SolverFactory(size_t popSize, size_t extendedPopSize)
    : popSize_(popSize), extendedPopSize_(extendedPopSize) {}

SolverGA SolverFactory::get_GA(SolverGA::assesser_type problem,
                                    size_t variable_count,
                                    std::mt19937_64::result_type rand_seed) {

    const size_t OPER_NUM = 2;
    const size_t MUTAT_NUM = 2;
    const size_t CROSS_NUM = 2;
    const double SURV_PART = 0.6;
    const double MASK_PART = 0.3;

    size_t operation_size = (extendedPopSize_ - popSize_) / OPER_NUM;
    size_t mutation_size = operation_size / MUTAT_NUM;
    size_t crossover_size = operation_size / CROSS_NUM / 2;
    size_t remainder = extendedPopSize_ - popSize_ - mutation_size * MUTAT_NUM -
                       crossover_size * CROSS_NUM * 2 -
                       (OPER_NUM - 2) * operation_size;
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers = {
        GenAlg::FlipMutationOperator(mutation_size + remainder, false),
        GenAlg::ReverseMutationOperator(mutation_size, false),
        GenAlg::CrossoverOperator(crossover_size, false, false),
        GenAlg::CrossoverOperator(crossover_size, true, false),
    };

    return SolverGA(problem, rand_seed, variable_count, popSize_,
                    popSize_ * SURV_PART, popSize_ * MASK_PART, solvers);
}
SolverGA SolverFactory::get_GEA1(SolverGA::assesser_type problem,
                                      size_t variable_count,
                                      std::mt19937_64::result_type rand_seed) {
    const size_t OPER_NUM = 2;
    const size_t MUTAT_NUM = 4;
    const size_t CROSS_NUM = 2;
    const double SURV_PART = 0.6;
    const double MASK_PART = 0.3;

    size_t operation_size = (extendedPopSize_ - popSize_) / OPER_NUM;
    size_t mutation_size = operation_size / MUTAT_NUM;
    size_t crossover_size = operation_size / CROSS_NUM / 2;
    size_t remainder = extendedPopSize_ - popSize_ - mutation_size * MUTAT_NUM -
                       crossover_size * CROSS_NUM * 2 -
                       (OPER_NUM - 2) * operation_size;
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers = {
        GenAlg::FlipMutationOperator(mutation_size + remainder, false),
        GenAlg::FlipMutationOperator(mutation_size, true),
        GenAlg::ReverseMutationOperator(mutation_size, false),
        GenAlg::ReverseMutationOperator(mutation_size, true),
        GenAlg::CrossoverOperator(crossover_size, false, false),
        GenAlg::CrossoverOperator(crossover_size, true, false),
    };

    return SolverGA(problem, rand_seed, variable_count, popSize_,
                    popSize_ * SURV_PART, popSize_ * MASK_PART, solvers);
}
SolverGA SolverFactory::get_GEA2(SolverGA::assesser_type problem,
                                      size_t variable_count,
                                      std::mt19937_64::result_type rand_seed) {
    const size_t OPER_NUM = 2;
    const size_t MUTAT_NUM = 2;
    const size_t CROSS_NUM = 4;
    const double SURV_PART = 0.6;
    const double MASK_PART = 0.3;

    size_t operation_size = (extendedPopSize_ - popSize_) / OPER_NUM;
    size_t mutation_size = operation_size / MUTAT_NUM;
    size_t crossover_size = operation_size / CROSS_NUM / 2;
    size_t remainder = extendedPopSize_ - popSize_ - mutation_size * MUTAT_NUM -
                       crossover_size * CROSS_NUM * 2 -
                       (OPER_NUM - 2) * operation_size;
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers = {
        GenAlg::FlipMutationOperator(mutation_size + remainder, false),
        GenAlg::ReverseMutationOperator(mutation_size, false),
        GenAlg::CrossoverOperator(crossover_size, false, false),
        GenAlg::CrossoverOperator(crossover_size, true, false),
        GenAlg::CrossoverOperator(crossover_size, false, true),
        GenAlg::CrossoverOperator(crossover_size, true, true),
    };

    return SolverGA(problem, rand_seed, variable_count, popSize_,
                    popSize_ * SURV_PART, popSize_ * MASK_PART, solvers);
}
SolverGA SolverFactory::get_GEA3(SolverGA::assesser_type problem,
                                      size_t variable_count,
                                      std::mt19937_64::result_type rand_seed) {
    const size_t OPER_NUM = 3;
    const size_t MUTAT_NUM = 2;
    const size_t CROSS_NUM = 2;
    const double SURV_PART = 0.6;
    const double MASK_PART = 0.3;

    size_t operation_size = (extendedPopSize_ - popSize_) / OPER_NUM;
    size_t mutation_size = operation_size / MUTAT_NUM;
    size_t crossover_size = operation_size / CROSS_NUM / 2;
    size_t remainder = extendedPopSize_ - popSize_ - mutation_size * MUTAT_NUM -
                       crossover_size * CROSS_NUM * 2 -
                       (OPER_NUM - 2) * operation_size;
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers = {
        GenAlg::FlipMutationOperator(mutation_size + remainder, false),
        GenAlg::ReverseMutationOperator(mutation_size, false),
        GenAlg::CrossoverOperator(crossover_size, false, false),
        GenAlg::CrossoverOperator(crossover_size, true, false),
        GenAlg::InsertionOperator(operation_size),
    };

    return SolverGA(problem, rand_seed, variable_count, popSize_,
                    popSize_ * SURV_PART, popSize_ * MASK_PART, solvers);
}
SolverGA SolverFactory::get_GEA(SolverGA::assesser_type problem,
                                     size_t variable_count,
                                     std::mt19937_64::result_type rand_seed) {
    const size_t OPER_NUM = 3;
    const size_t MUTAT_NUM = 4;
    const size_t CROSS_NUM = 4;
    const double SURV_PART = 0.6;
    const double MASK_PART = 0.3;

    size_t operation_size = (extendedPopSize_ - popSize_) / OPER_NUM;
    size_t mutation_size = operation_size / MUTAT_NUM;
    size_t crossover_size = operation_size / CROSS_NUM / 2;
    size_t remainder = extendedPopSize_ - popSize_ - mutation_size * MUTAT_NUM -
                       crossover_size * CROSS_NUM * 2 -
                       (OPER_NUM - 2) * operation_size;
    std::vector<GenAlg::SolverGA::operation_type> solvers;
    solvers = {
        GenAlg::FlipMutationOperator(mutation_size + remainder, false),
        GenAlg::FlipMutationOperator(mutation_size, true),
        GenAlg::ReverseMutationOperator(mutation_size, false),
        GenAlg::ReverseMutationOperator(mutation_size, true),
        GenAlg::CrossoverOperator(crossover_size, false, false),
        GenAlg::CrossoverOperator(crossover_size, true, false),
        GenAlg::CrossoverOperator(crossover_size, false, true),
        GenAlg::CrossoverOperator(crossover_size, true, true),
        GenAlg::InsertionOperator(operation_size),
    };

    return SolverGA(problem, rand_seed, variable_count, popSize_,
                    popSize_ * SURV_PART, popSize_ * MASK_PART, solvers);
}
std::vector<SolverGA> SolverFactory::get_solvers(
    SolverGA::assesser_type problem, size_t variable_count,
    std::mt19937_64::result_type rand_seed) {
    std::vector<GenAlg::SolverGA> solvers;
    solvers.push_back(
        get_GA(problem, variable_count, rand_seed));
    solvers.push_back(
        get_GEA1(problem, variable_count, rand_seed));
    solvers.push_back(
        get_GEA2(problem, variable_count, rand_seed));
    solvers.push_back(
        get_GEA3(problem, variable_count, rand_seed));
    solvers.push_back(
        get_GEA(problem, variable_count, rand_seed));
    return solvers;
}
}  // namespace GenAlg