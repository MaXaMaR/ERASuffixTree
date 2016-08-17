#pragma once

#include <memory>

#include "../prepare/SubTreePrepareResult.hpp"

#include "../tree/TreeNodeAccessor.hpp"

#include "../prefixes/PrefixPtr.hpp"
#include "../tree/TreePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class SubTreeBuildData : public MemoryLeakDetector<SubTreeBuildData> {
public:

    SubTreeBuildData(SubTreeBuildData&& data) = default;

    SubTreeBuildData(const PrefixPtr& prefix, const TreePtr& tree);

    SubTreePrepareResult& getPrepareResult() {
        return prepareResult;
    }

    PrefixPtr getPrefix() const {
        return prefix;
    }

    TreePtr getTree() const {
        return tree;
    }

    TreeNodeAccessor getRootNode() const {
        return rootNode;
    }

    SubTreeBuildData& operator=(SubTreeBuildData&& other) = default;

private:

    void init();

    SubTreePrepareResult prepareResult;
    PrefixPtr prefix;
    TreePtr tree;
    TreeNodeAccessor rootNode;
};
