//
// Created by Sami Dahoux on 06/05/2018.
//

#include <NParallelepiped.h>

#include "../header/NParallelepiped.h"
#include "../header/NSegment.h"

NParallelepiped::NParallelepiped(const mat_t &base, const vec_t &pos) : NCompact(base.n()),
                                                                        _base(base),
                                                                        _pos(pos),
                                                                        _vol(base.det()) {

}

std::string NParallelepiped::str() const {
    const std::vector<NSegment> segs = segments();

    std::string str = "NParallelepiped";
    char buffer[2];
    for (int k = 0; k < segs.size(); ++k) {
        sprintf(buffer, "%d", k);
        str += "\nsegment " + std::string(buffer) + " : " + segs[k].str();
    }
    return str;
}


bool NParallelepiped::isIn(const vec_t &x) const {
    vec_t u = x - _pos;
    mat_t pInv = _base ^-1;
    u = pInv * u;
    for (int k = 0; k < _dim; ++k) {
        if (u(k) > 1.0 || u(k) < 0.0) {
            return false;
        }
    }
    return true;
}

bool NParallelepiped::isEmpty() const {
    return abs(_vol) > std::numeric_limits<double>::epsilon();
}

void NParallelepiped::uni(const NSet *set) {

}

void NParallelepiped::inter(const NSet *set) {

}

int NParallelepiped::card() const {
    return 0;
}

NCompact *NParallelepiped::border() const {

    return nullptr;
}


std::vector<vec_t> NParallelepiped::mesh(const vec_t &h) const {
    std::vector<vec_t> e = _base.rows();
    vec_t end = vec_t::sum(e);

    ul_t mesh_size = meshSize(h);

    std::vector<vec_t> mesh{};
    vec_t x = vec_t::zeros(_dim);

    for (int k = 0; k < mesh_size; ++k) {
        mesh.push_back(_base * x + _pos);
        if (x(0) <= 1) {
            x(0) += h(0);
        }
        for (ul_t i = 0; i < _dim; ++i) {
            if (x(i) > 1) {
                for (ul_t j = 0; j <= i; ++j) {
                    x(j) = 0;
                }
                if (i < _dim - 1) {
                    x(i + 1) += h(i + 1);
                }
            }
        }
    }
    return mesh;
}


std::vector<NSegment> NParallelepiped::segments() const {
    const std::vector<vec_t> e = _base.cols();
    std::vector<NSegment> seg;
    for (int k = 0; k < _dim; ++k) {
        seg.emplace_back(NSegment(_pos, _pos + e[k]));
    }
    return seg;
}

double NParallelepiped::vol() const {
    return _vol;
}

ul_t NParallelepiped::meshSize(const vec_t &h) const {
    ul_t res = 1;
    for (int k = 0; k < _base.p(); ++k) {
        res *= (ul_t) ceil(1 / abs(h(k)));
    }
    return res;
}






