#pragma once

#include <iterator>

#include "../TreeNodeAccessor.hpp"
#include "../TreeEdgeAccessor.hpp"

#include "TreeNodeNodeIterator.hpp"

class TreeNodeLeafIterator : public std::iterator<std::forward_iterator_tag, TreeNode*> {
public:

    TreeNodeLeafIterator(const TreeNodeLeafIterator& it)
            : nodeIt(it.nodeIt) {
    }

    TreeNodeLeafIterator(TreeNodeNodeIterator nodeIt)
            : nodeIt(nodeIt) {
        init();
    }

    TreeNodeLeafIterator& operator++() {
        increment();
        return *this;
    };

    TreeNodeLeafIterator operator++(int) {
        TreeNodeLeafIterator tmp(*this);
        increment();
        return tmp;
    };

    bool operator==(const TreeNodeLeafIterator& other) const {
        return nodeIt == other.nodeIt;
    }

    bool operator!=(const TreeNodeLeafIterator& other) const {
        return !(*this == other);
    }

    bool isDefined() const {
        return nodeIt.isDefined();
    }

    TreeNodeAccessor getAccessor() const {
        return nodeIt.getAccessor();
    }

    TreeNode* operator->() const {
        return nodeIt.operator->();
    }

private:

    void init();

    void detect();

    void increment();

    TreeNodeNodeIterator nodeIt;
};
