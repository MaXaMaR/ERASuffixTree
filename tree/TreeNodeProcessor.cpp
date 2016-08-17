#include "TreeNode.hpp"
#include "TreeNodeProcessor.hpp"
#include "TreeNode.hpp"
#include "TreeEdge.hpp"

const TreeEdge* TreeNodeProcessor::getEdge(SubValue subValue) {
    const TreeEdge* found = nullptr;
    subValue.getValue(subValueLabel);
    node->iterateEdgesRet([&](const TreeEdge* edge) {
        edge->getLabel().getValue(edgeLabel);
        if (edgeLabel == subValueLabel) {
            found = edge;
            return false;
        }
        return true;
    }, true);
    if (found != nullptr) {
        return found;
    }
    auto newNode = node->getTree()->createNode();
    auto newEdge = node->getTree()->createEdge(node.get(), newNode, subValue);
    return newEdge;
}

TreeEdge* TreeNodeProcessor::getEdgeStepByStep(SubValue subValue) {
    TreeEdgeAccessor currentEdge;
    TreeNodeAccessor currentNode = node;
    uint64 start = subValue.getOffset();
    uint64 end = subValue.getOffset() + subValue.getLength();
    for (uint64 currentOffset = start; currentOffset < end; currentOffset++) {
//        currentEdge = TreeNodeProcessor(currentNode)
//                .getEdge(SubValue(subValue.getTreeNum(), (SubValue::OffsetType) currentOffset, 1))
//                ->getAccessor();
        currentEdge = TreeNodeProcessor(currentNode)
                .getEdge(SubValue(subValue.getTree(), (SubValue::OffsetType) currentOffset, 1))
                ->getAccessor();
        currentNode = currentEdge->getTarget()->getAccessor();
    }
    return currentEdge.get();
}
