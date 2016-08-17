#pragma once

#include <memory>
#include <vector>

#include "../utils/Types.hpp"
#include "../utils/LazyValue.hpp"

#include "../build/SubTreeBuildData.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "../virtual/VirtualTreePtr.hpp"
#include "../tree/TreePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class VirtualSubTreePrepare : public MemoryLeakDetector<VirtualSubTreePrepare> {
public:

    using BuildData = std::shared_ptr<std::vector<SubTreeBuildData>>;
    using VirtualTreeValue = std::shared_ptr<VirtualTree>;
    using TreeValue = std::shared_ptr<Tree>;

    VirtualSubTreePrepare(const DataSourcePtr& dataSource, const TreePtr& tree,
                          const VirtualTreePtr& virtualTree, uint64 rangePerScan);

    LazyValue<BuildData> getBuildData() const {
        return buildData;
    }

private:
    void generate(BuildData& buildData);

    DataSourcePtr dataSource;
    TreePtr tree;

    LazyValue<BuildData> buildData;
    VirtualTreePtr virtualTree;
    uint64 rangePerScan;
};
