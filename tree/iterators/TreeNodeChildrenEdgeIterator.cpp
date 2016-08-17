#include "TreeNodeChildrenEdgeIterator.hpp"
#include <exception>
#include "../TreeNode.hpp"
#include "../TreeEdge.hpp"

void TreeNodeChildrenEdgeIterator::init() {
    lastEdge = value->getFirstEdge()->getAccessor();
}

void TreeNodeChildrenEdgeIterator::increment() {
    if (lastEdge.isEmpty()) {
        throw std::runtime_error("TreeNodeChildrenEdgeIterator iterated over end");
    }
    auto nextEdge = lastEdge->getNextEdge();
    if (nextEdge != nullptr) {
        lastEdge = nextEdge->getAccessor();
    } else {
        lastEdge.clear();
    }
}
