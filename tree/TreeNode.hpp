#pragma once

#include <memory>
#include <functional>
#include <unordered_set>
#include <vector>

#include "../config/SuffixTreeGlobalConfig.hpp"

#include "TreeRepository.hpp"

#include "SubValue.hpp"
#include "SubValuePath.hpp"

#include "TreeNodeAccessor.hpp"
#include "TreeEdgeAccessor.hpp"

#include "../utils/MemoryLeakDetector.hpp"

#include "iterators/TreeNodeChildrenNodeIterator.hpp"
#include "iterators/TreeNodeChildrenEdgeIterator.hpp"
#include "iterators/TreeNodeEdgeIterator.hpp"
#include "iterators/TreeNodeNodeIterator.hpp"
#include "iterators/TreeNodeLeafIterator.hpp"
#include "iterators/TreeNodeInterIterator.hpp"

class Tree;

class TreeEdge;

class TreePath;

class TreeNode : public MemoryLeakDetector<TreeNode> {
public:

    using IterNodeFunc = std::function<void(const TreeNode*)>;
    using IterEdgeFunc = std::function<void(const TreeEdge*)>;
    using IterPathFunc = std::function<void(const TreePath*)>;

    using IterNodeNonConstFunc = std::function<void(TreeNode*)>;
    using IterEdgeNonConstFunc = std::function<void(TreeEdge*)>;
    using IterPathNonConstFunc = std::function<void(TreePath*)>;

    using IterNodeRetFunc = std::function<bool(const TreeNode*)>;
    using IterEdgeRetFunc = std::function<bool(const TreeEdge*)>;
    using IterPathRetFunc = std::function<bool(const TreePath*)>;

    using IterNodeRetNonConstFunc = std::function<bool(TreeNode*)>;
    using IterEdgeRetNonConstFunc = std::function<bool(TreeEdge*)>;
    using IterPathRetNonConstFunc = std::function<bool(TreePath*)>;

    using LabelType = SuffixTreeGlobalConfig::TreeNodeLabelType;
    using EdgeNumType = SuffixTreeGlobalConfig::TreeEdgeNumType;
    using NodeNumType = SuffixTreeGlobalConfig::TreeNodeNumType;
    using TreeNumType = SuffixTreeGlobalConfig::TreeNumType;

    /*
    TreeNode(TreeNumType treeNum, NodeNumType thisNum, LabelType label)
            : treeNum(treeNum), thisNum(thisNum), label(label) {
    }*/

    TreeNode(Tree* tree, NodeNumType thisNum, LabelType label)
            : tree(tree), thisNum(thisNum), label(label) {
    }

    NodeNumType getNum() const {
        return this->thisNum;
    }

    LabelType getLabel() const {
        return label;
    }

    Tree* getTree() const {
        //return TreeRepository::get(treeNum);
        return tree;
    }

    TreeEdge* getSourceEdge() const {
        return sourceEdge.get();
    }

    TreeEdge* getFirstEdge() const {
        return firstEdge.get();
    }

    TreeEdge* getLastEdge() const {
        return lastEdge.get();
    }

    void setFirstEdge(TreeEdge* firstEdge);

    void setSourceEdge(TreeEdge* sourceEdge);

    void setLastEdge(TreeEdge* lastEdge);

    void setLabel(LabelType label);

    bool isLeaf() const {
        return firstEdge.getEdgeNum() == -1;
    }

    std::vector<TreeEdgeAccessor>& getEdges(std::vector<TreeEdgeAccessor>& into) const;

    std::vector<TreeEdgeAccessor> getEdges() const;

    void clearEdges() {
        firstEdge.clear();
        lastEdge.clear();
    }

    SubValuePath getPath() const;

    SubValuePath& getPath(SubValuePath& into) const;

    void pruneEdges(const std::unordered_set<TreeNodeAccessor>& until);

    // thread-safe
    void iterateEdgesRet(IterEdgeRetFunc iterator, bool childrenOnly = false) const;

    // thread-safe
    void iterateNodesRet(IterNodeRetFunc iterator, bool withCurrent = false, bool childrenOnly = false) const;

    // thread-safe
    void iterateInterRet(IterNodeRetFunc iterator, bool* ret = nullptr) const;

    // thread-safe
    void iterateLeavesRet(IterNodeRetFunc iterator, bool* ret = nullptr) const;

    // thread-safe
    void iteratePathsRet(IterPathRetNonConstFunc iterator, TreePath* prevPath = nullptr, bool* ret = nullptr) const;

    // thread-safe
    void iterateEdges(IterEdgeFunc iterator, bool childrenOnly = false) const;

    // thread-safe
    void iterateNodes(IterNodeFunc iterator, bool withCurrent = false, bool childrenOnly = false) const;

    // thread-safe
    void iterateInter(IterNodeFunc iterator) const;

    // thread-safe
    void iterateLeaves(IterNodeFunc iterator) const;

    // thread-safe
    void iteratePaths(IterPathNonConstFunc iterator, TreePath* prevPath = nullptr) const;

    bool operator==(const TreeNode& other) {
        return this == &other;
    }

    TreeNodeAccessor getAccessor() const {
        //return {treeNum, thisNum};
        return {tree, thisNum};
    }

    TreeNodeChildrenNodeIterator childNodesBegin() const {
        return {getAccessor()};
    }

    TreeNodeChildrenNodeIterator childNodesEnd() const {
        return {getAccessor(), {}};
    }

    TreeNodeChildrenEdgeIterator childEdgesBegin() const {
        return {getAccessor()};
    }

    TreeNodeChildrenEdgeIterator childEdgesEnd() const {
        return {getAccessor(), {}};
    }

    TreeNodeEdgeIterator edgesBegin() const {
        return {getAccessor()};
    }

    TreeNodeEdgeIterator edgesEnd() const {
        return {getAccessor(), {}};
    }

    TreeNodeNodeIterator nodesBegin() const {
        return {edgesBegin()};
    }

    TreeNodeNodeIterator nodesEnd() const {
        return {edgesEnd()};
    }

    TreeNodeLeafIterator leavesBegin() const {
        return {nodesBegin()};
    }

    TreeNodeLeafIterator leavesEnd() const {
        return {nodesEnd()};
    }

    TreeNodeInterIterator interBegin() const {
        return {nodesBegin()};
    }

    TreeNodeInterIterator interEnd() const {
        return {nodesEnd()};
    }

    // returns the last matched node, if it is contained in a tree
    TreeNode* followPath(const std::vector<char>& path, uint64 offset = 0, std::vector<char>* edgeLabel = nullptr);

    uint64 getMaxEdgeLength() const;

private:

    TreeEdgeAccessor calcLastEdge() const;

    void iterateChildrenEdgesRet(IterEdgeRetNonConstFunc iterator) const;

    void iterateAllEdgesRet(IterEdgeRetFunc iterator, bool* ret = nullptr) const;

    void iterateChildrenNodesRet(IterNodeRetFunc iterator) const;

    void iterateAllNodesRet(IterNodeRetFunc iterator, bool withCurrent = false, bool* ret = nullptr) const;

    void iterateChildrenEdges(IterEdgeNonConstFunc iterator) const;

    void iterateAllEdges(IterEdgeFunc iterator) const;

    void iterateChildrenNodes(IterNodeFunc iterator) const;

    void iterateAllNodes(IterNodeFunc iterator, bool withCurrent = false) const;

    LabelType label;
    //TreeNumType treeNum;
    Tree* tree;
    NodeNumType thisNum;
    TreeEdgeAccessor sourceEdge;
    TreeEdgeAccessor firstEdge;
    TreeEdgeAccessor lastEdge;
};
