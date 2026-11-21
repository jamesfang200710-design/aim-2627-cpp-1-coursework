#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    std::vector<std::vector<int>> result;
    if (grid.empty()) {
        return result;
    }

    const std::size_t cols = grid.front().size();
    if (cols == 0) {
        throw std::invalid_argument("grid row is empty");
    }

    for (const std::string& row : grid) {
        if (row.size() != cols) {
            throw std::invalid_argument("grid rows have different lengths");
        }
        for (char cell : row) {
            if (cell != '.' && cell != '#') {
                throw std::invalid_argument("grid contains an unknown character");
            }
        }
    }

    const int rows = static_cast<int>(grid.size());
    result.assign(static_cast<std::size_t>(rows),
                  std::vector<int>(cols, 0));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < static_cast<int>(cols); ++c) {
            if (grid[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] == '#') {
                result[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = -1;
                continue;
            }
            int count = 0;
            if (r > 0 && grid[static_cast<std::size_t>(r - 1)][static_cast<std::size_t>(c)] == '#') {
                ++count;
            }
            if (r + 1 < rows &&
                grid[static_cast<std::size_t>(r + 1)][static_cast<std::size_t>(c)] == '#') {
                ++count;
            }
            if (c > 0 && grid[static_cast<std::size_t>(r)][static_cast<std::size_t>(c - 1)] == '#') {
                ++count;
            }
            if (c + 1 < static_cast<int>(cols) &&
                grid[static_cast<std::size_t>(r)][static_cast<std::size_t>(c + 1)] == '#') {
                ++count;
            }
            result[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = count;
        }
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
