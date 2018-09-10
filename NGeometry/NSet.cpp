//
// Created by Sami Dahoux on 06/05/2018.
//

#include "NSet.h"
#include "NDSet.h"

NSet::NSet(unsigned long dim) : _dim(dim) {

}

NSet::~NSet() = default;

unsigned long NSet::dim() const {
    return _dim;
}

std::ostream &operator<<(std::ostream &os, const NSet &set) {
    os << set.str();
    return os;
}




