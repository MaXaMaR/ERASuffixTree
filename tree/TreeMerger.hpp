#pragma once

#include <unordered_set>
#include <memory>
#include <vector>

#include "../utils/LazyValue.hpp"

#include "TreeNodeAccessor.hpp"
#include "TreeEdgeAccessor.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "../tree/TreePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class TreeMerger : public MemoryLeakDetector<TreeMerger> {
public:

    TreeMerger(const DataSourcePtr& dataSource, const TreePtr& tree, TreeNodeAccessor rootNode);

    LazyValue<TreeNodeAccessor> getNewRootNode() const {
        return newRootNode;
    }

private:
    void generate();
    void getEdges();
    void createUntilNodes();
    void createNodes();
    void prune();

    LazyValue<TreeNodeAccessor> newRootNode;
    std::unordered_set<TreeNodeAccessor> until;
    DataSourcePtr dataSource;
    TreeNodeAccessor rootNode;
    std::vector<TreeEdgeAccessor> edges;

    TreePtr tree;
    TreeNodeAccessor generatingTreeNode;
};
