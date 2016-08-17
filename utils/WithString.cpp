#include "WithString.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, WithString& value) {
    return stream << value.toString();
}

std::ostream& operator<<(std::ostream& stream, const WithString& value) {
    return stream << value.toStringConst();
}
