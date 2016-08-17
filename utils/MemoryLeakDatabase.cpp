#include "MemoryLeakDatabase.hpp"
#include <string>
#include <unordered_map>
#include <mutex>
#include "SpinLock.hpp"
#include <iostream>
#include <exception>
#include <sstream>
#include "Types.hpp"

std::unordered_map<std::string, int64> MemoryLeakDatabase::counts;

SpinLock MemoryLeakDatabase::lock;

const bool MemoryLeakDatabase::Enabled;

void MemoryLeakDatabase::onCreate(const std::string& className) {
    std::lock_guard<SpinLock> guard(lock);
    if (counts.find(className) == counts.end()) {
        counts[className] = 0;
    }
    counts[className]++;
}

void MemoryLeakDatabase::onDelete(const std::string& className) {
    std::lock_guard<SpinLock> guard(lock);
    if (counts.find(className) == counts.end()) {
        std::stringstream stream;
        stream << "Class " << className << " was deleted twice";
        throw std::runtime_error(stream.str());
    }
    counts[className]--;
    if (counts[className] == 0) {
        counts.erase(className);
    }
}

std::unordered_map<std::string, int64> MemoryLeakDatabase::getCounts() {
    std::lock_guard<SpinLock> guard(lock);
    return counts;
};

void MemoryLeakDatabase::dump() {
    std::lock_guard<SpinLock> guard(lock);
    if (counts.size() > 0) {
        for (auto& vals: counts) {
            std::cout << vals.first << ": " << vals.second << std::endl;
        }
    } else {
        std::cout << "No memory leaks detected" << std::endl;
    }
}
