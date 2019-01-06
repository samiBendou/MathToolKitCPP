//
// Created by Sami Dahoux on 08/05/2018.
//

#ifndef MATHTOOLKIT_SNEWTONIANFIELD_H
#define MATHTOOLKIT_SNEWTONIANFIELD_H

#include <NVector.h>
#include <NPField.h>


class SNewtonianField : public NPField<double> {
public:

    SNewtonianField(vec_t h, const std::vector<double> &mu, const std::vector<vec_t> &r, double k);

protected:
    vec_t apply(const vec_t &x) const override;

    const std::vector<double> _mu;

    const std::vector<vec_t> _r;

    double _k;
};


#endif //MATHTOOLKIT_SNEWTONIANFIELD_H
