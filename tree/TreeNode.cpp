#include "TreeNode.hpp"
#include "TreeEdge.hpp"
#include "TreePath.hpp"
#include <vector>
#include "../utils/ArrayUtils.hpp"
#include <algorithm>
#include <cmath>

TreeEdgeAccessor TreeNode::calcLastEdge() const {
    if (firstEdge.isEmpty()) {
        return {};
    }
    auto currentEdge = getFirstEdge();
    auto nextEdge = currentEdge->getNextEdge();
    while (nextEdge != nullptr) {
        currentEdge = nextEdge;
        nextEdge = currentEdge->getNextEdge();
    }
    return currentEdge->getAccessor();
}

void TreeNode::setFirstEdge(TreeEdge* firstEdge) {
    this->firstEdge = firstEdge->getAccessor();
    lastEdge = calcLastEdge();
}

void TreeNode::setSourceEdge(TreeEdge* sourceEdge) {
    this->sourceEdge = sourceEdge->getAccessor();
}

void TreeNode::setLastEdge(TreeEdge* lastEdge) {
    this->lastEdge = lastEdge->getAccessor();
}

void TreeNode::setLabel(LabelType label) {
    this->label = label;
}

void TreeNode::iterateChildrenEdgesRet(IterEdgeRetNonConstFunc iterator) const {
    auto currentEdge = getFirstEdge();
    while (currentEdge != nullptr) {
        auto res = iterator(currentEdge);
        if (!res) {
            return;
        }
        currentEdge = currentEdge->getNextEdge();
    }
}

void TreeNode::iterateChildrenEdges(IterEdgeNonConstFunc iterator) const {
    auto currentEdge = getFirstEdge();
    while (currentEdge != nullptr) {
        iterator(currentEdge);
        currentEdge = currentEdge->getNextEdge();
    }
}

void TreeNode::iterateAllEdgesRet(IterEdgeRetFunc iterator, bool* ret) const {
    if (ret != nullptr) {
        *ret = true;
    }
    iterateChildrenEdgesRet([&](const TreeEdge* edge) {
        auto res = iterator(edge);
        if (!res) {
            return false;
        }
        edge->getTarget()->iterateAllEdgesRet(iterator, &res);
        if (ret != nullptr) {
            *ret = res;
        }
        return res;
    });
}

void TreeNode::iterateAllEdges(IterEdgeFunc iterator) const {
    iterateChildrenEdges([&](const TreeEdge* edge) {
        iterator(edge);
        edge->getTarget()->iterateAllEdges(iterator);
    });
}

void TreeNode::iterateEdgesRet(IterEdgeRetFunc iterator, bool childrenOnly) const {
    if (!childrenOnly) {
        iterateAllEdgesRet(iterator);
    } else {
        iterateChildrenEdgesRet(iterator);
    }
}

void TreeNode::iterateEdges(IterEdgeFunc iterator, bool childrenOnly) const {
    if (!childrenOnly) {
        iterateAllEdges(iterator);
    } else {
        iterateChildrenEdges(iterator);
    }
}

void TreeNode::iterateChildrenNodesRet(IterNodeRetFunc iterator) const {
    iterateChildrenEdgesRet([&](const TreeEdge* edge) {
        return iterator(edge->getTarget());
    });
}

void TreeNode::iterateChildrenNodes(IterNodeFunc iterator) const {
    iterateChildrenEdges([&](const TreeEdge* edge) {
        iterator(edge->getTarget());
    });
}

void TreeNode::iterateAllNodesRet(IterNodeRetFunc iterator, bool withCurrent, bool* ret) const {
    if (ret != nullptr) {
        *ret = true;
    }
    if (withCurrent) {
        auto res = iterator(this);
        if (ret != nullptr) {
            *ret = res;
        }
        if (!res) {
            return;
        }
    }
    iterateChildrenNodesRet([&](const TreeNode* node) {
        auto res = iterator(node);
        if (ret != nullptr) {
            *ret = res;
        }
        if (!res) {
            return false;
        }
        node->iterateAllNodesRet(iterator, false, &res);
        if (ret != nullptr) {
            *ret = res;
        }
        return res;
    });
}

void TreeNode::iterateAllNodes(IterNodeFunc iterator, bool withCurrent) const {
    if (withCurrent) {
        iterator(this);
    }
    iterateChildrenNodes([&](const TreeNode* node) {
        iterator(node);
        node->iterateAllNodes(iterator, false);
    });
}

void TreeNode::iterateNodesRet(IterNodeRetFunc iterator, bool withCurrent, bool childrenOnly) const {
    if (!childrenOnly) {
        iterateAllNodesRet(iterator, withCurrent);
    } else {
        iterateChildrenNodesRet(iterator);
    }
}

void TreeNode::iterateNodes(IterNodeFunc iterator, bool withCurrent, bool childrenOnly) const {
    if (!childrenOnly) {
        iterateAllNodes(iterator, withCurrent);
    } else {
        iterateChildrenNodes(iterator);
    }
}

void TreeNode::iterateInterRet(IterNodeRetFunc iterator, bool* ret) const {
    if (ret != nullptr) {
        *ret = true;
    }
    iterateNodesRet([&](const TreeNode* node) {
        if (!node->isLeaf()) {
            auto res = iterator(node);
            if (ret != nullptr) {
                *ret = res;
            }
            if (!res) {
                return false;
            }
            node->iterateInterRet(iterator, &res);
            if (ret != nullptr) {
                *ret = res;
            }
            return res;
        }
        return true;
    });
}

void TreeNode::iterateInter(IterNodeFunc iterator) const {
    iterateNodes([&](const TreeNode* node) {
        if (!node->isLeaf()) {
            iterator(node);
            node->iterateInter(iterator);
        }
    });
}

