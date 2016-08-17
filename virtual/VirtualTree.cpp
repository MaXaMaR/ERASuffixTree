#include "VirtualTree.hpp"
#include "../utils/ArrayPrinter.hpp"
#include <sstream>
#include "../prefixes/Prefix.hpp"
#include "../prefixes/PrefixPtr.hpp"
#include "../utils/LazyValue.hpp"
#include "../tree/TreePtr.hpp"
#include "../tree/DefaultTree.hpp"
#include <string>
#include <memory>

VirtualTree::VirtualTree(const DataSourcePtr& dataSource, const PrefixesValue& prefixes)
        : dataSource(dataSource), prefixes(prefixes) {
    init();
}

void VirtualTree::init() {
    tree = std::make_shared<DefaultTree>(dataSource);
}

std::string VirtualTree::toString() {
    std::stringstream stream;

    stream << "Virtual Tree:" << std::endl
           << ArrayPrinter<PrefixPtr, Prefix, std::string>
                   (*prefixes, [&](auto& prefix) { return *prefix; },
                    "\n") << std::endl;

    return stream.str();
}
