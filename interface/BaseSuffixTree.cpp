#include "BaseSuffixTree.hpp"
#include <memory>
#include "BaseSuffixTreeInfo.hpp"
#include "SuffixTreeInfoPtr.hpp"

SuffixTreeInfoPtr BaseSuffixTree::getInfo() {
    if (info == nullptr) {
        info = std::make_shared<BaseSuffixTreeInfo>(shared_from_this());
    }
    return info;
}
