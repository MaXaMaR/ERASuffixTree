#pragma once

#include <vector>

#include "TreeNodeAccessor.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Tree;

class TreeMixer : public MemoryLeakDetector<TreeMixer> {
public:

    TreeMixer(Tree* tree, const std::vector<TreeNodeAccessor>& rootValues)
            : tree(tree), rootValues(rootValues) {
    }

    TreeNodeAccessor getRootNode() {
        if (rootNode.get() == nullptr) {
            generateRootNode();
        }
        return rootNode;
    }

private:
    void generateRootNode();

    Tree* tree;
    const std::vector<TreeNodeAccessor>& rootValues;
    TreeNodeAccessor rootNode;
};
