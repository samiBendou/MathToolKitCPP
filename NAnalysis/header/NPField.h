//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NFIELD_H
#define MATHTOOLKIT_NFIELD_H

#include <NVector.h>
#include <NCompact.h>
#include <NDSet.h>

template<typename T>
class NPField : public NVector<T> {
public:
    NVector<T> h;

    NPField(ul_t dim_in, ul_t dim_out, NVector<T> h);

    NVector<T> operator()(const NVector<T> &u) const;

    std::vector<NVector<T>> operator()(const std::vector<NVector<T>>& vectors) const;

    std::vector<NVector<T>> operator()(const NCompact& domain) const;

protected:

    virtual NVector<T> g(const NVector<T> &x) const = 0;

    std::vector<NVector<T>> map(const std::vector<NVector<T>>& vectors) const;

    std::vector<NVector<T>> mesh(const NCompact& domain) const;

    ul_t _dim_in;
    ul_t _dim_out;
};


#endif //MATHTOOLKIT_NFIELD_H
