#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <string>
#include <utility>

//#include <unordered_map>
//
//#include <boost/pool/pool.hpp>
//#include <boost/pool/pool_alloc.hpp>


#include <boost/optional.hpp>

#include "sources/SubTreeSource.hpp"

#include "../utils/Types.hpp"
#include "../utils/WithString.hpp"
#include "../utils/ArrayOrdering.hpp"

#include "Bvalue.hpp"

#include "SubTreePrepareResult.hpp"

#include "../dataSources/DataSourcePtr.hpp"
#include "sources/SubTreeSourcePtr.hpp"

#include "../utils/MemoryLeakDetector.hpp"

class SubTreePrepare : public WithString, public MemoryLeakDetector<SubTreePrepare> {
public:

    SubTreePrepare(const DataSourcePtr& dataSource,
                   const SubTreeSourcePtr& source,
                   uint64 rangePerScan);

    void go(SubTreePrepareResult& into);

    std::string toString() override;

private:

    void initLocations();
    void resize();
    void init();
    void initVars();

    void read();
    void getActiveAreaReorders(uint64 activeAreaNum);
    void reorderElements(uint64 oldIndex, uint64 newIndex);
    void postReorderElements();
    void goReorderElements();
    void reorderElements();
    void makeNewActiveAreas();
    void goReorderActiveArea(uint64 activeAreaNum);
    void reorder();
    void updateBs();
    bool BhasEmpty();

    void getResult(SubTreePrepareResult& into);

    std::shared_ptr<DataSource> dataSource;
    std::shared_ptr<SubTreeSource> source;
    uint64 rangePerScan;

    std::vector<uint64> L;
    std::vector<boost::optional<Bvalue>> B;
    std::vector<int64> I;
    std::vector<int64> A;
    std::vector<std::vector<char>> R;
    std::vector<uint64> P;

    std::vector<uint64> newL;
    std::vector<int64> newI;
    std::vector<int64> newA;
    std::vector<std::vector<char>> newR;
    std::vector<uint64> newP;

    std::vector<uint64> changedLocations;
    std::vector<uint64> changedILocations;

    uint64 start;

    uint64 maxActiveAreaNum;
    std::unordered_set<uint64> activeAreas;
    std::vector<uint64> activeAreasCopyBuffer;

    std::vector<uint64> rsOfArea;
    std::vector<uint64> targetRsOfArea;
    std::vector<std::tuple<uint64, uint64>> areaReorders;

    std::vector<char> updateBsCommonPrefix;

//    using AreaBufferName = std::vector<char>;
//    using AreaBufferValue = std::vector<uint64>;
//    using AreaBufferPair = std::pair<const AreaBufferName, AreaBufferValue>;
//    using AreaBufferAlloc = boost::fast_pool_allocator<AreaBufferPair>;
//    using ActiveAreasBuffer = std::unordered_map<AreaBufferName, AreaBufferValue,
//            std::hash<AreaBufferName>, std::equal_to<AreaBufferName>, AreaBufferAlloc>;
//
//    ActiveAreasBuffer activeAreasBuffer;

};
