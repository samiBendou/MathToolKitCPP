//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_GCFIELD_H
#define MATHTOOLKIT_GCFIELD_H

#include <NVector.h>
#include <NPField.h>


class NConstantField : public NPField<double> {
public:
    NConstantField(ul_t dim_in, vec_t h, vec_t k);

protected:
    vec_t g(const vec_t &x) const override;

    vec_t _k;
};


#endif //MATHTOOLKIT_GCFIELD_H
