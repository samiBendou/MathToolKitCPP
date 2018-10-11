//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_GCFIELD_H
#define MATHTOOLKIT_GCFIELD_H

#include <NVector.h>
#include <Vector3.h>

#include "NPField.h"


class NConstantField : public NPField {
public:
    NConstantField(NCompact *domain, const NVector<double> &cst);

    NVector<double> g(const NVector<double> &x) override;


protected:
    NVector<double> _cst;
};


#endif //MATHTOOLKIT_GCFIELD_H
