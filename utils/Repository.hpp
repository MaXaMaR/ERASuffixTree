#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <mutex>

#include "Types.hpp"
#include "SpinLock.hpp"

template<typename T>
class Repository {
public:
    using Values = std::vector<T>;
    using ValuesMark = std::vector<bool>;

    static uint64 reg(const T& value) {
        std::lock_guard<std::mutex> guard(mtx);
        std::lock_guard<SpinLock> guard2(spinLock);
        uint64 num;
        if (!valuesMark[0]) {
            num = 0;
        } else {
            num = prevNum + 1;
        }
        while (valuesMark.size() > num && valuesMark[num]) {
            num++;
        }
        if (num >= values.size()) {
            values.resize(num + 1);
            valuesMark.resize(num + 1);
        }
        prevNum = num;
        values[num] = value;
        valuesMark[num] = true;
        return num;
    }

    static void unreg(uint64 num) {
        std::lock_guard<std::mutex> guard(mtx);
        std::lock_guard<SpinLock> guard2(spinLock);
        values[num] = T();
        valuesMark[num] = false;
    }

    static T get(int64 num) {
        std::lock_guard<SpinLock> guard(spinLock);
        if (num < 0) {
            return T();
        }
        return values[num];
    }

private:
    static Values values;
    static ValuesMark valuesMark;
    static uint64 prevNum;
    static std::mutex mtx;
    static SpinLock spinLock;
};

template<typename T>
typename Repository<T>::Values Repository<T>::values{T()};

template<typename T>
typename Repository<T>::ValuesMark Repository<T>::valuesMark{false};

template<typename T>
uint64 Repository<T>::prevNum{0};

template<typename T>
std::mutex Repository<T>::mtx;

template<typename T>
SpinLock Repository<T>::spinLock;
