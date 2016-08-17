#pragma once

#include "../utils/LazyValue.hpp"

#include "TreeEdgeAccessor.hpp"

#include "SubValuePath.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class TreePath;

class TreePathSnapshot : public MemoryLeakDetector<TreePathSnapshot> {
public:

    using Data = std::vector<char>;

    TreePathSnapshot(TreePath& path) : path(path) {
        init();
    }

    LazyValue<Data>& getData() {
        return data;
    }

    LazyValue<SubValuePath>& getSubValuePath() {
        return subValuePath;
    }

private:

    void init();

    Data generateData();

    SubValuePath generateSubValuePath();

    TreePath& path;
    LazyValue<Data> data;
    LazyValue<SubValuePath> subValuePath;
};
