#include "VirtualSubTreePrepare.hpp"
#include "../utils/LazyValue.hpp"
#include <memory>
#include "../utils/Types.hpp"
#include "../virtual/VirtualTree.hpp"
#include "SubTreePrepare.hpp"
#include "sources/SimpleSubTreeSource.hpp"
#include "../dataSources/locations/DataSourceLocation.hpp"
#include "../dataSources/DataSourcePtr.hpp"
#include "../virtual/VirtualTreePtr.hpp"
#include "../tree/TreePtr.hpp"

VirtualSubTreePrepare::VirtualSubTreePrepare(const DataSourcePtr& dataSource, const TreePtr& tree,
                                             const VirtualTreePtr& virtualTree, uint64 rangePerScan)
        : dataSource(dataSource), virtualTree(virtualTree), rangePerScan(rangePerScan), tree(tree) {

    buildData = LazyValue<BuildData> {
            [=](auto& value) {
                generate(value);
            }
    };

}

void VirtualSubTreePrepare::generate(BuildData& buildData) {
    buildData = std::make_shared<std::vector<SubTreeBuildData>>();
    uint64 size = virtualTree->getPrefixes()->size();
    for (uint64 i = 0; i < size; i++) {
        auto prefix = (*virtualTree->getPrefixes())[i];
        auto source = std::make_shared<SimpleSubTreeSource>(prefix);
        buildData->push_back(SubTreeBuildData(prefix, tree));
        auto& prepareResult = buildData->back().getPrepareResult();
        SubTreePrepare(dataSource, source, rangePerScan).go(prepareResult);
    }
}
