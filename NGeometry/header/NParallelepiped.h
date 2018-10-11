//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NPARALLELEPIPED_H
#define MATHTOOLKIT_NPARALLELEPIPED_H

#include <NPMatrix.h>

#include "NCompact.h"
#include "NSegment.h"

class NParallelepiped : public NCompact {
public:
    NParallelepiped(NPMatrix<double> &base, const NVector<double> &_pos);

    std::string str() const override;

    std::vector<NSegment> segments() const;

    double volume() const;

    bool isIn(const NVector<double> &x) const override;

    bool isEmpty() const override;

    void uni(const NSet *set) override;

    void inter(const NSet *set) override;

    int card() const override;

    NCompact *border() const override;

    std::vector<NVector<double> > mesh(const NVector<double> &h) const override;

protected:
    NPMatrix<double> _base;
    NVector<double> _pos;
    double _vol;
};


#endif //MATHTOOLKIT_NPARALLELEPIPED_H
