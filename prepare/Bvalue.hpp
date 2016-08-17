#pragma once

#include <string>

#include "../utils/Types.hpp"
#include "../utils/WithString.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Bvalue : public WithString, public MemoryLeakDetector<Bvalue> {
public:

    Bvalue(char firstValue, char secondValue, uint64 offset)
            : firstValue(firstValue), secondValue(secondValue), offset(offset) {
    }

    char getFirstValue() const {
        return firstValue;
    }

    char getSecondValue() const {
        return secondValue;
    }

    uint64 getOffset() const {
        return offset;
    }

    std::string toString() override;

private:
    char firstValue;
    char secondValue;
    uint64 offset;
};
