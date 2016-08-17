#pragma once

#include <memory>

#include "SuffixTree.hpp"
#include "../tree/TreeNodeAccessor.hpp"
#include "../dataSources/DataSourcePtr.hpp"
#include "SuffixTreeConfigPtr.hpp"
#include "../tree/TreePtr.hpp"
#include "SuffixTreeInfoPtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class BaseSuffixTree : public SuffixTree, public std::enable_shared_from_this<BaseSuffixTree>, public MemoryLeakDetector<BaseSuffixTree> {
public:

    BaseSuffixTree(const DataSourcePtr& dataSource,
                   const SuffixTreeConfigPtr& config, const TreePtr& rootTree,
                   TreeNodeAccessor rootNode, const BuildData& buildData)
            : dataSource(dataSource), config(config), rootTree(rootTree),
              rootNode(rootNode), buildData(buildData) {
    }

    DataSourcePtr getDataSource() const override {
        return dataSource;
    }

    SuffixTreeConfigPtr getConfig() const override {
        return config;
    }

    TreePtr getRootTree() const override {
        return rootTree;
    }

    TreeNodeAccessor getRootNode() const override {
        return rootNode;
    }

    BuildData getBuildData() const override {
        return buildData;
    }

    SuffixTreeInfoPtr getInfo() override;

private:
    DataSourcePtr dataSource;
    SuffixTreeConfigPtr config;
    TreePtr rootTree;
    TreeNodeAccessor rootNode;
    SuffixTreeInfoPtr info;
    BuildData buildData;
};
