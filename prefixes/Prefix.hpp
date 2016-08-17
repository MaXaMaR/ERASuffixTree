#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "../utils/WithString.hpp"
#include "../utils/Types.hpp"
#include "../utils/ArrayPrinter.hpp"
#include "../dataSources/locations/DataSourceLocations.hpp"
#include "../dataSources/DataSourcePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Prefix : public WithString, public std::enable_shared_from_this<Prefix>, public MemoryLeakDetector<Prefix> {
public:

    using Label = std::vector<char>;

    using LocationsResult = DataSourceLocations::LocationsResult;

    uint64 count;

    Prefix(const Label& label) : label(label), count(0) {}

    void add(const DataSourcePtr& dataSource);

    std::string toString() override;

    const Label& getLabel() const {
        return label;
    }

    LocationsResult locations(const DataSourcePtr& dataSource);

private:
    Label label;
};
