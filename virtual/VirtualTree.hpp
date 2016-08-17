#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../utils/WithString.hpp"
#include "../utils/LazyValue.hpp"

#include "../prefixes/PrefixPtr.hpp"
#include "../tree/TreePtr.hpp"

#include "../dataSources/DataSourcePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class VirtualTree : public WithString, public MemoryLeakDetector<VirtualTree> {
public:

    using PrefixesValue = std::shared_ptr<std::vector<PrefixPtr>>;

    VirtualTree(const DataSourcePtr& dataSource, const PrefixesValue& prefixes);

    PrefixesValue getPrefixes() const {
        return prefixes;
    }

    TreePtr& getTree() {
        return tree;
    }

    std::string toString() override;

private:
    void init();

    DataSourcePtr dataSource;
    PrefixesValue prefixes;
    TreePtr tree;
};
