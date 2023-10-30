#pragma once
#include <string>
#include <vector>

namespace GenAlg {
template <typename T>
class CSVPrinter {
  public:
    CSVPrinter(std::string cell_separator = ",",
                std::string line_separator = "\n")
        : cell_separator_(cell_separator), line_separator_(line_separator) {}
    void print_row(std::string path, std::vector<T>& row) {
        std::ofstream out;
        out.open(path);
        out << row[0];
        for (size_t i = 1; i < row.size(); i++) {
            out << "," << row[i];
        }
        out << std::endl;
        out.close();
    }
    void print_table(std::string path, std::vector<std::vector<T>>& table) {
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

  private:
    std::string cell_separator_;
    std::string line_separator_;
};
}  // namespace GenAlg