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

// Assessment 01 Q4; see 题面.pdf.
namespace aim::q4 {
struct CommandResult { long long value; int accepted; int rejected; };

// BEGIN IMPLEMENTATION
namespace {

const long long kLimit = 1000000;

bool parse_command(const std::string& line, std::string& op, long long& x) {
    std::istringstream in(line);
    if (!(in >> op)) {
        return false;
    }

    if (op == "RESET") {
        std::string extra;
        if (in >> extra) {
            return false;
        }
        x = 0;
        return true;
    }

    if (op != "ADD" && op != "SET") {
        return false;
    }

    if (!(in >> x)) {
        return false;
    }
    std::string extra;
    if (in >> extra) {
        return false;
    }
    return x >= -kLimit && x <= kLimit;
}

}

CommandResult execute(const std::vector<std::string>& lines) {
    CommandResult result;
    result.value = 0;
    result.accepted = 0;
    result.rejected = 0;

    for (const std::string& line : lines) {
        std::string op;
        long long x = 0;
        if (!parse_command(line, op, x)) {
            ++result.rejected;
            continue;
        }

        const long long value = (op == "ADD") ? result.value + x : x;
        if (value < -kLimit || value > kLimit) {
            ++result.rejected;
            continue;
        }
        result.value = value;
        ++result.accepted;
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q4;
int main() {
    try {
        { aim::q4::CommandResult r=execute({"ADD 5","SET 8 x","RESET","ADD -2"}); CHECK(r.value==-2 && r.accepted==3 && r.rejected==1); }
        { aim::q4::CommandResult r=execute({}); CHECK(r.value==0 && r.accepted==0 && r.rejected==0); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
