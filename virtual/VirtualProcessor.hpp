#pragma once

#include <memory>
#include <vector>

#include "../utils/Types.hpp"

#include "../tree/TreeNodeAccessor.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "VirtualTreesPtr.hpp"
#include "../tree/TreePtr.hpp"

#include "../build/SubTreeBuildData.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class VirtualProcessor : public MemoryLeakDetector<VirtualProcessor> {
public:

    using VirtualTreeBuildData = std::shared_ptr<std::vector<SubTreeBuildData>>;
    using BuildData = std::shared_ptr<std::vector<VirtualTreeBuildData>>;

    VirtualProcessor(const DataSourcePtr& dataSource,
                     const VirtualTreesPtr& virtualTrees, uint64 rangePerScan);

    void go();

    TreePtr getTree() const {
        return tree;
    }

    BuildData getBuildData() const {
        return buildData;
    }

    TreeNodeAccessor getRootNode() const {
        return rootNode;
    }

private:

    void init();

    void createValues();

    void sort();

    void reconstruct();

    TreePtr tree;
    DataSourcePtr dataSource;
    VirtualTreesPtr virtualTrees;
    uint64 rangePerScan;
    TreeNodeAccessor rootNode;
    std::vector<TreeNodeAccessor> rootNodes;
    BuildData buildData;
};
