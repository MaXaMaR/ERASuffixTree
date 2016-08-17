#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../utils/LazyValue.hpp"
#include "../utils/WithString.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "../prefixes/PrefixPtr.hpp"
#include "VirtualTreePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class VirtualTrees : public WithString, public MemoryLeakDetector<VirtualTrees> {
public:

    using Values = std::shared_ptr<std::vector<VirtualTreePtr>>;
    using PrefixesValues = std::shared_ptr<std::vector<PrefixPtr>>;

    VirtualTrees(const DataSourcePtr& dataSource, const Values& values);

    Values getValues() const {
        return values;
    }

    LazyValue<PrefixesValues>& getPrefixes() {
        return prefixes;
    }

    std::string toString() override;

private:
    DataSourcePtr dataSource;
    LazyValue<PrefixesValues> prefixes;
    Values values;
};
