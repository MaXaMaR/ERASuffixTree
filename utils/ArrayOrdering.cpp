#include <vector>
#include <cmath>
#include "ArrayOrdering.hpp"

bool compareArrays(const std::vector<char>& x, const std::vector<char>& y) {
    auto length = std::min(x.size(), y.size());
    for (uint64 i = 0; i < length; i++) {
        auto xValue = x[i];
        auto yValue = y[i];
        if (xValue != yValue) {
            if (xValue == '$') {
                return false;
            }
            if (yValue == '$') {
                return true;
            }
            return xValue < yValue;
        }
    }
    return x.size() < y.size();
}
