#pragma once

#include <vector>

class PrefixUtils {
public:

    using Value = std::vector<char>;

    // sequental scan

    static Value& commonPrefix(const Value& first, const Value& second, Value& into);

    static Value commonPrefix(const Value& first, const Value& second);

};
