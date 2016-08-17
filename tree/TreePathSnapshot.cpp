#include "TreePathSnapshot.hpp"
#include "../utils/LazyValue.hpp"
#include "SubValuePath.hpp"
#include "TreePath.hpp"
#include "TreeEdge.hpp"

void TreePathSnapshot::init() {

    data = LazyValue<Data>{
            [=](auto& value) {
                value = generateData();
            }
    };

    subValuePath = LazyValue<SubValuePath>{
            [=](auto& value) {
                value = generateSubValuePath();
            }
    };

}

TreePathSnapshot::Data TreePathSnapshot::generateData() {
    Data res;
    for (auto& edge: path.getValues()) {
        edge->getLabel().getValue(res);
    }
    return res;
}

SubValuePath TreePathSnapshot::generateSubValuePath() {
    SubValuePath path;
    for (auto& edge: this->path.getValues()) {
        path.getValues().push_back(edge->getLabel());
    }
    return path;
}
