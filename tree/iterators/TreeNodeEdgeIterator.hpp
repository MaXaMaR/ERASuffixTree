#pragma once

#include <iterator>

#include "../TreeNodeAccessor.hpp"
#include "../TreeEdgeAccessor.hpp"

class TreeNodeEdgeIterator : public std::iterator<std::forward_iterator_tag, TreeEdge*> {
public:

    TreeNodeEdgeIterator(const TreeNodeEdgeIterator& it)
            : value(it.value), lastEdge(it.lastEdge) {
    }

    TreeNodeEdgeIterator(TreeNodeAccessor value, TreeEdgeAccessor lastEdge)
            : value(value), lastEdge(lastEdge) {
    }

    TreeNodeEdgeIterator(TreeNodeAccessor value = {})
            : value(value) {
        init();
    }

    TreeNodeEdgeIterator& operator++() {
        increment();
        return *this;
    };

    TreeNodeEdgeIterator operator++(int) {
        TreeNodeEdgeIterator tmp(*this);
        increment();
        return tmp;
    };

    bool operator==(const TreeNodeEdgeIterator& other) const {
        return value == other.value && lastEdge == other.lastEdge;
    }

    bool operator!=(const TreeNodeEdgeIterator& other) const {
        return !(*this == other);
    }

    TreeEdgeAccessor getAccessor() const {
        return lastEdge;
    }

    bool isDefined() const {
        return lastEdge.isDefined();
    }

    TreeEdge* operator->() const {
        return lastEdge.get();
    }

private:

    void init();

    void backward();

    void increment();

    TreeNodeAccessor value;
    TreeEdgeAccessor lastEdge;
};
