#pragma once

#include <iterator>

#include "../TreeNodeAccessor.hpp"
#include "../TreeEdgeAccessor.hpp"

class TreeNodeChildrenEdgeIterator : public std::iterator<std::forward_iterator_tag, TreeEdge*> {
public:

    TreeNodeChildrenEdgeIterator(const TreeNodeChildrenEdgeIterator& it) : value(it.value), lastEdge(it.lastEdge) {
    }

    TreeNodeChildrenEdgeIterator(TreeNodeAccessor value, TreeEdgeAccessor lastEdge)
            : value(value), lastEdge(lastEdge) {
    }

    TreeNodeChildrenEdgeIterator(TreeNodeAccessor value = {})
            : value(value) {
        init();
    }

    TreeNodeChildrenEdgeIterator& operator++() {
        increment();
        return *this;
    };

    TreeNodeChildrenEdgeIterator operator++(int) {
        TreeNodeChildrenEdgeIterator tmp(*this);
        increment();
        return tmp;
    };

    bool operator==(const TreeNodeChildrenEdgeIterator& other) const {
        return value == other.value && lastEdge == other.lastEdge;
    }

    bool operator!=(const TreeNodeChildrenEdgeIterator& other) const {
        return !(*this == other);
    }

    TreeEdgeAccessor getAccessor() const {
        return lastEdge;
    }

    TreeEdge* operator->() const {
        return lastEdge.get();
    }

private:

    void init();

    void increment();

    TreeNodeAccessor value;
    TreeEdgeAccessor lastEdge;
};
