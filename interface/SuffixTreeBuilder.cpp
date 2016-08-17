#include "SuffixTreeBuilder.hpp"
#include "../prefixes/PrefixCalc.hpp"
#include "SuffixTreeConfig.hpp"
#include "../virtual/VirtualTreeCalc.hpp"
#include "../virtual/VirtualProcessor.hpp"
#include "BaseSuffixTree.hpp"
#include <memory>
#include "../prefixes/Prefix.hpp"
#include "SuffixTreePtr.hpp"

SuffixTreeOwnPtr SuffixTreeBuilder::build() {
    auto prefixCalc = PrefixCalc(dataSource, config->getMaxCountPerVirtualTree());
    auto virtualTreeCalc = VirtualTreeCalc(dataSource, prefixCalc.getResult(), config->getMaxCountPerVirtualTree());
    auto virtualTrees = virtualTreeCalc.getValues().get();
    auto processor = VirtualProcessor(dataSource, virtualTrees, config->getRangePerScan());
    processor.go();
    auto rootTree = processor.getTree();
    auto rootNode = processor.getRootNode();
    auto buildData = processor.getBuildData();
    return std::make_shared<BaseSuffixTree>(dataSource, config, rootTree, rootNode, buildData);
}
