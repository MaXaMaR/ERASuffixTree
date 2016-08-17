#include "PrefixUtils.hpp"
#include "../utils/Types.hpp"
#include <cmath>

PrefixUtils::Value& PrefixUtils::commonPrefix(const Value& first, const Value& second, Value& into) {
    uint64 length = std::min(first.size(), second.size());
    into.clear();
    for (uint64 i = 0; i < length; i++) {
        if (first[i] == second[i]) {
            into.push_back(first[i]);
        } else {
            break;
        }
    }
    return into;
}

PrefixUtils::Value PrefixUtils::commonPrefix(const Value& first, const Value& second) {
    PrefixUtils::Value res;
    commonPrefix(first, second, res);
    return res;
}
