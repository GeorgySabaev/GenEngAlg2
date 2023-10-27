#include "Chromosome.h"

Chromosome::Chromosome(size_t size)
{
	genes = std::vector<bool>(size);
}

std::ostream& operator<<(std::ostream& os, const Chromosome chromosome)
{
    {
        os << "[";
        for (int i = 0; i < chromosome.genes.size(); ++i) {
            os << chromosome.genes[i];
            if (i != chromosome.genes.size() - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }
}
