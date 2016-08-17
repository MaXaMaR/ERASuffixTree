#pragma once

#include <vector>
#include <functional>

#include "../utils/Types.hpp"

class DataSource {
public:

    using Container = std::vector<char>;
    using IteratorFunc = std::function<void(uint64, char)>;

    virtual Container read() = 0;

    virtual Container read(uint64 offset) = 0;

    virtual void read(uint64 offset, Container& buffer) = 0;

    virtual Container read(uint64 offset, uint64 length, bool pad = false) = 0;

    virtual bool startsWith(uint64 offset, const Container& data) = 0;

    // unoptimized, may sequentally scan
    virtual bool contains(const Container& value) = 0;

    virtual uint64 dataLength() const = 0;

    virtual uint64 length() const = 0;

    virtual void iterate(IteratorFunc iterator) = 0;

};
