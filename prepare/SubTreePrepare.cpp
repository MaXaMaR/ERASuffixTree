#include "SubTreePrepare.hpp"
#include <memory>
#include "../utils/Types.hpp"
#include <algorithm>
#include "sources/SubTreeSource.hpp"
#include "../dataSources/locations/DataSourceLocations.hpp"
#include "../dataSources/locations/DataSourceLocation.hpp"
#include "../dataSources/DataSource.hpp"
#include "../utils/ArrayOrdering.hpp"
#include <tuple>
#include <unordered_map>
#include "../prefixes/PrefixUtils.hpp"
#include "Bvalue.hpp"
#include "../utils/bprinter/table_printer.h"
#include <sstream>
#include "../utils/DefaultArrayPrinter.hpp"
#include <cmath>
#include "../dataSources/DataSourcePtr.hpp"
#include "sources/SubTreeSourcePtr.hpp"

SubTreePrepare::SubTreePrepare(const DataSourcePtr& dataSource,
                               const SubTreeSourcePtr& source,
                               uint64 rangePerScan)
        : dataSource(dataSource), source(source), rangePerScan(rangePerScan) {
}

void SubTreePrepare::initLocations() {
    auto locations = source->locations(dataSource);
    L.reserve(locations.size());
    for (auto& location : locations) {
        L.push_back(location.getValue());
    }
}

void SubTreePrepare::resize() {

    R.resize(L.size());
    B.resize(L.size());
    I.resize(L.size());
    A.resize(L.size());
    R.resize(L.size());
    P.resize(L.size());

    for (uint64 i = 0; i < L.size(); i++) {
        I[i] = i;
        P[i] = i;
    }

    rsOfArea.reserve(L.size());
    targetRsOfArea.reserve(L.size());
    areaReorders.reserve(L.size());

    changedLocations.reserve(L.size());
    changedILocations.reserve(L.size());

    newL.resize(L.size());
    newI.resize(I.size());
    newA.resize(A.size());
    newR.resize(R.size());
    newP.resize(P.size());

    for (uint64 i = 0; i < L.size(); i++) {
        R[i].reserve(rangePerScan);
        newR[i].reserve(rangePerScan);
    }

    //activeAreasBuffer.reserve(L.size());
}

void SubTreePrepare::initVars() {
    start = source->getStart();
    maxActiveAreaNum = 0;
    activeAreas.insert(0);
}

void SubTreePrepare::init() {
    initLocations();
    resize();
    initVars();
}

// TODO: what to do if read empty data?
void SubTreePrepare::read() {

    for (uint64 i = 0; i < L.size(); i++) {
        R[i].clear();
    }

    for (auto& Ivalue : I) {
        if (Ivalue != -1) {
            R[Ivalue].resize(rangePerScan);
            dataSource->read(start + L[Ivalue], R[Ivalue]);
        }
    }

}

void SubTreePrepare::getActiveAreaReorders(uint64 activeAreaNum) {
    rsOfArea.clear();
    for (uint64 i = 0; i < R.size(); i++) {
        if (A[i] == activeAreaNum) {
            rsOfArea.push_back(i);
        }
    }
    targetRsOfArea = rsOfArea;
    std::sort(targetRsOfArea.begin(), targetRsOfArea.end(), [&](auto& first, auto& second) {
        return compareArrays(R[first], R[second]);
    });

    areaReorders.resize(rsOfArea.size());
    for (uint64 i = 0; i < rsOfArea.size(); i++) {
        areaReorders[i] = std::tuple<uint64, uint64>(targetRsOfArea[i], rsOfArea[i]);
    }
}

void SubTreePrepare::reorderElements(uint64 oldIndex, uint64 newIndex) {
    newR[newIndex] = R[oldIndex];
    newP[newIndex] = P[oldIndex];
    newL[newIndex] = L[oldIndex];
    newI[oldIndex] = I[newIndex];
    newA[newIndex] = A[oldIndex];

    changedLocations.push_back(newIndex);
    changedILocations.push_back(oldIndex);
}

void SubTreePrepare::postReorderElements() {

    for (auto changedLocation : changedLocations) {
        R[changedLocation] = newR[changedLocation];
        P[changedLocation] = newP[changedLocation];
        L[changedLocation] = newL[changedLocation];
        A[changedLocation] = newA[changedLocation];
    }

    for (auto changedILocation : changedILocations) {
        I[changedILocation] = newI[changedILocation];
    }

    changedLocations.clear();
    changedILocations.clear();
}

void SubTreePrepare::goReorderElements() {

    for (auto& val : areaReorders) {
        reorderElements(std::get<0>(val), std::get<1>(val));
    }

}

void SubTreePrepare::reorderElements() {

    goReorderElements();
    postReorderElements();

}

