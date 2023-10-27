#pragma once
#include <vector>
#include <ostream>
class Chromosome
{
public:
	std::vector<bool> genes;
	Chromosome(size_t size);
    friend std::ostream& operator<<(std::ostream& os, const Chromosome chromosome);
	Chromosome() {};
};
