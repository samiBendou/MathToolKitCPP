//
// Created by Sami Dahoux on 08/05/2018.
//

#ifndef MATHTOOLKIT_SNEWTONIANFIELD_H
#define MATHTOOLKIT_SNEWTONIANFIELD_H

#include <NVector.h>
#include <NPField.h>

/**
 * @ingroup NAnalysis
 * @{
 */

class SNewtonianField : public NPField<double_t> {
public:

    SNewtonianField(vec_t h, const std::vector<double_t> &mu, const std::vector<vec_t> &r, double_t k);

protected:
    vec_t apply(const vec_t &x) const override;

    const std::vector<double_t> _mu;

    const std::vector<vec_t> _r;

    double_t _k;
};

/** @} */

#endif //MATHTOOLKIT_SNEWTONIANFIELD_H
