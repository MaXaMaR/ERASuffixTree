#pragma once

#include <functional>
#include <boost/optional.hpp>
#include <mutex>
#include <boost/thread/recursive_mutex.hpp>

#include "MemoryLeakDetector.hpp"

template<typename T>
class LazyValue : public MemoryLeakDetector<LazyValue<T>> {
public:
    using Func = std::function<void(T& value)>;
    using ThisLazyValue = LazyValue<T>;
    using Mtx = boost::recursive_mutex;
    using ThisValue = T;

    LazyValue() : func(nullptr), isset(false) {}

    LazyValue(const Func& func) : func(func), isset(false) {}

    LazyValue(const ThisLazyValue& otherValue)
            : func(otherValue.func), isset(otherValue.isset),
              value(otherValue.value) {}

    LazyValue(ThisLazyValue&& otherValue)
            : func(std::move(otherValue.func)), isset(otherValue.isset),
              value(std::move(otherValue.value)) {}

    T& get() {
        std::lock_guard<Mtx> guard(mtx);
        if (!isset) {
            if (func) {
                func(value);
                isset = true;
            }
        }
        return value;
    }

    void set(const T& value) {
        std::lock_guard<Mtx> guard1(mtx);
        this->value = value;
        isset = true;
    }

    ThisLazyValue& operator=(const Func& func) {
        std::lock_guard<Mtx> guard1(mtx);

        this->isset = false;
        this->func = func;

        return *this;
    }

    ThisLazyValue& operator=(ThisLazyValue&& otherValue) {
        if (&otherValue == this) {
            return *this;
        }

        std::lock_guard<Mtx> guard0(otherValue.mtx);
        std::lock_guard<Mtx> guard1(mtx);

        this->isset = otherValue.isset;
        this->func = std::move(otherValue.func);
        this->value = std::move(otherValue.value);

        otherValue.isset = false;

        return *this;
    }

    ThisLazyValue& operator=(const ThisLazyValue& otherValue) {
        if (&otherValue == this) {
            return *this;
        }

        std::lock_guard<Mtx> guard0(otherValue.mtx);
        std::lock_guard<Mtx> guard1(mtx);

        this->isset = otherValue.isset;
        this->func = otherValue.func;
        this->value = otherValue.value;

        return *this;
    }

private:
    bool isset;
    Func func;
    T value;
    mutable Mtx mtx;
};
