#pragma once

#include <unordered_map>
#include <string>

#include "Types.hpp"

#include "SpinLock.hpp"

class MemoryLeakDatabase {
public:

    static constexpr bool Enabled = false;

    static void onCreate(const std::string& className);

    static void onDelete(const std::string& className);

    static std::unordered_map<std::string, int64> getCounts();

    static void dump();

private:
    static std::unordered_map<std::string, int64> counts;
    static SpinLock lock;
};
