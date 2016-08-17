#include "BaseSuffixTreeInfo.hpp"
#include "BaseSuffixTree.hpp"
#include "../dataSources/DataSource.hpp"
#include "../utils/Types.hpp"
#include "../tree/maintain/TreeInfo.hpp"
#include "SuffixTreeChecker.hpp"
#include "SuffixTreePtr.hpp"
#include "../tree/maintain/TreeInfoPtr.hpp"

SuffixTreePtr BaseSuffixTreeInfo::getSuffixTree() {
    return suffixTree;
}

uint64 BaseSuffixTreeInfo::getSourceLength() {
    auto suffixTreePtr = suffixTree.lock();
    if (suffixTreePtr == nullptr) {
        return 0;
    }
    return suffixTreePtr->getDataSource()->length();
}

TreeInfoPtr BaseSuffixTreeInfo::getTreeInfo() {
    auto suffixTreePtr = suffixTree.lock();
    if (suffixTreePtr == nullptr) {
        return nullptr;
    }
    return std::make_shared<TreeInfo>(suffixTreePtr->getRootNode());
}

void BaseSuffixTreeInfo::check() {
    auto suffixTreePtr = suffixTree.lock();
    if (suffixTreePtr == nullptr) {
        return;
    }
    SuffixTreeChecker(suffixTreePtr).go();
}
