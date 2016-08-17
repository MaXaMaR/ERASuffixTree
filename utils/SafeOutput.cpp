#include "SafeOutput.hpp"
#include "SpinLock.hpp"
#include <mutex>

SpinLock SafeOutput::spinLock;

void SafeOutput::go(Func func) {
    std::lock_guard<SpinLock> guard(spinLock);
    func();
}
