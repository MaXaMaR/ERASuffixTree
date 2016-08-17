#pragma once

#include <functional>
#include <vector>
#include <string>
#include <sstream>

#include "WithString.hpp"
#include "Types.hpp"

template<typename T, typename TN, typename S>
class ArrayPrinter : public WithString {
public:

    using MapFunc = std::function<TN(const T&)>;

    ArrayPrinter(const std::vector<T>& values, MapFunc func, const S& separator)
            : values(values), func(func), separator(separator) {
    }

    std::string toString() override {
        return toStringConst();
    }

    std::string toStringConst() const override {
        uint64 count = 0;
        std::stringstream stream;
        for (auto& value:values) {
            if (count > 0) {
                stream << separator;
            }
            stream << func(value);
            count++;
        }
        return stream.str();
    }

private:
    const std::vector<T>& values;
    MapFunc func;
    const S& separator;
};

template<typename T, typename S>
class SimpleArrayPrinter : public ArrayPrinter<T, T, S> {
public:

    SimpleArrayPrinter(const std::vector<T>& values, const S& separator)
            : ArrayPrinter<T, T, S>(values, [&](const T& value) { return value; }, separator) {
    }

};
