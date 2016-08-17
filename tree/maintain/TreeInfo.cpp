#include "TreeInfo.hpp"
#include "../TreeNode.hpp"

TreeInfo::TreeInfo(TreeNodeAccessor rootNode) : rootNode(rootNode) {

    nodesCount = LazyValue<uint64> {
            [=](auto& value) {
                value = generateNodesCount();
            }
    };

    edgesCount = LazyValue<uint64> {
            [=](auto& value) {
                value = generateEdgesCount();
            }
    };

    leavesCount = LazyValue<uint64> {
            [=](auto& value) {
                value = generateLeavesCount();
            }
    };

    interCount = LazyValue<uint64> {
            [=](auto& value) {
                value = generateInterCount();
            }
    };

}

uint64 TreeInfo::generateNodesCount() {
    uint64 res = 0;
    rootNode.get()->iterateNodes([&](const TreeNode* node) {
        res++;
    }, true);
    return res;
}

uint64 TreeInfo::generateEdgesCount() {
    uint64 res = 0;
    rootNode.get()->iterateEdges([&](const TreeEdge* edge) {
        res++;
    });
    return res;
}

uint64 TreeInfo::generateLeavesCount() {
    uint64 res = 0;
    rootNode.get()->iterateLeaves([&](const TreeNode* node) {
        res++;
    });
    return res;
}

uint64 TreeInfo::generateInterCount() {
    uint64 res = 0;
    rootNode.get()->iterateInter([&](const TreeNode* node) {
        res++;
    });
    return res;
}
