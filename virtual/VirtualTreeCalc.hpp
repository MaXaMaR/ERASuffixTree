#pragma once

#include <memory>
#include <vector>
#include <set>

#include "../utils/Types.hpp"
#include "../utils/LazyValue.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "../prefixes/PrefixPtr.hpp"
#include "VirtualTreePtr.hpp"
#include "VirtualTreesPtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class VirtualTreeCalc : public MemoryLeakDetector<VirtualTreeCalc> {
public:

    using PrefixesValue = std::shared_ptr<std::vector<PrefixPtr>>;
    using VirtualTreesSourceValue = std::shared_ptr<std::vector<VirtualTreePtr>>;

    VirtualTreeCalc(const DataSourcePtr& dataSource, const PrefixesValue& prefixes, uint64 maxCount);

    LazyValue<VirtualTreesPtr>& getValues() {
        return values;
    }

private:
    void prepare();
    void go();
    void goAll();

    VirtualTreesPtr generateValues();

    DataSourcePtr dataSource;
    PrefixesValue prefixes;
    uint64 maxCount;

    LazyValue<VirtualTreesPtr> values;
    std::set<uint64> prefixesIndexes;

    VirtualTreesSourceValue generatingValues;
};
