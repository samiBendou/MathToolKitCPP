//
// Created by Sami Dahoux on 06/05/2018.
//

#include <NCompact.h>



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

    vec_t h{vec_t::scalar(NEAR_TOL, _dim)};

    std::vector<vec_t> data{mesh(h)}, data_set{set.mesh(h)}, res;
    std::set_union(data.begin(), data.end(), data_set.begin(), data_set.end(), res.begin(), vec_t::areNear);

    return res;
}

std::vector<vec_t> NCompact::inter(const NCompact &set) {
    assert(_dim == set.dim());

    vec_t h{vec_t::scalar(0.5, _dim)};

    std::vector<vec_t> data{mesh(h)}, data_set{set.mesh(h)}, res;
    std::set_intersection(data.begin(), data.end(), data_set.begin(), data_set.end(), res.begin(), vec_t::areNear);

    return res;
}
