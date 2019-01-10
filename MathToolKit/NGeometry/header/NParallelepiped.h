//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NPARALLELEPIPED_H
#define MATHTOOLKIT_NPARALLELEPIPED_H

#include <NPMatrix.h>
#include <math.h>

#include <NCompact.h>
#include <NSegment.h>

/**
 * @ingroup NGeometry
 * @{
 */

class NParallelepiped : public NCompact {
public:
    NParallelepiped(const mat_t &base = mat_t::zeros(0), const vec_t &pos = vec_t::zeros(0));

    std::string str() const override;

    bool isIn(const vec_t &x) const override;

    bool isEmpty() const override;

    int card() const override;

    const mat_t &base() const;

    const vec_t &pos() const;

    double_t vol() const;

    void setBase(const mat_t &base);

    void setPos(const vec_t &pos);

    std::vector<vec_t> border() const override;

    std::vector<vec_t> mesh(const vec_t &h) const override;

    std::vector<NSegment> segments() const;



protected:

    size_t meshSize(const vec_t &h) const;

    mat_t _base;
    vec_t _pos;
    double_t _vol;
};

/** @} */

#endif //MATHTOOLKIT_NPARALLELEPIPED_H
