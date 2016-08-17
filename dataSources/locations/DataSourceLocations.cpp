#include "DataSourceLocations.hpp"
#include "../../utils/Types.hpp"
#include "../../prefixes/Prefix.hpp"
#include "../DataSource.hpp"
#include "DataSourceLocation.hpp"

DataSourceLocations::LocationsResult
DataSourceLocations::locations(const Prefixes& prefixes, int64 maxCount) {
    LocationsResult buffer;
    uint64 count = 0;
    for (uint64 offset = 0; offset < dataSource->length(); offset++) {
        for (uint64 prefixNum = 0; prefixNum < prefixes.size(); prefixNum++) {
            auto& prefix = prefixes[prefixNum];
            if (offset + prefix->getLabel().size() <= dataSource->length()) {
                if (dataSource->startsWith(offset, prefix->getLabel())) {
                    buffer.emplace_back(prefix, offset);
                    count++;
                    if (maxCount != -1 && maxCount == count) {
                        return buffer;
                    }
                }
            }
        }
    }
    return buffer;
}
