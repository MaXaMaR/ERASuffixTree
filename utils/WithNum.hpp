#pragma once

#include "Types.hpp"

template<typename T>
class WithNum {
public:

    WithNum() {
        num = -1;
    }

    virtual T getNum() {
        return num;
    }

    virtual void setNum(T num) {
        this->num = num;
    }

protected:
    T num;
};
