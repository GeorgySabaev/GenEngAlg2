#include "Solvers.h"

SolverGEA Solvers::getSolverGA(KnapsackProblem problem)
{
    return SolverGEA(problem, 400, 600, 0.6, 0.3, 1, 1, 0, 0, 0);
}

SolverGEA Solvers::getSolverGEA1(KnapsackProblem problem)
{
    return SolverGEA(problem, 400, 600, 0.6, 0.3, 1, 1, 1, 0, 0);
}
SolverGEA Solvers::getSolverGEA2(KnapsackProblem problem)
{
    return SolverGEA(problem, 400, 600, 0.6, 0.3, 1, 1, 0, 1, 0);
}
SolverGEA Solvers::getSolverGEA3(KnapsackProblem problem)
{
    return SolverGEA(problem, 400, 600, 0.6, 0.3, 1, 1, 0, 0, 1);
}

SolverGEA Solvers::getSolverGEA(KnapsackProblem problem)
{
    return SolverGEA(problem, 400, 600, 0.6, 0.3, 1, 1, 1, 1, 1);
}


