//
// Created by Sami Dahoux on 08/05/2018.
//

#ifndef MATHTOOLKIT_NEWTONIANFIELD_H
#define MATHTOOLKIT_NEWTONIANFIELD_H

#include <Vector3.h>
#include "NPField.h"


class SNewtonianField : public NPField {
public:


    SNewtonianField(NCompact *domain, double k, const std::vector<double> &mu, const std::vector<Vector3> &r);

    Vector3 g(const Vector3 &r);

    NVector<double> g(const NVector<double> &x) override;

protected:
    const std::vector<double> _mu;

    const std::vector<Vector3> _r;

    double _k;

    const unsigned long _size;
};


#endif //MATHTOOLKIT_NEWTONIANFIELD_H
