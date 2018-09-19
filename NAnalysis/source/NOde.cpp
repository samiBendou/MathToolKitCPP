//
// Created by Sami Dahoux on 07/05/2018.
//

#include "../header/NOde.h"

std::vector<ENVector> NOde::euler(const ENVector &u0, NPField& f, const double t0, const double t1, const double h) {

    const auto n = (int) floor((t1 - t0) / h);

    std::vector<ENVector> trajectory((unsigned long) n);
    trajectory[0] = u0;
    for(int k = 1; k < n; k++) {
        trajectory[k] = trajectory[k - 1] + h * f(trajectory[k - 1]);
    }
    return trajectory;
}
