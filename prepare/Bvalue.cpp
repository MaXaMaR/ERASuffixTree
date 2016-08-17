#include "Bvalue.hpp"
#include <string>
#include <sstream>

std::string Bvalue::toString() {
    std::stringstream stream;
    stream << "(" << firstValue << ", " << secondValue << ", " << offset << ")";
    return stream.str();
}
