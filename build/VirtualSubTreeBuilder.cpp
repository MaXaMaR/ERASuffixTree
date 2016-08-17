#include "VirtualSubTreeBuilder.hpp"
#include "../tree/Tree.hpp"
#include "SubTreeBuilder.hpp"
#include "../tree/TreeMixer.hpp"
#include "../utils/LazyValue.hpp"
#include <vector>

VirtualSubTreeBuilder::VirtualSubTreeBuilder(Data& data) : data(data) {
    rootNode = LazyValue<TreeNodeAccessor> {
            [=](auto& value) {
                value = generate();
            }
    };
}

TreeNodeAccessor VirtualSubTreeBuilder::generate() {
    build();
    return mix();
}

void VirtualSubTreeBuilder::build() {
    for (auto& dataValue: *data) {
        auto builder = SubTreeBuilder(dataValue);
        builder.go();
    }
}

TreeNodeAccessor VirtualSubTreeBuilder::mix() {
    std::vector<TreeNodeAccessor> rootNodes;
    rootNodes.reserve(data->size());
    for (auto& dataValue: *data) {
        rootNodes.push_back(dataValue.getRootNode());
    }
    auto tree = rootNodes[0].getTree();
    return TreeMixer(tree, rootNodes).getRootNode();
}
