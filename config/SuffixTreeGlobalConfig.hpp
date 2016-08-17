#pragma once

#include "../utils/Types.hpp"

class SuffixTreeGlobalConfig {
public:
    using SubValueOffsetType = uint32;
    using SubValueLengthType = uint32;
    using TreeNodeLabelType = int32;
    using TreeNodeNumType = int32;
    using TreeEdgeNumType = int32;
    using TreeNumType = int16;
};
