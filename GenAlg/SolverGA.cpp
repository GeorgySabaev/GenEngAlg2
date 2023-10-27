#include "SolverGA.h"
#include <array>
#include <cassert>

namespace GenAlg {

SolverGA::SolverGA(assesser_type assesser, std::mt19937 rand_engine,
                 size_t pop_size,
         size_t survivor_size, size_t mask_threshold,
         std::span<operation_type> operations) {}

const SolverGA::chromosome_type& SolverGA::get_best_result() const {
    assert((!population_.empty()) && "Population must not be empty");
    return population_[0];
}

SolverGA::score_type SolverGA::get_best_score() const {
    return assesser_(get_best_result());
}

const std::vector<SolverGA::chromosome_type>& SolverGA::get_population() const {
    return population_;
}

const std::vector<SolverGA::chromosome_type>& SolverGA::get_mask() const {
    return mask_;
}

size_t SolverGA::get_population_size() const {
    return population_size_;
}

size_t SolverGA::get_chromosome_size() const {
    return chromosome_size_;
}

size_t SolverGA::get_survivor_size() const {
    return survivor_size_;
}

size_t SolverGA::get_mask_threshold() const {
    return mask_threshold_;
}

size_t SolverGA::get_dom_chromosome() const {
    return dom_chrom_index_;
}

SolverGA::score_type SolverGA::iterate() {
    generate_mask();
    for (auto operation : operations_) {
        operation(population_, *this);
    }
    std::sort(population_.begin(), population_.end(),
              [this](chromosome_type a, chromosome_type b) {
                  return assesser_(a) > assesser_(b);
              });
    population_.resize(population_size_);
    return get_best_score();
}

void SolverGA::generate_mask() {
    mask_ = std::vector<chromosome_type>(
        population_size_, chromosome_type(chromosome_size_));
    std::array<std::array<size_t, 2>, 2> repeats;
    std::vector<size_t> locked_count(population_size_);

    for (size_t i = 0; i < chromosome_size_ - 1; i++) {
        repeats[0].fill(0);
        repeats[1].fill(0);
        for (size_t j = 0; j < population_size_; j++) {
            ++repeats[population_[j][i]][population_[j][i + 1]];
        }
        for (size_t j = 0; j < population_size_; j++) {
            if (mask_[j][i]) {
                continue;
            }
            if (repeats[population_[j][i]][population_[j][i + 1]] >=
                mask_threshold_) {
                mask_[j][i] = 1;
                mask_[j][i + 1] = 1;
                locked_count[j] += 2;
            }
        }
    }
    dom_chrom_index_ = std::distance(
        locked_count.begin(),
        std::max_element(locked_count.begin(), locked_count.end()));
}

void SolverGA::randomise_population() {
    for (auto& c : population_) {
        randomise_chromosome(c);
    }
}

void SolverGA::randomise_chromosome(chromosome_type& c) {
    for (auto& i : c) {
        i = std::uniform_int_distribution<int>(0, 1)(rand_engine_);
    }
}

}  // namespace GenAlg