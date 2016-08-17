#include "TreeNodeLeafIterator.hpp"
#include "../TreeNode.hpp"

void TreeNodeLeafIterator::init() {
    detect();
}

void TreeNodeLeafIterator::detect() {
    while (nodeIt.isDefined() && !nodeIt->isLeaf()) {
        nodeIt++;
    }
}

void TreeNodeLeafIterator::increment() {
    nodeIt++;
    detect();
}
