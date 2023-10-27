#pragma once
#include "SolverGEA.h"
class Solvers
{
public:
	static SolverGEA getSolverGA(KnapsackProblem problem);
	static SolverGEA getSolverGEA1(KnapsackProblem problem);
	static SolverGEA getSolverGEA2(KnapsackProblem problem);
	static SolverGEA getSolverGEA3(KnapsackProblem problem);
	static SolverGEA getSolverGEA(KnapsackProblem problem);
};

