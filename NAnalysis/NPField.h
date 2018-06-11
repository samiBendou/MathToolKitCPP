//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NFIELD_H
#define MATHTOOLKIT_NFIELD_H

#include "../NAlgebra/ENVector.h"
#include "../NGeometry/NCompact.h"
#include "../NAlgebra/NPMatrix.h"
#include "../NGeometry/NDSet.h"

class NPField : public ENVector {
public:
    ENVector h;

    NPField(NCompact* doaminIn, unsigned long dimOut);

    virtual ENVector g(const ENVector& x) = 0;

    ENVector operator()(const ENVector& u);

    NPMatrix meshMatrix();

    std::vector<ENVector> meshVectors();

protected:
    void mesh();

    std::vector<unsigned long> meshArround(const ENVector& x);

    NCompact* _domainIn;

    std::vector<ENVector> _meshIn;

    unsigned long _dimOut;

    // ACCES OPERATOR

};


#endif //MATHTOOLKIT_NFIELD_H
