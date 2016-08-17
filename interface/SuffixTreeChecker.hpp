#pragma once

#include <memory>

#include "SuffixTreePtr.hpp"
#include "SuffixTreeInfoPtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class SuffixTreeChecker : public MemoryLeakDetector<SuffixTreeChecker> {
public:

    SuffixTreeChecker(const SuffixTreeOwnPtr& suffixTree);

    void go();

private:

    void checkLeaves();
    void checkInterChildrenCount();
    void checkEmptyLabels();
    void checkLabelsInDataSource();
    void checkEdgesDifferentPrefixes();
    void checkPathsSuffixes();

    SuffixTreeOwnPtr suffixTree;
    SuffixTreeInfoPtr info;
};
