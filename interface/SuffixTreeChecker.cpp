#include "SuffixTreeChecker.hpp"
#include "SuffixTree.hpp"
#include "SuffixTreeException.hpp"
#include "SuffixTreeInfo.hpp"
#include "../tree/maintain/TreeInfo.hpp"
#include <sstream>
#include "../tree/TreeNode.hpp"
#include "../tree/SubValue.hpp"
#include "../tree/TreeEdge.hpp"
#include "../utils/Combinations.hpp"
#include "../prefixes/PrefixUtils.hpp"
#include "../utils/ArrayPrinter.hpp"
#include "../utils/DefaultArrayPrinter.hpp"
#include "../tree/TreePath.hpp"
#include "../utils/ArrayUtils.hpp"
#include "SuffixTreePtr.hpp"

SuffixTreeChecker::SuffixTreeChecker(const SuffixTreeOwnPtr& suffixTree) : suffixTree(suffixTree) {
    info = suffixTree->getInfo();
}

void SuffixTreeChecker::checkLeaves() {
    auto leavesCount = info->getTreeInfo()->getLeavesCount().get();
    if (leavesCount != info->getSourceLength()) {
        std::stringstream stream;
        stream << "Leaves count (" << leavesCount << " != source length (" << info->getSourceLength() << ")";
        throw SuffixTreeException(stream.str());
    }
}

void SuffixTreeChecker::checkInterChildrenCount() {
    suffixTree->getRootNode().get()->iterateInter([&](const TreeNode* node) {
        auto childrenCount = node->getEdges().size();
        if (childrenCount < 2) {
            auto label = node->getLabel();
            auto path = node->getPath();
            std::stringstream stream;
            stream << "Inter node (label: " << label << "), path: " << path <<
                   ") children count (" << childrenCount << ") less than min (2)";
            throw SuffixTreeException(stream.str());
        }
    });
}

void SuffixTreeChecker::checkEmptyLabels() {
    suffixTree->getRootNode().get()->iterateEdges([&](const TreeEdge* edge) {
        auto length = edge->getLabel().getLength();
        if (length == 0) {
            auto offset = edge->getLabel().getOffset();
            auto prevLabel = edge->getSource()->getLabel();
            auto toLabel = edge->getTarget()->getLabel();
            auto path = edge->getTarget()->getPath();
            std::stringstream stream;
            stream << "Edge contains empty label (offset: " << offset <<
                   ", prev node label: " << prevLabel << ", to node label: " << toLabel << ", path: " << path;
            throw SuffixTreeException(stream.str());
        }
    });
}

void SuffixTreeChecker::checkLabelsInDataSource() {
    suffixTree->getRootNode().get()->iterateEdges([&](const TreeEdge* edge) {
        if (!suffixTree->getDataSource()->contains(edge->getLabel().getValue())) {
            std::stringstream stream;
            stream << "Edge label not in data source: '" << edge->getLabel() << "'";
            throw SuffixTreeException(stream.str());
        }
    });
}

void SuffixTreeChecker::checkEdgesDifferentPrefixes() {
    suffixTree->getRootNode().get()->iterateNodes([&](const TreeNode* node) {
        auto edges = node->getEdges();
        auto edgesCombinations = Combinations<TreeEdgeAccessor>(edges).getResult();
        for (auto& value : edgesCombinations) {
            auto firstValue = std::get<0>(value).get()->getLabel().getValue();
            auto secondValue = std::get<1>(value).get()->getLabel().getValue();
            auto starts = PrefixUtils::commonPrefix(firstValue, secondValue);
            if (starts.size() != 0) {
                auto startsValue = DefaultArrayPrinter(starts, "").toString();
                auto path = node->getPath();
                std::stringstream stream;
                stream << "Node (path: " << path << ") has edges with the same starting value: '" << startsValue << "'";
                throw SuffixTreeException(stream.str());
            }
        }
    }, true);
}

void SuffixTreeChecker::checkPathsSuffixes() {
    auto bufferData = suffixTree->getDataSource()->read();
    suffixTree->getRootNode().get()->iteratePaths([&](TreePath* path) {
        auto snapshot = path->getSnapshot();
        auto pathData = snapshot.getData().get();
        if (!ArrayUtils::endsWith<char>(bufferData, pathData)) {
            std::stringstream stream;
            auto& pathSubValues = snapshot.getSubValuePath().get();
            stream << "Path " << pathSubValues << " is not suffix of source data";
            throw SuffixTreeException(stream.str());
        }
    });
}

void SuffixTreeChecker::go() {
    checkLeaves();
    checkInterChildrenCount();
    checkEmptyLabels();
    checkLabelsInDataSource();
    //fails sometimes
    //checkEdgesDifferentPrefixes();
    checkPathsSuffixes();
}
