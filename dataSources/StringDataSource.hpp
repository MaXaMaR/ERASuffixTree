#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "BaseDataSource.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class StringDataSource : public BaseDataSource, public MemoryLeakDetector<StringDataSource> {
public:

    static const char endSymbol = '$';

    StringDataSource(const std::string& value) {
        values.reserve(value.length() + 1);
        std::copy(value.begin(), value.end(), std::back_inserter(values));
        values.push_back(endSymbol);
    }

    bool startsWith(uint64 offset, const Container& value) override {
        return std::equal(values.begin() + offset, values.begin() + offset + value.size(), value.begin());
    }

    void iterate(IteratorFunc iterator) override {
        for (uint64 i = 0; i < values.size(); i++) {
            iterator(i, values[i]);
        }
    }

    uint64 length() const override {
        return values.size();
    }

    uint64 dataLength() const override {
        return length() - 1;
    }

protected:
    void readInternal(uint64 offset, uint64 length, Container& buffer) override {
        std::copy(values.begin() + offset, values.begin() + offset + length, buffer.begin());
    }

private:
    Container values;
};
