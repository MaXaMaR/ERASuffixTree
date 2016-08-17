#pragma once

#include "../utils/Types.hpp"

class SuffixTreeConfig {
public:

    SuffixTreeConfig(uint64 maxCountPerVirtualTree, uint64 rangePerScan)
            : maxCountPerVirtualTree(maxCountPerVirtualTree), rangePerScan(rangePerScan) {
    }

    uint64 getMaxCountPerVirtualTree() const {
        return maxCountPerVirtualTree;
    }

    uint64 getRangePerScan() const {
        return rangePerScan;
    }

private:
    uint64 maxCountPerVirtualTree;
    uint64 rangePerScan;
};
