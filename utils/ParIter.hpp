#pragma once

#include <functional>
#include <condition_variable>
#include <mutex>

#include "Types.hpp"
#include "Work.hpp"

class ParIter;

class ParIterExecutor {
public:

    using Func = std::function<void(uint64 value)>;

    ParIterExecutor(ParIter& parIter, const Func& func, uint64 start, uint64 end)
            : parIter(parIter), func(func), start(start), end(end) {
    }

    void operator()();

private:
    ParIter& parIter;
    const Func& func;
    uint64 start;
    uint64 end;
};

class ParIter {
public:
    using Func = std::function<void(uint64 value)>;

    ParIter(uint64 start = 0, uint64 end = 0);

    void setPar(bool value);

    void change(uint64 start, uint64 end);

    void go(const Func& func);

    void notify();

private:

    void compute();

    void schedule(const Func& func);

    void waitCompletion();

    bool par;

    uint64 start;
    uint64 end;
    uint64 count;
    uint64 threadCount;
    std::mutex mtx;

    uint64 completedCount;
    std::condition_variable waiter;
    std::vector<ParIterExecutor> executors;
};