void TreeNode::iterateLeavesRet(IterNodeRetFunc iterator, bool* ret) const {
    if (ret != nullptr) {
        *ret = true;
    }
    if (isLeaf()) {
        auto res = iterator(this);
        if (ret != nullptr) {
            *ret = res;
        }
        if (!res) {
            return;
        }
    } else {
        iterateChildrenEdgesRet([&](const TreeEdge* edge) {
            bool res;
            edge->getTarget()->iterateLeavesRet(iterator, &res);
            if (ret != nullptr) {
                *ret = res;
            }
            return res;
        });
    }
}

void TreeNode::iterateLeaves(IterNodeFunc iterator) const {
    if (isLeaf()) {
        iterator(this);
    } else {
        iterateChildrenEdges([&](const TreeEdge* edge) {
            edge->getTarget()->iterateLeaves(iterator);
        });
    }
}

void TreeNode::iteratePathsRet(IterPathRetNonConstFunc iterator, TreePath* prevPath, bool* ret) const {
    std::vector<TreeEdgeAccessor> values;
    TreePath tempPath(values);
    TreePath* path = prevPath;

    if (path == nullptr) {
        path = &tempPath;
    }

    if (ret != nullptr) {
        *ret = true;
    }

    iterateChildrenEdgesRet([&](TreeEdge* edge) {
        path->getValues().push_back(edge->getAccessor());
        bool res;
        edge->getTarget()->iteratePathsRet(iterator, path, &res);
        if (ret != nullptr) {
            *ret = res;
        }
        if (!res) {
            return false;
        }
        path->getValues().pop_back();
        return true;
    });

    if (isLeaf()) {
        auto res = iterator(path);
        if (ret != nullptr) {
            *ret = res;
        }
    }
}

void TreeNode::iteratePaths(IterPathNonConstFunc iterator, TreePath* prevPath) const {
    std::vector<TreeEdgeAccessor> values;
    TreePath tempPath(values);
    TreePath* path = prevPath;
    if (path == nullptr) {
        path = &tempPath;
    }

    iterateChildrenEdges([&](const TreeEdge* edge) {
        path->getValues().push_back(edge->getAccessor());
        edge->getTarget()->iteratePaths(iterator, path);
        path->getValues().pop_back();
    });

    if (isLeaf()) {
        iterator(path);
    }
}

std::vector<TreeEdgeAccessor>& TreeNode::getEdges(std::vector<TreeEdgeAccessor>& into) const {
    iterateChildrenEdges([&](const TreeEdge* edge) {
        into.push_back(edge->getAccessor());
    });
    return into;
}

std::vector<TreeEdgeAccessor> TreeNode::getEdges() const {
    std::vector<TreeEdgeAccessor> res;
    getEdges(res);
    return res;
}

void TreeNode::pruneEdges(const std::unordered_set<TreeNodeAccessor>& until) {
    std::vector<TreeEdgeAccessor> currentNextEdges;

    iterateChildrenEdges([&](TreeEdge* edge) {
        auto go = true;
        while (go) {
            go = false;
            currentNextEdges.clear();
            edge->getTarget()->getEdges(currentNextEdges);
            if (currentNextEdges.size() == 1) {
                auto& nextEdge = currentNextEdges[0];
                /*
                edge->setLabel(SubValue(edge->getLabel().getTreeNum(), edge->getLabel().getOffset(),
                                        edge->getLabel().getLength() + nextEdge->getLabel().getLength()));
                                        */
                edge->setLabel(SubValue(edge->getLabel().getTree(), edge->getLabel().getOffset(),
                                        edge->getLabel().getLength() + nextEdge->getLabel().getLength()));
                edge->setTarget(nextEdge->getTarget());
                go = true;
            }
        }
        if (until.find(edge->getTarget()->getAccessor()) == until.end()) {
            edge->getTarget()->pruneEdges(until);
        }
    });
}

SubValuePath TreeNode::getPath() const {
    SubValuePath res;
    getPath(res);
    return res;
}

SubValuePath& TreeNode::getPath(SubValuePath& into) const {
    auto sourceEdge = getSourceEdge();
    if (sourceEdge != nullptr) {
        sourceEdge->getSource()->getPath(into);
        into.getValues().push_back(sourceEdge->getLabel());
    }
    return into;
}

uint64 TreeNode::getMaxEdgeLength() const {
    uint64 edgeLength = 0;
    iterateChildrenEdges([&](TreeEdge* edge) {
        edgeLength = std::max<uint64>(edgeLength, edge->getLabel().getLength());
    });
    return edgeLength;
}

TreeNode* TreeNode::followPath(const std::vector<char>& path, uint64 offset, std::vector<char>* edgeLabel) {
    std::vector<char> tempEdgeLabel;
    TreeNode* foundNode = nullptr;

    if (path.size() == offset) {
        return this;
    }

    if (edgeLabel == nullptr) {
        edgeLabel = &tempEdgeLabel;
    }

    iterateChildrenEdgesRet([&](TreeEdge* edge) {
        edge->getLabel().getValue(*edgeLabel);
        if (path.size() >= edgeLabel->size() + offset) {
            if (ArrayUtils::startsWith(path, *edgeLabel, offset)) {
                auto res = edge->getTarget()->followPath(path, offset + edgeLabel->size());
                if (res != nullptr) {
                    foundNode = res;
                    return false;
                }
            }
        } else {
            if (std::equal(path.cbegin() + offset, path.cend(), edgeLabel->begin())) {
                foundNode = this;
                return false;
            }
        }
        return true;
    });

    return foundNode;
}
