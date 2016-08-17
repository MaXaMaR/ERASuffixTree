#include "SubTreeBuilder.hpp"
#include "../tree/TreeNode.hpp"
#include "../tree/TreeEdge.hpp"
#include "../utils/Types.hpp"
#include <stack>
#include "../config/SuffixTreeGlobalConfig.hpp"

void SubTreeBuilder::init() {
    dataSource = data.getPrepareResult().getDataSource();
    firstLeaf = data.getTree()->createNode((Tree::NodeLabelType) data.getPrepareResult().getL()[0])->getAccessor();
    //firstEdgeToLeafLabel = SubValue(data.getTree()->getNum(), (SubValue::OffsetType) firstLeaf->getLabel());
    firstEdgeToLeafLabel = SubValue(data.getTree().get(), (SubValue::OffsetType) firstLeaf->getLabel());
}

void SubTreeBuilder::clearRoot() {
    data.getRootNode()->clearEdges();
}

// TODO: possible duplicates solutions:
// TODO: fix edge breakage by first checking if there is already the same node
// TODO: now it breaks the first found node therefore it may create duplicates
// TODO: OR:
// TODO: fix R reading in Prepare

void SubTreeBuilder::go() {

    clearRoot();

    auto firstEdgeToLeaf = data.getTree()
            ->createEdge(data.getRootNode().get(), firstLeaf.get(), firstEdgeToLeafLabel)
            ->getAccessor();

    std::stack<TreeEdgeAccessor> stack;
    stack.push(firstEdgeToLeaf);

    uint64 depth = firstEdgeToLeaf->getLabel().getLength();

    TreeEdgeAccessor se = firstEdgeToLeaf;
    TreeNodeAccessor v1 = data.getRootNode();
    TreeNodeAccessor v2 = firstLeaf;

    auto size = data.getPrepareResult().getB().size();
    for (uint64 i = 1; i < size; i++) {
        auto& bValue = data.getPrepareResult().getB()[i];
        auto c1 = bValue->getFirstValue();
        auto c2 = bValue->getSecondValue();
        auto offset = bValue->getOffset();
        while (depth > offset) {
            // moving down to root
            se = stack.top();
            stack.pop();
            v1 = se->getSource()->getAccessor();
            v2 = se->getTarget()->getAccessor();
            depth -= se->getLabel().getLength();
        }
        TreeNodeAccessor u;
        if (depth == offset) {
            u = v1;
        } else {
            // depth < offset
            auto vt = data.getTree()->createNode()->getAccessor();
            // fix to initial paper
            auto firstValueLength = offset - depth;
//          auto label1 = SubValue(data.getTree()->getNum(), se->getLabel().getOffset(),
//                                   (SubValue::LengthType) firstValueLength);
//          auto label2 = SubValue(data.getTree()->getNum(),
//                                   (SubValue::OffsetType) (se->getLabel().getOffset() + firstValueLength),
//                                   (SubValue::LengthType) (se->getLabel().getLength() - firstValueLength));
            auto label1 = SubValue(data.getTree().get(), se->getLabel().getOffset(),
                                   (SubValue::LengthType) firstValueLength);
            auto label2 = SubValue(data.getTree().get(),
                                   (SubValue::OffsetType) (se->getLabel().getOffset() + firstValueLength),
                                   (SubValue::LengthType) (se->getLabel().getLength() - firstValueLength));
            se->getSource()->setLabel(-1);
            se->setTarget(vt.get());
            se->setLabel(label1);
            auto se2 = data.getTree()->createEdge(vt.get(), v2.get(), label2);
            stack.push(se);
            depth += se->getLabel().getLength();
            u = vt;
        }
        auto uNew = data.getTree()->createNode(
                (Tree::NodeLabelType) (data.getPrepareResult().getL()[i]))->getAccessor();
        // fix to initial paper
        auto neLabelValue = (SubValue::OffsetType) (data.getPrepareResult().getL()[i] + depth);
//      auto neLabel = SubValue(data.getTree()->getNum(), neLabelValue);
        auto neLabel = SubValue(data.getTree().get(), neLabelValue);
        auto ne = data.getTree()->createEdge(u.get(), uNew.get(), neLabel);
        stack.push(ne->getAccessor());
        depth += ne->getLabel().getLength();
    }

}
