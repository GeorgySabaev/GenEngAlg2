#include <fstream>
#include <iostream>
#include <sstream>
#include "RandFunctions.h"
#include "SolverGA.h"
#include "SolverFactory.h"
#include "KnapsackProblemAssesser.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

void printCSV(std::string path,
              std::vector<std::vector<GenAlg::SolverGA::score_type>>& table) {
    std::ofstream out;
    out.open(path);
    for (auto row : table) {
        out << row[0];
        for (size_t i = 1; i < row.size(); i++) {
            out << "," << row[i];
        }
        out << std::endl;
    }
    out.close();
}

template <typename T>
void printFile(std::string path, T obj) {
    std::ofstream out;
    out.open(path);
    out << obj;
    out.close();
}

void solveBenchmark(std::string groupName,
                    GenAlg::KnapsackProblemAssesser problem, size_t var_count,
                    int iterations, int attempts) {
    using score_t = GenAlg::SolverGA::score_type;

    std::mt19937_64 gen_engine(42);
    std::vector<std::vector<std::vector<score_t>>> results(5);
    std::string names[5] = {"GA", "GEA1", "GEA2", "GEA3", "GEA"};
    for (size_t attempt = 0; attempt < attempts; attempt++) {
        GenAlg::SolverFactory solver_factory(400, 800);

        std::vector<GenAlg::SolverGA> solvers;
        std::mt19937_64::result_type rand_seed = gen_engine();
        solvers.push_back(
            solver_factory.getSolverGA(problem, var_count, rand_seed));
        solvers.push_back(
            solver_factory.getSolverGEA1(problem, var_count, rand_seed));
        solvers.push_back(
            solver_factory.getSolverGEA2(problem, var_count, rand_seed));
        solvers.push_back(
            solver_factory.getSolverGEA3(problem, var_count, rand_seed));
        solvers.push_back(
            solver_factory.getSolverGEA(problem, var_count, rand_seed));
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
        printCSV(groupName + "_" + names[i] + ".csv", results[i]);
    }
}

int main() {
    using score_t = GenAlg::SolverGA::score_type;
    std::mt19937_64 gen_engine(42);
    auto gen_linear = [&gen_engine]() {
        return GenAlg::RandFunctions<score_t>::rand_int(gen_engine, 100);
    };
    auto gen_quintic = [&gen_engine]() {
        return std::pow(
            GenAlg::RandFunctions<score_t>::rand_int(gen_engine, 10), 5);
    };
    // - test 1: small, 50% capacity
    std::string name = "1_small";
    std::vector<score_t> scores1(200);
    std::generate(scores1.begin(), scores1.end(), gen_linear);
    printFile(name + "_input.txt", scores1);

    GenAlg::KnapsackProblemAssesser problem1(50 * 200, scores1);
    solveBenchmark(name, problem1, 200, 200, 11);

    // - test 2: low bar, 30% capacity
    name = "2_low_bar";
    std::vector<score_t> scores2(200);
    std::generate(scores2.begin(), scores2.end(), gen_linear);
    printFile(name + "_input.txt", scores2);

    GenAlg::KnapsackProblemAssesser problem2(30 * 200, scores2);
    solveBenchmark(name, problem2, 200, 200, 11);

    // - test 3: high bar, 80% capacity
    name = "3_high_bar";
    std::vector<score_t> scores3(200);
    std::generate(scores3.begin(), scores3.end(), gen_linear);
    printFile(name + "_input.txt", scores3);

    GenAlg::KnapsackProblemAssesser problem3(80 * 200, scores3);
    solveBenchmark(name, problem3, 200, 200, 11);

    // - test 4: large, 50% capacity
    name = "4_large";
    std::vector<score_t> scores4(1000);
    std::generate(scores4.begin(), scores4.end(), gen_linear);
    printFile(name + "_input.txt", scores4);

    GenAlg::KnapsackProblemAssesser problem4(50 * 1000, scores4);
    solveBenchmark(name, problem4, 1000, 200, 5);

    // - test 5: heavy_spread, 30% capacity
    name = "5_heavy_spread";
    std::vector<score_t> scores5(200);
    std::generate(scores5.begin(), scores5.end(), gen_quintic);
    printFile(name + "_input.txt", scores5);

    GenAlg::KnapsackProblemAssesser problem5(50000 * 200, scores5);
    solveBenchmark(name, problem5, 200, 200, 11);
}