#pragma once

#include <memory>

#include "../config/SuffixTreeGlobalConfig.hpp"

#include "../tree/TreeRepository.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Tree;

class TreeNode;

class TreeNodeAccessor : public MemoryLeakDetector<TreeNodeAccessor> {
public:

    using TreeNumType = SuffixTreeGlobalConfig::TreeNumType;
    using TreeNodeNumType = SuffixTreeGlobalConfig::TreeNodeNumType;

    TreeNodeAccessor() : /*treeNum(-1),*/ tree(nullptr), nodeNum(-1) {
    }

    TreeNodeAccessor(const TreeNodeAccessor& other) = default;

//    TreeNodeAccessor(TreeNumType treeNum, TreeNodeNumType nodeNum) : treeNum(treeNum), nodeNum(nodeNum) {
//    }

    TreeNodeAccessor(Tree* tree, TreeNodeNumType nodeNum) : tree(tree), nodeNum(nodeNum) {
    }

//    TreeNumType getTreeNum() const {
//        return treeNum;
//    }

    TreeNodeNumType getNodeNum() const {
        return nodeNum;
    }

    Tree* getTree() const {
        //return TreeRepository::get(treeNum);
        return tree;
    }

    // valid until new item is added to tree
    TreeNode* get() const;

    void clear() {
        //treeNum = -1;
        tree = nullptr;
        nodeNum = -1;
    }

    bool isDefined() const {
        //return treeNum != -1 && nodeNum != -1;
        return tree != nullptr && nodeNum != -1;
    }

    bool isEmpty() const {
        return !isDefined();
    }

    bool operator==(const TreeNodeAccessor& other) const {
        //return treeNum == other.treeNum && nodeNum == other.nodeNum;
        return tree == other.tree && nodeNum == other.nodeNum;
    }

    bool operator!=(const TreeNodeAccessor& other) const {
        return !(*this == other);
    }

    // valid until new item is added to tree
    TreeNode* operator->() const noexcept {
        return get();
    }

    // valid until new item is added to tree
    TreeNode& operator*() const noexcept {
        return *get();
    }

private:
    //TreeNumType treeNum;
    Tree* tree;
    TreeNodeNumType nodeNum;
};

namespace std {
    template<>
    struct hash<TreeNodeAccessor> {
        size_t operator()(const TreeNodeAccessor& x) const;
    };
}
