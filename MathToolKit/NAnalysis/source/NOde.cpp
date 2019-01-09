//
// Created by Sami Dahoux on 07/05/2018.
//

#include <NOde.h>

std::vector<vec_t> NOde::euler(const vec_t &u0, const NPField<double> &f, double t0, double t1, double dt) {

    ul_t n = (ul_t) floor((t1 - t0) / dt);

    std::vector<vec_t> trajectory(n);
    trajectory[0] = u0;
    for (int k = 1; k < n; k++) {
        trajectory[k] = trajectory[k - 1] + dt * f(trajectory[k - 1]);
    }
    return trajectory;
}
