#include "TreeNodeInterIterator.hpp"
#include "../TreeNode.hpp"

void TreeNodeInterIterator::init() {
    detect();
}

void TreeNodeInterIterator::detect() {
    while (nodeIt.isDefined() && nodeIt->isLeaf()) {
        nodeIt++;
    }
}

void TreeNodeInterIterator::increment() {
    nodeIt++;
    detect();
}
