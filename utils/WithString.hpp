#pragma once

#include <string>
#include <iostream>

class WithString {
public:
    WithString() = default;
    virtual ~WithString() = default;

    virtual std::string toString() = 0;

    virtual std::string toStringConst() const {
        return "";
    }

};

std::ostream& operator<<(std::ostream& stream, WithString& value);
std::ostream& operator<<(std::ostream& stream, const WithString& value);
