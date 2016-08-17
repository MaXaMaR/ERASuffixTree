#include "EdgesSort.hpp"
#include "../utils/ArrayOrdering.hpp"
#include "TreeEdge.hpp"
#include "SubValue.hpp"

bool EdgesSort::operator()(const TreeEdge* x, const TreeEdge* y) {
    x->getLabel().getValue(buffers[0]);
    y->getLabel().getValue(buffers[1]);
    return compareArrays(buffers[0], buffers[1]);
}

bool EdgesSort::operator()(const TreeEdgeAccessor& x, const TreeEdgeAccessor& y) {
    return (*this)(x.get(), y.get());
}
