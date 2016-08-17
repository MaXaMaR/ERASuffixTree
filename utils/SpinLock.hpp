#pragma once

#import <atomic>

class SpinLock {
public:

    void lock() {
        while (flag.test_and_set(std::memory_order::memory_order_acquire)) {}
    }

    void unlock() {
        flag.clear(std::memory_order::memory_order_release);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};
