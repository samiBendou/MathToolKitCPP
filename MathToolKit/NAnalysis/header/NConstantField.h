//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_GCFIELD_H
#define MATHTOOLKIT_GCFIELD_H

#include <NVector.h>
#include <NPField.h>

/**
 * @ingroup NAnalysis
 * @{
 */

class NConstantField : public NPField<double> {
public:
    NConstantField(vec_t h, vec_t k);

protected:
    vec_t apply(const vec_t &x) const override;

    vec_t _k;
};

/** @} */

#endif //MATHTOOLKIT_GCFIELD_H
