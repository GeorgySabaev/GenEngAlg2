#pragma once
#include <functional>
#include <span>
#include <vector>
#include <random>

namespace GenAlg {

class SolverGA {
  public:
    using score_type = int64_t;
    using chromosome_type = std::vector<char>;
    using assesser_type = std::function<score_type(chromosome_type const&)>;
    using operation_type = std::function<void(std::vector<chromosome_type>&, SolverGA const&)>;

    SolverGA(assesser_type assesser, std::mt19937 rand_engine, size_t pop_size,
             size_t survivor_size, size_t mask_threshold,
             std::span<operation_type> operations);

    const chromosome_type& get_best_result() const;
    score_type get_best_score() const;
    const std::vector<chromosome_type>& get_population() const;
    const std::vector<chromosome_type>& get_mask() const;
    size_t get_population_size() const;
    size_t get_chromosome_size() const;
    size_t get_survivor_size() const;
    size_t get_mask_threshold() const;
    size_t get_dom_chromosome() const;

    score_type iterate();

  private:
    assesser_type assesser_;

    size_t population_size_;
    size_t chromosome_size_;
    size_t survivor_size_;
    size_t mask_threshold_;
    size_t dom_chrom_index_;

    std::mt19937 rand_engine_;

    std::vector<chromosome_type> population_;
    std::vector<chromosome_type> mask_;
    std::vector<operation_type> operations_;

    void generate_mask();
    void randomise_population();
    void randomise_chromosome(chromosome_type& c);
};

}