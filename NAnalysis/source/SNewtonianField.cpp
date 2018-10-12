//
// Created by Sami Dahoux on 08/05/2018.
//

#include <SNewtonianField.h>

SNewtonianField::SNewtonianField(ul_t dim, vec_t h, const std::vector<double> &mu,
                                 const std::vector<vec_t> &r, double k) : NPField(dim, dim, h), _mu(mu), _r(r), _k(k){

}

vec_t SNewtonianField::g(const vec_t &r) const {
    vec_t g = vec_t::zeros(_dim_out);
    vec_t rj = vec_t::zeros(_dim_in);
    double d;

    for (int j = 0; j < _mu.size(); j++) {
        if ((d = (r / _r[j])) > std::numeric_limits<double>::epsilon()) {
            g += _k * _mu[j] * (r - _r[j]) / pow(d, 3);
        }
    }
    return g;
}


