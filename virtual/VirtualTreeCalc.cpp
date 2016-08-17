#include "VirtualTreeCalc.hpp"
#include <algorithm>
#include "../prefixes/Prefix.hpp"
#include <memory>
#include <unordered_set>
#include "VirtualTree.hpp"
#include "VirtualTrees.hpp"
#include "../dataSources/DataSourcePtr.hpp"
#include "../prefixes/PrefixPtr.hpp"
#include "VirtualTreePtr.hpp"
#include "VirtualTreesPtr.hpp"

VirtualTreeCalc::VirtualTreeCalc(const DataSourcePtr& dataSource, const PrefixesValue& prefixes,
                                 uint64 maxCount)
        : dataSource(dataSource), prefixes(prefixes), maxCount(maxCount) {

    values = LazyValue<VirtualTreesPtr> {
            [=](VirtualTreesPtr& value) {
                value = generateValues();
            }
    };

}

void VirtualTreeCalc::go() {
    auto treeValues = std::make_shared<std::vector<PrefixPtr>>();
    auto firstPrefixIndex = *prefixesIndexes.begin();
    auto firstPrefix = (*prefixes)[firstPrefixIndex];
    treeValues->push_back(firstPrefix);
    prefixesIndexes.erase(firstPrefixIndex);
    auto treeSum = firstPrefix->count;
    std::unordered_set<uint64> removeIndexes;
    for (auto prefixIndex : prefixesIndexes) {
        auto prefix = (*prefixes)[prefixIndex];
        if ((prefix->count + treeSum) < maxCount) {
            treeValues->push_back(prefix);
            treeSum += prefix->count;
            removeIndexes.insert(prefixIndex);
        }
    }
    for (auto value : removeIndexes) {
        prefixesIndexes.erase(value);
    }
    auto tree = std::make_shared<VirtualTree>(dataSource, treeValues);
    generatingValues->push_back(tree);
}

void VirtualTreeCalc::goAll() {
    while (prefixesIndexes.size() > 0) {
        go();
    }
}

void VirtualTreeCalc::prepare() {
    std::sort(prefixes->begin(), prefixes->end(), [&](auto& first, auto& second) {
        return second->count - first->count;
    });
    auto count = prefixes->size();
    prefixesIndexes.clear();
    for (uint64 i = 0; i < count; i++) {
        prefixesIndexes.insert(i);
    }
}

VirtualTreesPtr VirtualTreeCalc::generateValues() {

    generatingValues = std::make_shared<std::vector<VirtualTreePtr>>();

    prepare();
    goAll();

    auto res = std::make_shared<VirtualTrees>(dataSource, generatingValues);

    return res;
}
