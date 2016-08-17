#include "TreeMixer.hpp"
#include <vector>
#include "TreeEdge.hpp"
#include "TreeNode.hpp"
#include "TreeEdgeAccessor.hpp"

void TreeMixer::generateRootNode() {
    std::vector<TreeEdgeAccessor> edges;
    for (auto& thisRootValue:rootValues) {
        thisRootValue.get()->getEdges(edges);
    }
    rootNode = tree->createNode()->getAccessor();
    for (auto& edge : edges) {
        edge.get()->reconnect(rootNode.get());
    }
}
