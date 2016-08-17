#include "BaseDataSource.hpp"
#include "../utils/Types.hpp"

bool BaseDataSource::contains(const Container& value) {
    const auto hasEnd = value.back() == '$';
    const auto* usedValue = &value;
    Container tempValue;
    if (hasEnd) {
        tempValue.reserve(value.size() - 1);
        std::copy_n(value.begin(), value.size() - 1, std::back_inserter(tempValue));
        usedValue = &tempValue;
    }
    const auto count = length() - usedValue->size();
    for (uint64 i = 0; i < count; i++) {
        if (startsWith(i, *usedValue)) {
            if (!hasEnd || i == count - 1) {
                return true;
            }
        }
    }
    return value.size() == 0;
}

BaseDataSource::Container BaseDataSource::read(uint64 offset, uint64 length, bool pad) {
    const auto readLength = pad ? length : std::min(length, this->length() - offset);
    Container res;
    res.resize(readLength);
    read(offset, res);
    return res;
}
