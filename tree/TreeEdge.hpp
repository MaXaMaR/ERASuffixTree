#pragma once

#include "../config/SuffixTreeGlobalConfig.hpp"

#include "TreeRepository.hpp"

#include "Tree.hpp"

#include "SubValue.hpp"

#include "TreeEdgeAccessor.hpp"
#include "TreeNodeAccessor.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Tree;

class TreeEdge : public MemoryLeakDetector<TreeEdge> {
public:

    using EdgeNumType = SuffixTreeGlobalConfig::TreeEdgeNumType;
    using NodeNumType = SuffixTreeGlobalConfig::TreeNodeNumType;
    using TreeNumType = SuffixTreeGlobalConfig::TreeNumType;

    /*
    TreeEdge(TreeNumType treeNum, EdgeNumType thisNum,
             TreeNode* sourceNode, TreeNode* targetNode, SubValue label);
             */

    TreeEdge(Tree* tree, EdgeNumType thisNum,
             TreeNode* sourceNode, TreeNode* targetNode, SubValue label);

    void init();

    EdgeNumType getNum() const {
        return this->thisNum;
    }

    Tree* getTree() const {
        //return TreeRepository::get(treeNum);
        return tree;
    }

    TreeEdge* getNextEdge() const {
        return nextEdge.get();
    }

    TreeNode* getSource() const {
        return sourceNode.get();
    }

    TreeNode* getTarget() const {
        return targetNode.get();
    }

    SubValue getLabel() const {
        return label;
    }

    void setLabel(SubValue label) {
        this->label = label;
    }

    void setTarget(TreeNode* value);

    void reconnect(TreeNode* newSource);

    TreeEdgeAccessor getAccessor() const {
        //return {treeNum, thisNum};
        return {tree, thisNum};
    }

    bool operator==(const TreeEdge& other) {
        return this == &other;
    }

private:
    void updateTargetParent();
    void updateSourceNextEdge();
    void updateSourceEdges();
    void connect();

    void setSource(TreeNode* value);

    void setNextEdge(TreeEdge* value);

    //TreeNumType treeNum;
    Tree* tree;
    EdgeNumType thisNum;
    SubValue label;
    TreeEdgeAccessor nextEdge;
    TreeNodeAccessor sourceNode;
    TreeNodeAccessor targetNode;
};
