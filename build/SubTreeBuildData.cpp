#include "SubTreeBuildData.hpp"
#include "../tree/Tree.hpp"
#include "../tree/TreeNode.hpp"
#include "../prefixes/PrefixPtr.hpp"
#include "../tree/TreePtr.hpp"

SubTreeBuildData::SubTreeBuildData(const PrefixPtr& prefix, const TreePtr& tree)
        : prefix(prefix), tree(tree) {
    init();
}

void SubTreeBuildData::init() {
    rootNode = tree->createNode()->getAccessor();
}
