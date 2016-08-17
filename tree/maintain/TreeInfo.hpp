#pragma once

#include "../../utils/Types.hpp"
#include "../../utils/LazyValue.hpp"

#include "../TreeNodeAccessor.hpp"

#include "../../utils/MemoryLeakDetector.hpp"

class TreeInfo : public MemoryLeakDetector<TreeInfo> {
public:

    TreeInfo(TreeNodeAccessor rootNode);

    LazyValue<uint64>& getNodesCount() {
        return nodesCount;
    }

    LazyValue<uint64>& getEdgesCount() {
        return edgesCount;
    }

    LazyValue<uint64>& getLeavesCount() {
        return leavesCount;
    }

    LazyValue<uint64>& getInterCount() {
        return interCount;
    }

private:

    uint64 generateNodesCount();
    uint64 generateEdgesCount();
    uint64 generateLeavesCount();
    uint64 generateInterCount();

    TreeNodeAccessor rootNode;
    LazyValue<uint64> nodesCount;
    LazyValue<uint64> edgesCount;
    LazyValue<uint64> leavesCount;
    LazyValue<uint64> interCount;
};
