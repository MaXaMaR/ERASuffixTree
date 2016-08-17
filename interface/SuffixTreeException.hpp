#pragma once

#include <string>
#include <exception>

class SuffixTreeException : public std::exception {
public:
    SuffixTreeException(const std::string& str) : msg(str) {}

    char const* what() const noexcept {
        return msg.c_str();
    }

private:
    std::string msg;
};
