#pragma once

#include <iterator>

#include "../TreeNodeAccessor.hpp"
#include "../TreeEdgeAccessor.hpp"

#include "TreeNodeEdgeIterator.hpp"

class TreeNodeNodeIterator : public std::iterator<std::forward_iterator_tag, TreeNode*> {
public:

    TreeNodeNodeIterator(const TreeNodeNodeIterator& it)
            : edgeIt(it.edgeIt) {
    }

    TreeNodeNodeIterator(TreeNodeEdgeIterator edgeIt)
            : edgeIt(edgeIt) {
    }

    TreeNodeNodeIterator& operator++() {
        edgeIt++;
        return *this;
    };

    TreeNodeNodeIterator operator++(int) {
        TreeNodeNodeIterator tmp(*this);
        edgeIt++;
        return tmp;
    };

    bool operator==(const TreeNodeNodeIterator& other) const {
        return edgeIt == other.edgeIt;
    }

    bool operator!=(const TreeNodeNodeIterator& other) const {
        return !(*this == other);
    }

    bool isDefined() const {
        return edgeIt.isDefined();
    }

    TreeNodeAccessor getAccessor() const;

    TreeNode* operator->() const;

private:

    TreeNodeEdgeIterator edgeIt;
};
