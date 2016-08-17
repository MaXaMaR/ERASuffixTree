#include "TreeNodeNodeIterator.hpp"
#include "../TreeNode.hpp"
#include "../TreeEdge.hpp"

TreeNodeAccessor TreeNodeNodeIterator::getAccessor() const {
    return edgeIt.getAccessor()->getTarget()->getAccessor();
}

TreeNode* TreeNodeNodeIterator::operator->() const {
    return edgeIt->getTarget();
}
