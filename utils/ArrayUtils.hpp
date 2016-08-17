#pragma once

#include <vector>
#include <algorithm>

#include "Types.hpp"

class ArrayUtils {
public:

    template<typename T>
    static bool startsWith(const std::vector<T>& what, const std::vector<T>& withWhat, uint64 whatOffset = 0) {
        if (what.size() < withWhat.size()) {
            return false;
        }
        return std::equal(withWhat.begin(), withWhat.end(), what.begin() + whatOffset);
    }

    template<typename T>
    static bool endsWith(const std::vector<T>& what, const std::vector<T>& withWhat) {
        if (what.size() < withWhat.size()) {
            return false;
        }
        return std::equal(what.begin() + (what.size() - withWhat.size()), what.end(), withWhat.begin());
    }

};
