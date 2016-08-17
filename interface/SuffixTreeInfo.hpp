#pragma once

#include <memory>

#include "SuffixTreePtr.hpp"
#include "../tree/maintain/TreeInfoPtr.hpp"

#include "../utils/Types.hpp"


class SuffixTreeInfo {
public:

    virtual SuffixTreePtr getSuffixTree() = 0;

    virtual uint64 getSourceLength() = 0;

    virtual TreeInfoPtr getTreeInfo() = 0;

    virtual void check() = 0;

};
