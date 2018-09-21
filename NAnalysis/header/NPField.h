//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NFIELD_H
#define MATHTOOLKIT_NFIELD_H

#include "../../NAlgebra/header/NVector.h"
#include "../../NGeometry/header/NCompact.h"
#include "../../NAlgebra/header/NPMatrix.h"
#include "../../NGeometry/header/NDSet.h"

class NPField : public NVector {
public:
    NVector h;

    NPField(NCompact* doaminIn, unsigned long dimOut);

    virtual NVector g(const NVector& x) = 0;

    NVector operator()(const NVector& u);

    NPMatrix meshMatrix();

    std::vector<NVector> meshVectors();

protected:
    void mesh();

    std::vector<unsigned long> meshArround(const NVector& x);

    NCompact* _domainIn;

    std::vector<NVector> _meshIn;

    unsigned long _dimOut;

    // ACCES OPERATOR

};


#endif //MATHTOOLKIT_NFIELD_H
