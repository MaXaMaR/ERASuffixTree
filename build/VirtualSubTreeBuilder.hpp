#pragma once

#include <vector>
#include <memory>

#include "SubTreeBuildData.hpp"

#include "../utils/LazyValue.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class TreeNode;

class VirtualSubTreeBuilder : public MemoryLeakDetector<VirtualSubTreeBuilder> {
public:

    using Data = std::shared_ptr<std::vector<SubTreeBuildData>>;

    VirtualSubTreeBuilder(Data& data);

    LazyValue<TreeNodeAccessor> getRootNode() {
        return rootNode;
    }

private:

    void build();

    TreeNodeAccessor mix();

    TreeNodeAccessor generate();

    LazyValue<TreeNodeAccessor> rootNode;
    Data& data;
};
