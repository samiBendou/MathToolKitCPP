//
// Created by Sami Dahoux on 06/05/2018.
//

#include "../header/NPField.h"

NPField::NPField(NCompact* domainIn, const unsigned long dimOut) :
        NVector(0),
        _domainIn(domainIn), _dimOut(dimOut),
        h(NVector::scalar(0.25, domainIn->dim())), _meshIn(domainIn->mesh(NVector::scalar(0.25, domainIn->dim()))) {
}

NVector NPField::operator()(const NVector &u) {
    const std::vector<unsigned long> arroundIndex = meshArround(u);
    double min = std::numeric_limits<double>::infinity();
    unsigned long minIndex;
    for (unsigned long k = 0; k < arroundIndex.size(); ++k) {
        if(u / _meshIn[arroundIndex[k]] < min) {
            min = u / _meshIn[arroundIndex[k]];
            minIndex = k;
        }
    }
    return ((const NVector) *this)(_dimOut * arroundIndex[minIndex], _dimOut * (arroundIndex[minIndex] + 1) - 1);
}

std::vector<NVector> NPField::meshVectors() {
    return meshMatrix().rows();
}

NPMatrix NPField::meshMatrix() {
    mesh();
    return NPMatrix((*this), dim() / _dimOut, _dimOut);
}


void NPField::mesh() {
    const auto dim = _meshIn.size() * _dimOut;
    NVector res;
    (*this).clear();
    (*this).resize(dim);
    for (unsigned long k = 0; k < dim; ++k) {
        if(k % _dimOut == 0) {
            res = g(_meshIn[k / _dimOut]);
        }
        (*this)[k] = res(k % _dimOut);
    }
}

std::vector<unsigned long> NPField::meshArround(const NVector& x) {
    std::vector<unsigned long> arroundIndex{};
    NVector res;
    if(dim() > 0) {
        //mémoriser un tableau d'index les plus proche à un rayon près
        for (unsigned long k = 0; k < _meshIn.size(); ++k) {
            if(x / _meshIn[k] <= !h) {
                arroundIndex.push_back(k);
            }
        }
        for (unsigned long k = 0; k < arroundIndex.size(); ++k) {
            res = g(_meshIn[arroundIndex[k]]);
            ((NVector) *this)(_dimOut * arroundIndex[k], _dimOut * (arroundIndex[k] + 1) - 1) = res;
        }
    } else {
        mesh();
    }
    return arroundIndex;
}






