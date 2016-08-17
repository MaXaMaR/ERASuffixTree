#pragma once

#include <string>

template<typename To, typename From>
class EmptyType {
public:

    using ThisType = EmptyType<To, From>;

    operator To() {
        return To();
    }

    ThisType& operator=(const From& from) {
        return *this;
    }

};

using StringEmptyType = EmptyType<std::string, std::string>;
