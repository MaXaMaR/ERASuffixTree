#include "TreeSorter.hpp"
#include "TreeNode.hpp"
#include "TreeEdge.hpp"
#include <algorithm>
#include "EdgesSort.hpp"
#include <array>
#include <vector>

void TreeSorter::go() {
    auto edges = rootNode->getEdges();
    rootNode->clearEdges();
    std::array<std::vector<char>, 2> buffers;
    std::sort(edges.begin(), edges.end(), EdgesSort(buffers));
    for (auto& edge : edges) {
        edge->reconnect(rootNode.get());
    }
}
