//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_GCFIELD_H
#define MATHTOOLKIT_GCFIELD_H


#include "NPField.h"
#include "../../NAlgebra/header/ENVector.h"
#include "../../NAlgebra/header/Vector3.h"

class NConstantField : public NPField {
public:
    NConstantField(NCompact* domain, const ENVector& cst);

    ENVector g(const ENVector& x) override;


protected:
    ENVector _cst;
};


#endif //MATHTOOLKIT_GCFIELD_H
