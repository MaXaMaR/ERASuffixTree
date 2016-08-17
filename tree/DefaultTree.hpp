#pragma once

#include <vector>

#include "Tree.hpp"

#include "TreeEdge.hpp"
#include "TreeNode.hpp"

#include "../dataSources/DataSourcePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class DefaultTree : public Tree, public MemoryLeakDetector<DefaultTree> {
public:

    DefaultTree(const DataSourcePtr& dataSource)
            : Tree(dataSource) {}

    TreeNode* createNode(NodeLabelType label = -1) override {
        //nodes.emplace_back(getNum(), (NodeNumType) nodes.size(), label);
        nodes.emplace_back(this, (NodeNumType) nodes.size(), label);
        return &nodes.back();
    }

    TreeEdge* createEdge(TreeNode* sourceNode, TreeNode* targetNode, SubValue label) override {
        //edges.emplace_back(getNum(), (EdgeNumType) edges.size(), sourceNode, targetNode, label);
        edges.emplace_back(this, (EdgeNumType) edges.size(), sourceNode, targetNode, label);
        edges.back().init();
        return &edges.back();
    }

    TreeNode* getNode(NodeNumType num) override {
        if (num == -1) {
            return nullptr;
        }
        return &nodes[num];
    }

    TreeEdge* getEdge(EdgeNumType num) override {
        if (num == -1) {
            return nullptr;
        }
        return &edges[num];
    }

private:
    std::vector<TreeEdge> edges;
    std::vector<TreeNode> nodes;
};
