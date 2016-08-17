#pragma once

#include <memory>
#include <vector>

#include "../../utils/Types.hpp"
#include "../DataSourcePtr.hpp"
#include "../../prefixes/PrefixPtr.hpp"

class DataSourceLocation;

class Prefix;

class DataSourceLocations {
public:

    using LocationsResult = std::vector<DataSourceLocation>;

    using Prefixes = std::vector<PrefixPtr>;

    DataSourceLocations(const DataSourcePtr& dataSource) : dataSource(dataSource) {
    }

    LocationsResult locations(const Prefixes& prefixes, int64 maxCount = -1);

private:
    const DataSourcePtr& dataSource;
};
