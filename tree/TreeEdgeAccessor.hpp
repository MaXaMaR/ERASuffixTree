#pragma once

#include <memory>

#include "../config/SuffixTreeGlobalConfig.hpp"

#include "TreeRepository.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Tree;

class TreeEdge;

class TreeEdgeAccessor : public MemoryLeakDetector<TreeEdgeAccessor> {
public:

    using TreeNumType = SuffixTreeGlobalConfig::TreeNumType;
    using TreeEdgeNumType = SuffixTreeGlobalConfig::TreeEdgeNumType;

    TreeEdgeAccessor() : /*treeNum(-1),*/ tree(nullptr), edgeNum(-1) {
    }

    TreeEdgeAccessor(const TreeEdgeAccessor& other) = default;

//    TreeEdgeAccessor(TreeNumType treeNum, TreeEdgeNumType edgeNum) : treeNum(treeNum), edgeNum(edgeNum) {
//    }

    TreeEdgeAccessor(Tree* tree, TreeEdgeNumType edgeNum) : tree(tree), edgeNum(edgeNum) {
    }

//    TreeNumType getTreeNum() const {
//        return treeNum;
//    }

    TreeEdgeNumType getEdgeNum() const {
        return edgeNum;
    }

    Tree* getTree() const {
        //return TreeRepository::get(treeNum);
        return tree;
    }

    // valid until new item is added to tree
    TreeEdge* get() const;

    void clear() {
        //treeNum = -1;
        tree = nullptr;
        edgeNum = -1;
    }

    bool isDefined() const {
        //return treeNum != -1 && edgeNum != -1;
        return tree != nullptr && edgeNum != -1;
    }

    bool isEmpty() const {
        return !isDefined();
    }

    bool operator==(const TreeEdgeAccessor& other) const {
        //return treeNum == other.treeNum && edgeNum == other.edgeNum;
        return tree == other.tree && edgeNum == other.edgeNum;
    }

    bool operator!=(const TreeEdgeAccessor& other) const {
        return !(*this == other);
    }

    // valid until new item is added to tree
    TreeEdge* operator->() const noexcept {
        return get();
    }

    // valid until new item is added to tree
    TreeEdge& operator*() const noexcept {
        return *get();
    }

private:
    //TreeNumType treeNum;
    Tree* tree;
    TreeEdgeNumType edgeNum;
};

namespace std {
    template<>
    struct hash<TreeEdgeAccessor> {
        size_t operator()(const TreeEdgeAccessor& x) const;
    };
}
