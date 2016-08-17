#pragma once

#include <memory>

#include "../dataSources/DataSourcePtr.hpp"
#include "SuffixTreeConfigPtr.hpp"
#include "SuffixTreePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class SuffixTreeBuilder : public MemoryLeakDetector<SuffixTreeBuilder> {
public:

    SuffixTreeBuilder(const DataSourcePtr& dataSource, const SuffixTreeConfigPtr& config)
            : dataSource(dataSource), config(config) {
    }

    SuffixTreeOwnPtr build();

private:
    DataSourcePtr dataSource;
    SuffixTreeConfigPtr config;
};
