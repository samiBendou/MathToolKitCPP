//
// Created by Sami Dahoux on 06/05/2018.
//

#include <NCompact.h>

#define NEAR_TOL 0.01


NCompact::NCompact(unsigned long dim) : _dim(dim) {

}

unsigned long NCompact::dim() const {
    return _dim;
}

std::ostream &operator<<(std::ostream &os, const NCompact &set) {
    os << set.str();
    return os;
}

std::vector<vec_t> NCompact::uni(const NCompact &set) {

    assert(_dim == set.dim());

    return {};
}

std::vector<vec_t> NCompact::inter(const NCompact &set) {
    assert(_dim == set.dim());

    return {};
}
