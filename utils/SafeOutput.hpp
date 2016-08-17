#pragma once

#include <functional>

#include "SpinLock.hpp"

class SafeOutput {
public:

    using Func = std::function<void()>;

    static void go(Func func);

private:
    static SpinLock spinLock;
};
