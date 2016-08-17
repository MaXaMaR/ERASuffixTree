#pragma once

// ERA Suffix Tree

#include <memory>
#include <vector>

#include "../tree/TreeNodeAccessor.hpp"
#include "../dataSources/DataSourcePtr.hpp"
#include "SuffixTreeConfigPtr.hpp"
#include "../tree/TreePtr.hpp"
#include "SuffixTreeInfoPtr.hpp"

#include "../virtual/VirtualProcessor.hpp"

class SuffixTree {
public:

    using BuildData = VirtualProcessor::BuildData;

    virtual DataSourcePtr getDataSource() const = 0;

    virtual SuffixTreeConfigPtr getConfig() const = 0;

    virtual TreePtr getRootTree() const = 0;

    virtual BuildData getBuildData() const = 0;

    virtual TreeNodeAccessor getRootNode() const = 0;

    virtual SuffixTreeInfoPtr getInfo() = 0;

};
