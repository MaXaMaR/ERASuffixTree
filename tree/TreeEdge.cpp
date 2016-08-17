#include "TreeEdge.hpp"
#include "TreeNode.hpp"

//TreeEdge::TreeEdge(TreeNumType treeNum, EdgeNumType thisNum,
//                   TreeNode* sourceNode, TreeNode* targetNode, SubValue label)
//        : treeNum(treeNum), thisNum(thisNum),
//          sourceNode(sourceNode->getAccessor()), targetNode(targetNode->getAccessor()),
//          label(label) {
//}

TreeEdge::TreeEdge(Tree* tree, EdgeNumType thisNum,
                   TreeNode* sourceNode, TreeNode* targetNode, SubValue label)
        : tree(tree), thisNum(thisNum),
          sourceNode(sourceNode->getAccessor()), targetNode(targetNode->getAccessor()),
          label(label) {
}

void TreeEdge::setSource(TreeNode* value) {
    sourceNode = value->getAccessor();
}

void TreeEdge::setTarget(TreeNode* value) {
    targetNode = value->getAccessor();
    updateTargetParent();
}

void TreeEdge::setNextEdge(TreeEdge* value) {
    nextEdge = value->getAccessor();
}

void TreeEdge::updateTargetParent() {
    getTarget()->setSourceEdge(this);
}

void TreeEdge::updateSourceNextEdge() {
    auto lastEdge = getSource()->getLastEdge();
    if (lastEdge != nullptr) {
        lastEdge->setNextEdge(this);
    }
}

void TreeEdge::updateSourceEdges() {
    if (getSource()->getFirstEdge() == nullptr) {
        getSource()->setFirstEdge(this);
    } else {
        getSource()->setLastEdge(this);
    }
}

void TreeEdge::connect() {
    updateSourceNextEdge();
    updateSourceEdges();
    updateTargetParent();
}

void TreeEdge::init() {
    connect();
}

void TreeEdge::reconnect(TreeNode* newSource) {
    nextEdge.clear();
    setSource(newSource);
    connect();
}
