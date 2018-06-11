//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_SEGMENT_H
#define MATHTOOLKIT_SEGMENT_H


#include "../NAlgebra/ENVector.h"
#include "NCompact.h"


class NSegment : NCompact {
public:
    explicit NSegment(const ENVector& a, const ENVector& b);

    std::string str()const override;

    ENVector a() const;

    ENVector b() const;

    void setA(const ENVector& a);

    void setB(const ENVector& b);

    std::vector<ENVector> mesh(double h) const;

    std::vector<ENVector> mesh(const ENVector& h) const override;

    bool isIn(const ENVector& x) const override;

    bool isEmpty() const override;

protected:
    ENVector _a;
    ENVector _b;



    void uni(const NSet* set) override;

    void inter(const NSet* set) override;

    NCompact* border() const override;




    int card() const override;
};


#endif //MATHTOOLKIT_SEGMENT_H
