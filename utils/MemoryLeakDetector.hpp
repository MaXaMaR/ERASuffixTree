#pragma once

#include <string>

#include <boost/type_index.hpp>

#include "MemoryLeakDatabase.hpp"

#include "EmptyType.hpp"

template<typename T>
class MemoryLeakDetector {
public:

    using ClassName = std::conditional<MemoryLeakDatabase::Enabled, std::string, StringEmptyType>::type;

    MemoryLeakDetector() {
        initLeakDetector();
    }

    MemoryLeakDetector(const MemoryLeakDetector& other) {
        initLeakDetector();
    }

    MemoryLeakDetector(MemoryLeakDetector&& other) {
        initLeakDetector();
    }

    virtual ~MemoryLeakDetector() {
        if (MemoryLeakDatabase::Enabled) {
            MemoryLeakDatabase::onDelete(className);
        }
    }

    MemoryLeakDetector& operator=(const MemoryLeakDetector& other) = default;

    MemoryLeakDetector& operator=(MemoryLeakDetector&& other) = default;

private:

    void initLeakDetector() {
        if (MemoryLeakDatabase::Enabled) {
            className = boost::typeindex::type_id<T>().pretty_name();
            MemoryLeakDatabase::onCreate(className);
        }
    }

    ClassName className;

};
