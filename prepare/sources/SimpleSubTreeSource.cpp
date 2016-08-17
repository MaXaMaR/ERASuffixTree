#include "SimpleSubTreeSource.hpp"
#include "../../dataSources/DataSourcePtr.hpp"
#include "../../prefixes/Prefix.hpp"
#include <string>
#include "../../dataSources/locations/DataSourceLocation.hpp"

SimpleSubTreeSource::LocationsResult SimpleSubTreeSource::locations(const DataSourcePtr& dataSource) {
    return prefix->locations(dataSource);
}

void SimpleSubTreeSource::generate() {
    start = prefix->getLabel().size();
}

std::string SimpleSubTreeSource::toString() {
    return prefix->toString();
}
