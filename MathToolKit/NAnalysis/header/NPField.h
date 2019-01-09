//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NFIELD_H
#define MATHTOOLKIT_NFIELD_H

#include <NVector.h>
#include <NCompact.h>
#include <NDSet.h>

/**
 * @ingroup NAnalysis
 * @{
 */

template<typename T, typename P = T>
class NPField {
public:
    NVector<T> h;

    explicit NPField(NVector<T> h);

    NVector<P> operator()(const NVector<T> &u) const;

    std::vector<NVector<P>> operator()(const std::vector<NVector<T>>& vectors) const;

    std::vector<NVector<P>> operator()(const NCompact& domain) const;

protected:

    virtual NVector<P> apply(const NVector<T> &x) const = 0;

    std::vector<NVector<P>> map(const std::vector<NVector<T>>& vectors) const;

    std::vector<NVector<P>> mesh(const NCompact& domain) const;
};

/** @} */

#endif //MATHTOOLKIT_NFIELD_H