void SubTreePrepare::makeNewActiveAreas() {

    bool creatingArea = false;
    uint64 count = 0;
    uint64 prevValue;
    for (auto& item: areaReorders) {
        auto& thisValue = std::get<1>(item);
        if (count > 0) {
            if (R[prevValue] == R[thisValue]) {
                if (!creatingArea) {
                    creatingArea = true;
                    auto newActiveAreaNum = maxActiveAreaNum + 1;
                    maxActiveAreaNum = newActiveAreaNum;
                    activeAreas.insert(newActiveAreaNum);
                    A[prevValue] = maxActiveAreaNum;
                }
                A[thisValue] = maxActiveAreaNum;
            } else {
                creatingArea = false;
            }
        }
        count++;
        prevValue = thisValue;
    }

//    for (auto val:areaReorders) {
//        auto& thisValue = std::get<1>(val);
//        auto& Rvalue = R[thisValue];
//        activeAreasBuffer[Rvalue].push_back(thisValue);
//    }
//
//    for (auto& item : activeAreasBuffer) {
//        if (item.second.size() > 1) {
//            auto newActiveAreaNum = maxActiveAreaNum + 1;
//            maxActiveAreaNum = newActiveAreaNum;
//            activeAreas.insert(newActiveAreaNum);
//            for (auto num : item.second) {
//                A[num] = newActiveAreaNum;
//            }
//        }
//    }
//
//    activeAreasBuffer.clear();

}

void SubTreePrepare::goReorderActiveArea(uint64 activeAreaNum) {

    getActiveAreaReorders(activeAreaNum);
    reorderElements();
    makeNewActiveAreas();

}

void SubTreePrepare::reorder() {

    activeAreasCopyBuffer.clear();
    std::copy(activeAreas.begin(), activeAreas.end(), std::back_inserter(activeAreasCopyBuffer));

    for (auto activeAreaNum : activeAreasCopyBuffer) {
        goReorderActiveArea(activeAreaNum);
    }

}

// TODO: what to do if R[i] or R[i-1] is empty? when accessing at commonPrefix.size()
void SubTreePrepare::updateBs() {
    auto& commonPrefix = updateBsCommonPrefix;
    // TODO: may be optimized
    for (uint64 i = 1; i < L.size(); i++) {
        if (B[i] == boost::none) {
            PrefixUtils::commonPrefix(R[i - 1], R[i], commonPrefix);
            if (commonPrefix.size() < rangePerScan) {
                B[i] = Bvalue(R[i - 1][commonPrefix.size()], R[i][commonPrefix.size()],
                              start + commonPrefix.size());
                if (i == 1 || B[i - 1] != boost::none) {
                    I[P[i - 1]] = -1;
                    A[i - 1] = -1;
                }
                if (i == L.size() - 1 || B[i + 1] != boost::none) {
                    I[P[i]] = -1;
                    A[i] = -1;
                    auto activeAreaNum = A[i];
                    A[i] = -1;
                    activeAreas.erase((uint64) activeAreaNum);
                }
            }
        }
    }

}

// TODO: may be optimized
bool SubTreePrepare::BhasEmpty() {
    return std::find(B.begin() + 1, B.end(), boost::none) != B.end();
}

void SubTreePrepare::go(SubTreePrepareResult& into) {

    init();

    while (BhasEmpty()) {
        read();
        reorder();
        updateBs();
        start += rangePerScan;
    }

    getResult(into);
}

void SubTreePrepare::getResult(SubTreePrepareResult& into) {
    into.setDataSource(dataSource);
    into.moveL(std::move(L));
    into.moveB(std::move(B));
}

std::string SubTreePrepare::toString() {
    std::stringstream stream;
    bprinter::TablePrinter tp(&stream);

    stream << "Source: " << *source << std::endl;

    tp.AddColumn("", 5);
    for (uint64 i = 0; i < R.size(); i++) {
        std::stringstream streamInner;
        streamInner << "'" << DefaultArrayPrinter(R[i], "") << "'";
        std::string res = streamInner.str();
        uint64 length = std::max<uint64>((int) 4, (int) res.length());
        if (B[i]) {
            std::stringstream thisStream;
            thisStream << *B[i];
            auto Bres = thisStream.str();
            length = std::max<uint64>(length, Bres.length() + 1);
        }
        tp.AddColumn("", (int) length);
    }

    tp << "I: ";
    for (auto& val : I) {
        if (val == -1) {
            tp << "done";
        } else {
            tp << val;
        }
    }

    tp << "A: ";
    for (auto& val : A) {
        if (val == -1) {
            tp << "done";
        } else {
            tp << val;
        }
    }

    tp << "R: ";
    for (auto& val : R) {
        std::stringstream thisStream;
        thisStream << "'" << DefaultArrayPrinter(val, "") << "'";
        auto value = thisStream.str();
        tp << value;
    }

    tp << "P: ";
    for (auto& val : P) {
        tp << val;
    }

    tp << "L: ";
    for (auto& val : L) {
        tp << val;
    }

    tp << "B: ";
    for (auto& val : B) {
        if (val) {
            tp << *val;
        } else {
            tp << "";
        }
    }

    return stream.str();
}
