#pragma once

#include <memory>

class SuffixTree;

using SuffixTreePtr = std::weak_ptr<SuffixTree>;
using SuffixTreeOwnPtr = std::shared_ptr<SuffixTree>;
