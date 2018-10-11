//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_SEGMENT_H
#define MATHTOOLKIT_SEGMENT_H


#include <NVector.h>
#include "NCompact.h"


class NSegment : NCompact {
public:
    explicit NSegment(const NVector<double> &a, const NVector<double> &b);

    std::string str() const override;

    NVector<double> a() const;

    NVector<double> b() const;

    void setA(const NVector<double> &a);

    void setB(const NVector<double> &b);

    std::vector<NVector<double> > mesh(double h) const;

    std::vector<NVector<double> > mesh(const NVector<double> &h) const override;

    bool isIn(const NVector<double> &x) const override;

    bool isEmpty() const override;

protected:
    NVector<double> _a;
    NVector<double> _b;


    void uni(const NSet *set) override;

    void inter(const NSet *set) override;

    NCompact *border() const override;


    int card() const override;
};


#endif //MATHTOOLKIT_SEGMENT_H
