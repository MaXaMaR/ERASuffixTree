#include "StringVector.hpp"
#include <algorithm>
#include <vector>

const std::vector<char>& StringVector::getVector() {
    if (!vectorInit) {
        buf.reserve(str.length());
        std::copy(str.cbegin(), str.cend(), std::back_inserter(buf));
        vectorInit = true;
    }
    return buf;
}
