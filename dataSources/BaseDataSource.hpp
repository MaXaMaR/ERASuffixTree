#pragma once

#include <cmath>
#include <algorithm>

#include "DataSource.hpp"

#include "../utils/Types.hpp"

class BaseDataSource : public DataSource {
public:

    Container read() override {
        return read(0);
    }

    Container read(uint64 offset) override {
        return read(offset, (uint64) (length() - offset));
    }

    void read(uint64 offset, Container& buffer) override {
        const auto readCount = std::min((uint64) (length() - offset), (uint64) buffer.size());
        if (readCount < buffer.size()) {
            buffer.resize(readCount);
        }
        readInternal(offset, readCount, buffer);
    }

    Container read(uint64 offset, uint64 length, bool pad = false) override;

    bool contains(const Container& value) override;

protected:
    virtual void readInternal(uint64 offset, uint64 length, Container& buffer) = 0;
};
