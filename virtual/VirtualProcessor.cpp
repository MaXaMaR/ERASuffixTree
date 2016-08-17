#include "VirtualProcessor.hpp"
#include "../utils/Types.hpp"
#include "VirtualTree.hpp"
#include "VirtualTrees.hpp"
#include "../prepare/VirtualSubTreePrepare.hpp"
#include "../tree/DefaultTree.hpp"
#include "../tree/TreeRepository.hpp"
#include "../build/VirtualSubTreeBuilder.hpp"
#include "../tree/TreeMixer.hpp"
#include "../tree/TreeMerger.hpp"
#include "../dataSources/DataSourcePtr.hpp"
#include "VirtualTreesPtr.hpp"
#include "../utils/ParIter.hpp"
#include "../utils/SpinLock.hpp"
#include <mutex>
#include <thread>
#include "../tree/TreeSorter.hpp"

VirtualProcessor::VirtualProcessor(const DataSourcePtr& dataSource, const VirtualTreesPtr& virtualTrees,
                                   uint64 rangePerScan)
        : dataSource(dataSource), virtualTrees(virtualTrees), rangePerScan(rangePerScan) {
}

void VirtualProcessor::init() {
    tree = std::make_shared<DefaultTree>(dataSource);
    buildData = std::make_shared<std::vector<VirtualTreeBuildData>>();
}

void VirtualProcessor::createValues() {
    rootNodes.clear();
    auto values = virtualTrees->getValues();
    ParIter iter(0, values->size());
    SpinLock lock;
    iter.go([&](uint64 num) {
        auto virtualTree = (*values)[num];
        auto tree = virtualTree->getTree();
        auto virtualTreeBuilData = VirtualSubTreePrepare(dataSource, tree, virtualTree,
                                                         rangePerScan).getBuildData().get();
        auto subTreeBuilder = VirtualSubTreeBuilder(virtualTreeBuilData);
        auto newRootNode = subTreeBuilder.getRootNode();
        auto realNode = newRootNode.get();
        {
            std::lock_guard<SpinLock> guard(lock);
            rootNodes.push_back(realNode);
            buildData->push_back(virtualTreeBuilData);
        }
    });
}

void VirtualProcessor::sort() {
    rootNode = TreeMixer(tree.get(), rootNodes).getRootNode();
    TreeSorter(rootNode).go();
}

void VirtualProcessor::reconstruct() {
    rootNode = TreeMerger(dataSource, tree, rootNode).getNewRootNode().get();
}

void VirtualProcessor::go() {
    init();
    createValues();
    sort();
    reconstruct();
}
