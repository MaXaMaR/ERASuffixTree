#pragma once

#include <vector>
#include <string>

#include "SubValue.hpp"

#include "../utils/WithString.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class SubValuePath : public WithString, public MemoryLeakDetector<SubValuePath> {
public:

    SubValuePath() = default;

    SubValuePath(const SubValuePath& other) = default;

    SubValuePath(SubValuePath&& other) = default;

    std::vector<SubValue>& getValues() {
        return values;
    }

    std::string toString() override;

    std::string toStringConst() const override;

    SubValuePath& operator=(const SubValuePath& other) = default;

    SubValuePath& operator=(SubValuePath&& other) = default;

private:
    std::vector<SubValue> values;
};
