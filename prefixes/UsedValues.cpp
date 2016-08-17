#include "UsedValues.hpp"
#include "../dataSources/DataSource.hpp"

void UsedValues::generate() {
    dataSource->iterate([&](auto offset, auto value) {
        values.insert(value);
    });
}
