#include "SubValue.hpp"
#include "Tree.hpp"
#include "../utils/DefaultArrayPrinter.hpp"
#include <string>
#include "../dataSources/DataSourcePtr.hpp"

DataSourcePtr SubValue::getDataSource() const {
    auto tree = getTree();
    if (tree == nullptr) {
        return nullptr;
    }
    return tree->getDataSource();
}

SubValue::RawValue& SubValue::getValue(RawValue& into) const {
    into.resize(length);
    getDataSource()->read(offset, into);
    return into;
}

SubValue::RawValue SubValue::getValue() const {
    RawValue res;
    getValue(res);
    return res;
}

SubValue::RawValue SubValue::getPrintValue() const {
    RawValue res = getValue();
    if (isLeaf()) {
        res.pop_back();
    }
    return res;
}

std::string SubValue::toString() {
    return toStringConst();
}

std::string SubValue::toStringConst() const {
    return DefaultArrayPrinter(getPrintValue(), "").toString();
}
