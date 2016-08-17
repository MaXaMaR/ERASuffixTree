#pragma once

#include <vector>
#include <memory>

#include "UsedValues.hpp"

#include "../utils/Types.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "PrefixPtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class DataSource;

class PrefixCalc : public MemoryLeakDetector<PrefixCalc> {
public:

    using Values = std::vector<char>;

    using PrefixesValue = std::vector<PrefixPtr>;
    using Prefixes = std::shared_ptr<PrefixesValue>;

    PrefixCalc(const DataSourcePtr& dataSource, uint64 maxCount);

    Prefixes getResult();

private:
    void init();
    void generate(const Values& startsWith = Values{});
    void goAll();

    Prefixes prefixes;
    Prefixes unprocessedPrefixes;
    UsedValues usedValues;
    DataSourcePtr dataSource;
    uint64 maxCount;
};
