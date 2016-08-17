#pragma once

#include <vector>

#include "../utils/MemoryLeakDetector.hpp"

#include "TreePathSnapshot.hpp"

class TreePath : public MemoryLeakDetector<TreePath> {
public:

    using Values = std::vector<TreeEdgeAccessor>;

    TreePath(Values& values) : values(values) {}

    Values& getValues() {
        return values;
    }

    TreePathSnapshot getSnapshot() {
        return {*this};
    }

private:
    Values& values;
};
