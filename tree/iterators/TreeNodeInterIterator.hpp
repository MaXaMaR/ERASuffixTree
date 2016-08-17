#pragma once

#include <iterator>

#include "../TreeNodeAccessor.hpp"
#include "../TreeEdgeAccessor.hpp"

#include "TreeNodeNodeIterator.hpp"

class TreeNodeInterIterator : public std::iterator<std::forward_iterator_tag, TreeNode*> {
public:

    TreeNodeInterIterator(const TreeNodeInterIterator& it)
            : nodeIt(it.nodeIt) {
    }

    TreeNodeInterIterator(TreeNodeNodeIterator nodeIt)
            : nodeIt(nodeIt) {
        init();
    }

    TreeNodeInterIterator& operator++() {
        increment();
        return *this;
    };

    TreeNodeInterIterator operator++(int) {
        TreeNodeInterIterator tmp(*this);
        increment();
        return tmp;
    };

    bool operator==(const TreeNodeInterIterator& other) const {
        return nodeIt == other.nodeIt;
    }

    bool operator!=(const TreeNodeInterIterator& other) const {
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
