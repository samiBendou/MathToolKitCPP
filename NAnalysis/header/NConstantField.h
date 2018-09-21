//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_GCFIELD_H
#define MATHTOOLKIT_GCFIELD_H


#include "NPField.h"
#include "../../NAlgebra/header/NVector.h"
#include "../../NAlgebra/header/Vector3.h"

class NConstantField : public NPField {
public:
    NConstantField(NCompact* domain, const NVector& cst);

    NVector g(const NVector& x) override;


protected:
    NVector _cst;
};


#endif //MATHTOOLKIT_GCFIELD_H
