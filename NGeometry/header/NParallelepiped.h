//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NPARALLELEPIPED_H
#define MATHTOOLKIT_NPARALLELEPIPED_H

#include <NPMatrix.h>
#include <math.h>

#include <NCompact.h>
#include <NSegment.h>

class NParallelepiped : public NCompact {
public:
    NParallelepiped(const mat_t &base, const vec_t &pos);

    std::string str() const override;

    std::vector<NSegment> segments() const;

    bool isIn(const vec_t &x) const override;

    bool isEmpty() const override;

    void uni(const NSet *set) override;

    void inter(const NSet *set) override;

    int card() const override;

    NCompact *border() const override;

    std::vector<vec_t > mesh(const vec_t &h) const override;

    double vol() const;

protected:

    ul_t meshSize(const vec_t &h) const;

    mat_t _base;
    vec_t _pos;
    double _vol;
};


#endif //MATHTOOLKIT_NPARALLELEPIPED_H
