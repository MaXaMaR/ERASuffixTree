#pragma once

#include <iterator>

#include "../TreeNodeAccessor.hpp"
#include "../TreeEdgeAccessor.hpp"

class TreeNodeChildrenNodeIterator : public std::iterator<std::forward_iterator_tag, TreeNode*> {
public:

    TreeNodeChildrenNodeIterator(const TreeNodeChildrenNodeIterator& it) : value(it.value), lastEdge(it.lastEdge) {
    }

    TreeNodeChildrenNodeIterator(TreeNodeAccessor value, TreeEdgeAccessor lastEdge)
            : value(value), lastEdge(lastEdge) {
    }

    TreeNodeChildrenNodeIterator(TreeNodeAccessor value = {})
            : value(value) {
        init();
    }

    TreeNodeChildrenNodeIterator& operator++() {
        increment();
        return *this;
    };

    TreeNodeChildrenNodeIterator operator++(int) {
        TreeNodeChildrenNodeIterator tmp(*this);
        increment();
        return tmp;
    };

    bool operator==(const TreeNodeChildrenNodeIterator& other) const {
        return value == other.value && lastEdge == other.lastEdge;
    }

    bool operator!=(const TreeNodeChildrenNodeIterator& other) const {
        return !(*this == other);
    }

    TreeNodeAccessor getAccessor() const;

    TreeNode* operator->() const;

private:

    void init();

    void increment();

    TreeNodeAccessor value;
    TreeEdgeAccessor lastEdge;
};
