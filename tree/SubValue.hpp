#pragma once

#include <memory>
#include <vector>

#include "../utils/Types.hpp"
#include "../utils/WithString.hpp"

#include "../config/SuffixTreeGlobalConfig.hpp"

#include "../dataSources/DataSource.hpp"
#include "../dataSources/DataSourcePtr.hpp"

#include "TreeRepository.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class Tree;

// size = vptr size + tree ptr size + offset num size + length num size
class SubValue : public WithString, public MemoryLeakDetector<SubValue> {
public:

    using RawValue = std::vector<char>;

    using TreeNumType = SuffixTreeGlobalConfig::TreeNumType;
    using OffsetType = SuffixTreeGlobalConfig::SubValueOffsetType;
    using LengthType = SuffixTreeGlobalConfig::SubValueLengthType;

//    SubValue() : treeNum(-1), offset(0), length(0) {
//    }
//
//    SubValue(TreeNumType treeNum, OffsetType offset)
//            : treeNum(treeNum), offset(offset) {
//        length = (LengthType) (getDataSource()->length() - offset);
//    }
//
//    SubValue(TreeNumType treeNum, OffsetType offset, LengthType length)
//            : treeNum(treeNum), offset(offset), length(length) {
//    }
//
//    TreeNumType getTreeNum() const {
//        return treeNum;
//    }

    SubValue() : tree(nullptr), offset(0), length(0) {
    }

    SubValue(Tree* tree, OffsetType offset)
            : tree(tree), offset(offset) {
        length = (LengthType) (getDataSource()->length() - offset);
    }

    SubValue(Tree* tree, OffsetType offset, LengthType length)
            : tree(tree), offset(offset), length(length) {
    }

    Tree* getTree() const {
        //return TreeRepository::get(treeNum);
        return tree;
    }

    DataSourcePtr getDataSource() const;

    bool isLeaf() const {
        return offset + length == getDataSource()->length();
    }

    OffsetType getOffset() const {
        return offset;
    }

    LengthType getLength() const {
        return length;
    }

    RawValue& getValue(RawValue& into) const;

    RawValue getValue() const;

    RawValue getPrintValue() const;

    std::string toString() override;

    std::string toStringConst() const override;

private:
    //TreeNumType treeNum;
    Tree* tree;
    OffsetType offset;
    LengthType length;
};
