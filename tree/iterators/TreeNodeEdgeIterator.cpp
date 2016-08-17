#include "TreeNodeEdgeIterator.hpp"
#include <exception>
#include "../TreeNode.hpp"
#include "../TreeEdge.hpp"

void TreeNodeEdgeIterator::init() {
    lastEdge = value->getFirstEdge()->getAccessor();
}

void TreeNodeEdgeIterator::backward() {
    while (lastEdge.isDefined() && lastEdge->getNextEdge() == nullptr) {
        auto sourceEdge = lastEdge->getSource()->getSourceEdge();
        if (sourceEdge != nullptr) {
            lastEdge = sourceEdge->getAccessor();
        } else {
            lastEdge.clear();
        }
    }
    if (lastEdge.isDefined()) {
        lastEdge = lastEdge->getNextEdge()->getAccessor();
    }
}

void TreeNodeEdgeIterator::increment() {
    if (lastEdge.isEmpty()) {
        throw std::runtime_error("TreeNodeEdgeIterator iterated over end");
    }
    auto targetEdge = lastEdge->getTarget()->getFirstEdge();
    if (targetEdge != nullptr) {
        lastEdge = targetEdge->getAccessor();
    } else {
        auto nextEdge = lastEdge->getNextEdge();
        if (nextEdge != nullptr) {
            lastEdge = nextEdge->getAccessor();
        } else {
            backward();
        }
    }
}
