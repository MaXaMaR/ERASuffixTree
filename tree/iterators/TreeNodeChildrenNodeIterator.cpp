#include "TreeNodeChildrenNodeIterator.hpp"
#include <exception>
#include "../TreeNode.hpp"
#include "../TreeEdge.hpp"

void TreeNodeChildrenNodeIterator::init() {
    lastEdge = value->getFirstEdge()->getAccessor();
}

void TreeNodeChildrenNodeIterator::increment() {
    if (lastEdge.isEmpty()) {
        throw std::runtime_error("TreeNodeChildrenNodeIterator iterated over end");
    }
    auto nextEdge = lastEdge->getNextEdge();
    if (nextEdge != nullptr) {
        lastEdge = nextEdge->getAccessor();
    } else {
        lastEdge.clear();
    }
}

TreeNode* TreeNodeChildrenNodeIterator::operator->() const {
    return lastEdge->getTarget();
}

TreeNodeAccessor TreeNodeChildrenNodeIterator::getAccessor() const {
    return lastEdge->getTarget()->getAccessor();
}
