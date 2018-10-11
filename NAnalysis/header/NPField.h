//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NFIELD_H
#define MATHTOOLKIT_NFIELD_H

#include <NVector.h>
#include <NPMatrix.h>

#include "../../NGeometry/header/NCompact.h"
#include "../../NGeometry/header/NDSet.h"

class NPField : public NVector<double> {
public:
    NVector<double> h;

    NPField(NCompact *doaminIn, unsigned long dimOut);

    virtual NVector<double> g(const NVector<double> &x) = 0;

    NVector<double> operator()(const NVector<double> &u);

    NPMatrix<double> meshMatrix();

    std::vector<NVector<double>> meshVectors();

protected:
    void mesh();

    std::vector<unsigned long> meshArround(const NVector<double> &x);

    NCompact *_domainIn;

    std::vector<NVector<double> > _meshIn;

    unsigned long _dimOut;

    // ACCES OPERATOR

};


#endif //MATHTOOLKIT_NFIELD_H
