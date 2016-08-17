#include "TreeNodeAccessor.hpp"
#include "Tree.hpp"

TreeNode* TreeNodeAccessor::get() const {
    auto tree = getTree();
    if (tree == nullptr) {
        return nullptr;
    }
    return tree->getNode(nodeNum);
}

size_t std::hash<TreeNodeAccessor>::operator()(const TreeNodeAccessor& x) const {
    return (size_t) ((uint64) x.getTree() * 345 + x.getNodeNum() * 678);
}
