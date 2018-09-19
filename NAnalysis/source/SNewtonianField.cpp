//
// Created by Sami Dahoux on 08/05/2018.
//

#include "../header/SNewtonianField.h"

SNewtonianField::SNewtonianField(NCompact* domain, const double k, const std::vector<double>& mu, const std::vector<Vector3>& r) :
        NPField(domain, 3), _k(k), _size(mu.size()), _mu(mu), _r(r)
{
    mesh();
}

Vector3 SNewtonianField::g(const Vector3 &r) {
    Vector3 g{0, 0, 0};
    Vector3 rj{0, 0, 0};
    double d;

    for(int j = 0; j < _size; j++) {
        if((d = (r / _r[j])) > std::numeric_limits<double>::epsilon()) {
            g += _k * _mu[j] * (r - _r[j]) / pow(d, 3);
        }
    }
    return g;
}

ENVector SNewtonianField::g(const ENVector &x) {
    return g((Vector3) x);
}
