#pragma once

#include <unordered_set>
#include <memory>

#include "../dataSources/DataSourcePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class UsedValues : public MemoryLeakDetector<UsedValues> {
public:

    using Values = std::unordered_set<char>;

    UsedValues() {
    }

    UsedValues(const DataSourcePtr& dataSource) : dataSource(dataSource) {
        generate();
    }

    const Values& getValues() const {
        return values;
    }

private:
    void generate();

    Values values;
    DataSourcePtr dataSource;
};
