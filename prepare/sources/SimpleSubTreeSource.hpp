#pragma once

#include <memory>
#include <string>

#include "SubTreeSource.hpp"

#include "../../dataSources/DataSourcePtr.hpp"
#include "../../prefixes/PrefixPtr.hpp"

class SimpleSubTreeSource : public SubTreeSource {
public:

    SimpleSubTreeSource(const PrefixPtr& prefix) : prefix(prefix) {
        generate();
    }

    std::string toString() override;

    uint64 getStart() override {
        return start;
    }

    LocationsResult locations(const DataSourcePtr& dataSource) override;

private:
    void generate();

    PrefixPtr prefix;
    uint64 start;
};
