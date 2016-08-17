#pragma once

#include "TreeNodeAccessor.hpp"

class TreeSorter {
public:

    TreeSorter(TreeNodeAccessor rootNode) : rootNode(rootNode) {}

    void go();

private:
    TreeNodeAccessor rootNode;
};
