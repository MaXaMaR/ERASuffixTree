#pragma once

#include <vector>
#include <tuple>

#include "Types.hpp"

template<typename T>
class Combinations {
public:

    using Result = std::vector<std::tuple<T, T>>;

    Combinations(const std::vector<T>& values) : values(values), generated(false) {
    }

    const Result& getResult() {
        if (!generated) {
            generate();
        }
        return result;
    };

private:

    void generate() {
        result.reserve(values.size() * values.size());
        for (uint64 i = 0; i < values.size(); i++) {
            for (uint64 k = 0; k < values.size(); k++) {
                if (values[i] != values[k]) {
                    result.push_back(std::make_tuple(values[i], values[k]));
                }
            }
        }
        result.shrink_to_fit();
    }

    bool generated;
    const std::vector<T>& values;
    Result result;
};
