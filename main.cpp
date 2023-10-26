#include <iostream>
#include <sstream>
#include <fstream>
#include "Solvers.h"
#include "RandomUtils.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}

void printCSV(std::string path, std::vector<std::vector<score_t>>& table) {
	std::ofstream out;
	out.open(path);
	for (auto row : table)
	{
		out << row[0];
		for (size_t i = 1; i < row.size(); i++)
		{
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

void solveBenchmark(std::string groupName, KnapsackProblem problem, int iterations, int attempts) {
	std::vector<std::vector<std::vector<score_t>>> results (5);
	std::string names[5] = { "GA", "GEA1", "GEA2", "GEA3", "GEA" };
	for (size_t attempt = 0; attempt < attempts; attempt++)
	{
		
		std::vector<SolverGEA> solvers;
		solvers.push_back(Solvers::getSolverGA(problem));
		solvers.push_back(Solvers::getSolverGEA1(problem));
		solvers.push_back(Solvers::getSolverGEA2(problem));
		solvers.push_back(Solvers::getSolverGEA3(problem));
		solvers.push_back(Solvers::getSolverGEA(problem));
		for (size_t i = 0; i < 5; i++)
		{
			results[i].emplace_back(iterations);
			for (size_t j = 0; j < iterations; j++)
			{
				std::cout << groupName << "_attempt_" << attempt << "_solver_" << i << "_iteration_" << j << std::endl;
				results[i].back()[j] = solvers[i].solver_iteration();
			}
		}
	}
	for (size_t i = 0; i < 5; i++)
	{
		printCSV("output/" + groupName + "_" + names[i] + ".csv", results[i]);
	}
}

int main()
{
	// - test 1: small, 50% capacity
	std::uniform_int_distribution<score_t> dist1{ 1, 100 };
	auto gen1 = [&dist1]() {
		return dist1(randenginefixed);
	};
	std::vector<score_t> scores1(200);
	std::generate(scores1.begin(), scores1.end(), gen1);
	printFile("output/1_small_input.txt", scores1);
	KnapsackProblem problem1(scores1, 50*200);
	solveBenchmark("1_small", problem1, 200, 11);


	// - test 2: low bar, 30% capacity
	std::vector<score_t> scores2(200);
	std::generate(scores2.begin(), scores2.end(), gen1);
	printFile("output/2_low_bar_input.txt", scores2);
	KnapsackProblem problem2(scores2, 30 * 200);
	solveBenchmark("2_low_bar", problem2, 200, 11);

	// - test 3: high bar, 80% capacity
	std::vector<score_t> scores3(200);
	std::generate(scores3.begin(), scores3.end(), gen1);
	printFile("output/3_high_bar_input.txt", scores3);
	KnapsackProblem problem3(scores3, 80 * 200);
	solveBenchmark("3_high_bar", problem3, 200, 11);

	// - test 4: large, 50% capacity
	std::vector<score_t> scores4(1000);
	std::generate(scores4.begin(), scores4.end(), gen1);
	printFile("output/4_large_input.txt", scores4);
	KnapsackProblem problem4(scores4, 50*1000);
	solveBenchmark("4_large", problem4, 200, 5);

	// - test 5: heavy_spread, 30% capacity
	std::uniform_int_distribution<score_t> dist2{ 1, 10 };
	auto gen2 = [&dist2]() {
		return std::pow(dist2(randenginefixed), 5);
	};
	std::vector<score_t> scores5(200);
	printFile("output/5_heavy_spread_input.txt", scores5);
	std::generate(scores5.begin(), scores5.end(), gen2);
	KnapsackProblem problem5(scores5, 50000 * 200);
	solveBenchmark("5_heavy_spread", problem5, 200, 11);
}