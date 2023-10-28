#pragma once
#include <random>
#include <vector>
#include <set>

namespace GenAlg {
template <class T>
requires std::integral<T> class RandFunctions {
  public:
    static T rand_int(std::mt19937_64& engine, T cap) {
        return rand_int(engine, T(0), cap);
    }
    static T rand_int(std::mt19937_64& engine, T floor, int64_t cap) {
        std::uniform_int_distribution<T> dist(floor, cap - T(1));
        return dist(engine);
    }
    static std::vector<T> sample(std::mt19937_64& engine, T n, T k) {
        // Robert Floyd's subset selection algorithm
        std::set<T> values;
        for (T i = n - k; i < n; i++) {
            T j = rand_int(engine, i + 1);
            if (values.contains(j)) {
                values.insert(i);
            } else {
                values.insert(j);
            }
        }
        return std::vector<T>(values.begin(), values.end());
    }

  private:
    RandFunctions();
};

}  // namespace GenAlg