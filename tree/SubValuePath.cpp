#include "SubValuePath.hpp"
#include <string>
#include <sstream>
#include <vector>
#include "../utils/ArrayPrinter.hpp"

std::string SubValuePath::toString() {
    return toStringConst();
}

std::string SubValuePath::toStringConst() const {
    std::vector<std::string> vals;
    for (auto& value : values) {
        std::stringstream stream;
        stream << "'" << value << "'";
        vals.push_back(stream.str());
    }
    return SimpleArrayPrinter<std::string, std::string>(vals, " ").toString();
}
