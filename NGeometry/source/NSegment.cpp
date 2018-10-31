//
// Created by Sami Dahoux on 06/05/2018.
//

#include "../header/NSegment.h"


NSegment::NSegment(const vec_t &a, const vec_t &b) : NCompact(1), _a(a), _b(b) {

}

std::string NSegment::str() const {
    return "[ " + _a.str() + ", " + _b.str() + " ]";
}


vec_t NSegment::a() const {
    return vec_t(_a);
}

vec_t NSegment::b() const {
    return vec_t(_b);
}

void NSegment::setA(const vec_t &a) {
    _a = vec_t(a);
}

void NSegment::setB(const vec_t &b) {
    _b = vec_t(b);
}

// CHARACTERIZATION

bool NSegment::isIn(const vec_t &x) const {
    const vec_t u = (x - _a);
    const vec_t l = (_b - _a);

    return (abs((u | l) - !u * !l) < D_EPSILON) && !u / !l <= 1;
}

bool NSegment::isEmpty() const {
    return false;
}

std::vector<vec_t> NSegment::border() const {
    return std::vector<vec_t>{_a, _b};
}

std::vector<vec_t > NSegment::mesh(double h) const {
    const vec_t v = h * (_b - _a) / !vec_t(_b - _a);
    vec_t u = vec_t(_a);
    std::vector<vec_t> mesh;
    while (u / _b > h) {
        mesh.push_back(u);
        u += v;
    }
    return mesh;
}

std::vector<vec_t > NSegment::mesh(const vec_t &h) const {
    return mesh(h(0));
}

int NSegment::card() const {
    return std::numeric_limits<int>::infinity();
}





