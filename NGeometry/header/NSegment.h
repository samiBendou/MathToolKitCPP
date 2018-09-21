//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_SEGMENT_H
#define MATHTOOLKIT_SEGMENT_H


#include "../../NAlgebra/header/NVector.h"
#include "NCompact.h"


class NSegment : NCompact {
public:
    explicit NSegment(const NVector& a, const NVector& b);

    std::string str()const override;

    NVector a() const;

    NVector b() const;

    void setA(const NVector& a);

    void setB(const NVector& b);

    std::vector<NVector> mesh(double h) const;

    std::vector<NVector> mesh(const NVector& h) const override;

    bool isIn(const NVector& x) const override;

    bool isEmpty() const override;

protected:
    NVector _a;
    NVector _b;



    void uni(const NSet* set) override;

    void inter(const NSet* set) override;

    NCompact* border() const override;



    int card() const override;
};


#endif //MATHTOOLKIT_SEGMENT_H
