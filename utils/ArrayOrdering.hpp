#pragma once

#include <vector>

#include <boost/functional/hash.hpp>

#include "Types.hpp"

bool compareArrays(const std::vector<char>& x, const std::vector<char>& y);

namespace std {

    template<>
    struct hash<std::vector<char>> {

        std::size_t operator()(const std::vector<char>& k) const {
            std::size_t value = 0;
            for (auto val : k) {
                boost::hash_combine(value, val);
            }
            return value;
        }

    };

}
