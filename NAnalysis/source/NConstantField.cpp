//
// Created by Sami Dahoux on 07/05/2018.
//

#include <NConstantField.h>

NConstantField::NConstantField(ul_t dim_in, vec_t h, vec_t k) : NPField<double>(dim_in, k.dim(), h),
                                                                _k(k) {

}

vec_t NConstantField::g(const vec_t &x) const {
    return _k;
}




