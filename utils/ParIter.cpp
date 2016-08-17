#include "ParIter.hpp"
#include "Types.hpp"
#include <boost/thread/thread.hpp>
#include <boost/range/irange.hpp>
#include <functional>
#include <thread>
#include <vector>
#include <mutex>

ParIter::ParIter(uint64 start, uint64 end) : start(start), end(end), par(true) {
    compute();
}

void ParIter::setPar(bool value) {
    par = value;

    compute();
}

void ParIter::change(uint64 start, uint64 end) {
    this->start = start;
    this->end = end;

    compute();
}

void ParIter::compute() {
    count = end - start;
    threadCount = par ? boost::thread::hardware_concurrency() * 2 : 1;
}

void ParIterExecutor::operator()() {
    for (auto k : boost::irange(start, end)) {
        func(k);
    }
    parIter.notify();
}

void ParIter::notify() {
    std::unique_lock<std::mutex> guard(mtx);
    completedCount++;
    if (completedCount == threadCount) {
        waiter.notify_all();
    }
}

void ParIter::go(const Func& func) {
    executors.clear();
    executors.reserve(threadCount);

    completedCount = 0;

    schedule(func);

    waitCompletion();
}

void ParIter::schedule(const Func& func) {
    auto perThread = count / threadCount + (((count % threadCount) != 0) ? 1 : 0);
    for (auto i : boost::irange<uint64>(0, threadCount)) {
        auto thisStart = perThread * i;
        auto workCount = std::min<int64>(perThread, (int64) end - (int64) thisStart);
        if (workCount < 0) {
            workCount = 0;
        }
        auto thisEnd = thisStart + workCount;
        executors.emplace_back(*this, func, thisStart, thisEnd);
        if (threadCount > 1) {
            work.ioService.post(executors.back());
        } else {
            executors.back()();
        }
    }
}

void ParIter::waitCompletion() {
    if (threadCount > 1) {
        std::unique_lock<std::mutex> guard(mtx);
        while (completedCount < threadCount) {
            waiter.wait(guard);
        }
    }
}
