#include "Tree.hpp"
#include "TreeRepository.hpp"

Tree::Tree(const DataSourcePtr& dataSource) : dataSource(dataSource) {
    //num = (TreeNumType) TreeRepository::reg(this);
}

Tree::~Tree() {
    //TreeRepository::unreg(num);
}
