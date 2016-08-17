#pragma once

#include <memory>

#include "../../prefixes/PrefixPtr.hpp"
#include "../../utils/Types.hpp"

class DataSourceLocation {
public:
    DataSourceLocation() {
    }

    DataSourceLocation(const PrefixPtr& prefix, uint64 value) : prefix(prefix), value(value) {
    }

    PrefixPtr getPrefix() const {
        return prefix;
    }

    uint64 getValue() const {
        return value;
    }

private:
    PrefixPtr prefix;
    uint64 value;
};
