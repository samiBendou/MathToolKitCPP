//
// Created by Sami Dahoux on 07/05/2018.
//

#include <NConstantField.h>

NConstantField::NConstantField(vec_t h, vec_t k) : NPField<double_t>(h),
                                                                _k(k) {

}

vec_t NConstantField::apply(const vec_t &x) const {
    return _k;
}




