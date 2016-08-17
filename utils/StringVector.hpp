#pragma once

#include <string>
#include <vector>

class StringVector {
public:

    StringVector(const std::string& str) : str(str), vectorInit(false) {}

    const std::vector<char>& getVector();

private:
    const std::string& str;
    std::vector<char> buf;
    bool vectorInit;
};
