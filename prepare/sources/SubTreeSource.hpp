#pragma once

#include <memory>

#include "../../utils/Types.hpp"
#include "../../utils/WithString.hpp"

#include "../../dataSources/locations/DataSourceLocations.hpp"

#include "../../dataSources/DataSourcePtr.hpp"

class SubTreeSource : public WithString {
public:

    using LocationsResult = DataSourceLocations::LocationsResult;

    virtual uint64 getStart() = 0;

    virtual LocationsResult locations(const DataSourcePtr& dataSource) = 0;

};
