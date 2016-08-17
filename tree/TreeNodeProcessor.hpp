#pragma once

#include "SubValue.hpp"

#include "TreeNodeAccessor.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class TreeEdge;

class TreeNodeProcessor : public MemoryLeakDetector<TreeNodeProcessor> {
public:

    TreeNodeProcessor(TreeNodeAccessor node) : node(node) {}

    const TreeEdge* getEdge(SubValue subValue);

    TreeEdge* getEdgeStepByStep(SubValue subValue);

private:
    TreeNodeAccessor node;
    std::vector<char> edgeLabel;
    std::vector<char> subValueLabel;
};
