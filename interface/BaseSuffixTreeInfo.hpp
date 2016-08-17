#pragma once

#include <memory>

#include "SuffixTreeInfo.hpp"
#include "SuffixTreePtr.hpp"
#include "../utils/Types.hpp"

#include "../tree/maintain/TreeInfoPtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class BaseSuffixTree;

class BaseSuffixTreeInfo : public SuffixTreeInfo, public MemoryLeakDetector<BaseSuffixTreeInfo> {
public:

    BaseSuffixTreeInfo(const SuffixTreePtr& suffixTree) : suffixTree(suffixTree) {}

    SuffixTreePtr getSuffixTree() override;

    uint64 getSourceLength() override;

    TreeInfoPtr getTreeInfo() override;

    void check() override;

private:
    SuffixTreePtr suffixTree;
};
