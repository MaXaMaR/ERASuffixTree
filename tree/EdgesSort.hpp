#pragma once

#include <array>
#include <vector>

#include "TreeEdgeAccessor.hpp"

class TreeEdge;

class EdgesSort {
public:
    EdgesSort(std::array<std::vector<char>, 2>& buffers) : buffers(buffers) {};

    bool operator()(const TreeEdge* x, const TreeEdge* y);

    bool operator()(const TreeEdgeAccessor& x, const TreeEdgeAccessor& y);

private:
    std::array<std::vector<char>, 2>& buffers;
};
