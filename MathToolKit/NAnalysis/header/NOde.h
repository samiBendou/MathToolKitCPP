//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_NODE_H
#define MATHTOOLKIT_NODE_H


#include <NVector.h>
#include <NPField.h>

/**
 * @ingroup NAnalysis
 * @{
 */

class NOde {
public:
    static std::vector<vec_t> euler(const vec_t &u0,
                                    const NPField<double_t> &f,
                                    double_t t0 = 0,
                                    double_t t1 = 1,
                                    double_t dt = 0.1);
};

/** @} */

#endif //MATHTOOLKIT_NODE_H
