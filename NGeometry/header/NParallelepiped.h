//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NPARALLELEPIPED_H
#define MATHTOOLKIT_NPARALLELEPIPED_H


#include "NCompact.h"
#include "../../NAlgebra/header/NMatrix.h"
#include "NSegment.h"

class NParallelepiped : public NCompact{
public:
    NParallelepiped(NMatrix& base, const NVector& _pos);

    std::string str() const override;

    std::vector<NSegment> segments() const;

    double volume() const;

    bool isIn(const NVector& x) const override;

    bool isEmpty() const override;

    void uni(const NSet* set) override;

    void inter(const NSet* set) override;

    int card() const override;

    NCompact* border() const override;

    std::vector<NVector> mesh(const NVector& h) const override;

protected:
    NMatrix _base;
    NVector _pos;
    double _vol;
};


#endif //MATHTOOLKIT_NPARALLELEPIPED_H
