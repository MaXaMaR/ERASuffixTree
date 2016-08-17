#include "Prefix.hpp"
#include <memory>
#include "../dataSources/DataSource.hpp"
#include "../dataSources/locations/DataSourceLocations.hpp"
#include <string>
#include <sstream>
#include "../utils/DefaultArrayPrinter.hpp"
#include "../dataSources/locations/DataSourceLocation.hpp"
#include "../dataSources/DataSourcePtr.hpp"

Prefix::LocationsResult Prefix::locations(const DataSourcePtr& dataSource) {
    return DataSourceLocations(dataSource).locations(DataSourceLocations::Prefixes{shared_from_this()});
}

std::string Prefix::toString() {
    std::stringstream stream;
    stream << DefaultArrayPrinter(label, "") << " -> " << count;
    return stream.str();
}

void Prefix::add(const DataSourcePtr& dataSource) {
    count += locations(dataSource).size();
}
