#include "PrefixCalc.hpp"
#include "Prefix.hpp"
#include "../dataSources/DataSourcePtr.hpp"

PrefixCalc::PrefixCalc(const DataSourcePtr& dataSource, uint64 maxCount)
        : dataSource(dataSource), maxCount(maxCount), usedValues(dataSource) {
}

void PrefixCalc::init() {
    unprocessedPrefixes = std::make_shared<PrefixesValue>();
    generate();
}

void PrefixCalc::generate(const Values& startsWith) {
    for (auto& usedValue : usedValues.getValues()) {
        Values label = startsWith;
        label.push_back(usedValue);
        auto prefix = std::make_shared<Prefix>(label);
        unprocessedPrefixes->push_back(prefix);
    }
}

void PrefixCalc::goAll() {
    prefixes = std::make_shared<PrefixesValue>();
    while (!unprocessedPrefixes->empty()) {
        auto oldPrefixes = unprocessedPrefixes;
        unprocessedPrefixes = std::make_shared<PrefixesValue>();
        for (auto& prefix : *oldPrefixes) {
            prefix->add(dataSource);
            if (prefix->count > 0) {
                if (prefix->count < maxCount) {
                    prefixes->push_back(prefix);
                } else {
                    generate(prefix->getLabel());
                }
            }
        }
    }
}

PrefixCalc::Prefixes PrefixCalc::getResult() {
    if (prefixes == nullptr) {
        init();
        goAll();
    }
    return prefixes;
}
