#include "TreeMerger.hpp"
#include "TreeNode.hpp"
#include "TreeEdge.hpp"
#include "../utils/LazyValue.hpp"
#include "TreeNodeAccessor.hpp"
#include "TreeEdgeAccessor.hpp"
#include "../dataSources/DataSourcePtr.hpp"
#include "TreeNodeProcessor.hpp"

TreeMerger::TreeMerger(const DataSourcePtr& dataSource, const TreePtr& tree, TreeNodeAccessor rootNode)
        : dataSource(dataSource), tree(tree), rootNode(rootNode) {

    newRootNode = LazyValue<TreeNodeAccessor> {
            [=](auto& value) {
                generate();
                value = generatingTreeNode;
            }
    };

}

void TreeMerger::generate() {
    getEdges();
    createUntilNodes();
    createNodes();
    prune();
}

void TreeMerger::getEdges() {
    rootNode->getEdges(edges);
}

void TreeMerger::createUntilNodes() {
    until.clear();
    for (auto& edge : edges) {
        until.insert(edge->getTarget()->getAccessor());
    }
}

void TreeMerger::createNodes() {
    generatingTreeNode = tree->createNode()->getAccessor();
    rootNode->clearEdges();
    for (auto& edge : edges) {
        TreeNodeProcessor(generatingTreeNode)
                .getEdgeStepByStep(edge->getLabel())
                ->setTarget(edge->getTarget());
    }
}

void TreeMerger::prune() {
    generatingTreeNode->pruneEdges(until);
}
