#pragma once

#include <memory>

#include "../config/SuffixTreeGlobalConfig.hpp"

#include "SubValue.hpp"

#include "../utils/WithNum.hpp"

#include "../dataSources/DataSourcePtr.hpp"

class TreeNode;

class TreeEdge;

// Tree with linked list elements
// Search on node for next edge: O(n) where n is count of elements on an edge
// May be converted (with O(n)) to tree with vector elements for O(1) access time

class Tree : public WithNum<SuffixTreeGlobalConfig::TreeNumType> {
public:

    using TreeNumType = SuffixTreeGlobalConfig::TreeNumType;
    using NodeLabelType = SuffixTreeGlobalConfig::TreeNodeLabelType;
    using NodeNumType = SuffixTreeGlobalConfig::TreeNodeNumType;
    using EdgeNumType = SuffixTreeGlobalConfig::TreeEdgeNumType;

    Tree(const DataSourcePtr& dataSource);

    virtual ~Tree();

    DataSourcePtr getDataSource() const {
        return dataSource;
    }

    // valid until new item is created
    virtual TreeNode* createNode(NodeLabelType label = -1) = 0;

    // valid until new item is created
    virtual TreeEdge* createEdge(TreeNode* sourceNode, TreeNode* targetNode, SubValue label) = 0;

    // valid until new item is created
    virtual TreeNode* getNode(NodeNumType num) = 0;

    // valid until new item is created
    virtual TreeEdge* getEdge(EdgeNumType num) = 0;

private:
    DataSourcePtr dataSource;
};
