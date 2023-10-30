#include <fstream>
#include <iostream>
#include <sstream>
#include "KnapsackProblemAssesser.h"
#include "RandFunctions.h"
#include "SolverFactory.h"
#include "SolverGA.h"
#include "CSVPrinter.h"

namespace GenAlgBenchmark {
void benchmark(std::string groupName, GenAlg::KnapsackProblemAssesser problem,
               size_t var_count, int iterations, int attempts) {
    using score_t = GenAlg::SolverGA::score_type;

    std::mt19937_64 gen_engine(42);
    std::vector<std::vector<std::vector<score_t>>> results(5);
    std::string names[5] = {"GA", "GEA1", "GEA2", "GEA3", "GEA"};
    for (size_t attempt = 0; attempt < attempts; attempt++) {
        GenAlg::SolverFactory solver_factory(400, 800);

        std::vector<GenAlg::SolverGA> solvers =
            solver_factory.get_solvers(problem, var_count, gen_engine());

        for (size_t i = 0; i < 5; i++) {
            results[i].emplace_back(iterations);
            for (size_t j = 0; j < iterations; j++) {
                std::cout << groupName << "_attempt_" << attempt << "_solver_"
                          << i << "_iteration_" << j << "\n";
                results[i].back()[j] = solvers[i].iterate();
            }
        }
    }
    for (size_t i = 0; i < 5; i++) {
        GenAlg::CSVPrinter<score_t> printer;
        printer.print_table(groupName + "_" + names[i] + ".csv", results[i]);
    }
}
}  // namespace GenAlgBenchmark

int main() {
    using score_t = GenAlg::SolverGA::score_type;

    std::mt19937_64 gen_engine(42);
    auto gen_linear = [&gen_engine]() {
        return GenAlg::RandFunctions<score_t>::rand_int(gen_engine, 100);
    };
    const size_t LIN_MAX = 100;
    auto gen_quintic = [&gen_engine]() {
        return std::pow(
            GenAlg::RandFunctions<score_t>::rand_int(gen_engine, 10), 5);
    };
    const size_t QUIN_MAX = 100000;

    std::vector<std::string> group_names = {
        "1_small", "2_low_bar", "3_high_bar", "4_large", "5_heavy_spread"};
    std::vector<size_t> group_sizes = {200, 200, 200, 1000, 200};
    std::vector<std::function<score_t()>> group_gen_funcs = {
        gen_linear, gen_linear, gen_linear, gen_linear, gen_quintic};
    std::vector<size_t> group_maxvalues = {100, 100, 100, 100, 100000};
    std::vector<double> group_capacities = {0.5, 0.3, 0.8, 0.5, 0.5};

    const size_t ATTEMPTS = 10;
    const size_t ITERATIONS = 200;
    for (size_t i = 0; i < group_names.size(); i++) {
        std::vector<score_t> scores(group_sizes[i]);
        std::generate(scores.begin(), scores.end(), group_gen_funcs[i]);
        GenAlg::CSVPrinter<score_t> printer;
        printer.print_row(group_names[i] + "_input.txt", scores);
        size_t capacity_score =
            group_maxvalues[i] * group_capacities[i] * group_sizes[i];
        GenAlg::KnapsackProblemAssesser assesser(capacity_score, scores);
        GenAlgBenchmark::benchmark(group_names[i], assesser, group_sizes[i],
                                   ITERATIONS, ATTEMPTS);
    }
    return 0;
}