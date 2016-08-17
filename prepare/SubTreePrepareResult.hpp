#pragma once

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include "Bvalue.hpp"

#include "../utils/Types.hpp"

#include "../dataSources/DataSourcePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class SubTreePrepareResult : public MemoryLeakDetector<SubTreePrepareResult> {
public:

    SubTreePrepareResult() {
    }

    SubTreePrepareResult(const DataSourcePtr& dataSource,
                         const std::vector<uint64>& L,
                         const std::vector<boost::optional<Bvalue>>& B)
            : dataSource(dataSource), L(L), B(B) {
    }

    void setDataSource(const DataSourcePtr& dataSource) {
        this->dataSource = dataSource;
    }

    DataSourcePtr getDataSource() const {
        return dataSource;
    }

    void setL(const std::vector<uint64>& L) {
        this->L = L;
    }

    void moveL(std::vector<uint64>&& L) {
        this->L = L;
    }

    const std::vector<uint64>& getL() const {
        return L;
    }

    const std::vector<boost::optional<Bvalue>>& getB() const {
        return B;
    }

    void setB(const std::vector<boost::optional<Bvalue>>& B) {
        this->B = B;
    }

    void moveB(std::vector<boost::optional<Bvalue>>&& B) {
        this->B = B;
    }

private:
    DataSourcePtr dataSource;
    std::vector<uint64> L;
    std::vector<boost::optional<Bvalue>> B;
};
