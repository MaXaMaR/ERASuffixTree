#include "TreeEdgeAccessor.hpp"
#include "Tree.hpp"

TreeEdge* TreeEdgeAccessor::get() const {
    auto tree = getTree();
    if (tree == nullptr) {
        return nullptr;
    }
    return tree->getEdge(edgeNum);
}

size_t std::hash<TreeEdgeAccessor>::operator()(const TreeEdgeAccessor& x) const {
    return (size_t) ((uint64) x.getTree() * 345 + x.getEdgeNum() * 678);
}
