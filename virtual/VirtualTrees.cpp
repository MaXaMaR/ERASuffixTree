#include "VirtualTrees.hpp"
#include <memory>
#include <vector>
#include <algorithm>
#include "VirtualTree.hpp"
#include "../utils/ArrayPrinter.hpp"
#include <string>
#include "../dataSources/DataSourcePtr.hpp"
#include "../prefixes/PrefixPtr.hpp"
#include "VirtualTreePtr.hpp"

VirtualTrees::VirtualTrees(const DataSourcePtr& dataSource, const Values& values)
        : dataSource(dataSource), values(values) {

    prefixes = LazyValue<PrefixesValues> {
            [=](PrefixesValues& prefixesValues) {
                prefixesValues = std::make_shared<std::vector<PrefixPtr>>();
                for (auto& value : *values) {
                    auto prefixes = value->getPrefixes();
                    std::copy(prefixes->begin(), prefixes->end(), std::back_inserter(*prefixesValues));
                }
            }
    };

}

std::string VirtualTrees::toString() {
    return ArrayPrinter<VirtualTreePtr, VirtualTree, std::string>
            (*values, [&](const auto& value) { return *value; }, "\n").toString();
}
