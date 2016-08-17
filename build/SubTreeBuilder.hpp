#pragma once

#include <memory>

#include "SubTreeBuildData.hpp"

#include "../tree/SubValue.hpp"

#include "../tree/TreeNodeAccessor.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class DataSource;

class SubTreeBuilder : public MemoryLeakDetector<SubTreeBuilder> {
public:

    using DataSourceValue = std::shared_ptr<DataSource>;

    SubTreeBuilder(SubTreeBuildData& data) : data(data) {
        init();
    }

    void go();

private:

    void clearRoot();

    void init();

    DataSourceValue dataSource;
    SubTreeBuildData& data;
    TreeNodeAccessor firstLeaf;
    SubValue firstEdgeToLeafLabel;
};
