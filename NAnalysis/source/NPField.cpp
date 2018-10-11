//
// Created by Sami Dahoux on 06/05/2018.
//

#include "../header/NPField.h"

NPField::NPField(NCompact *domainIn, const unsigned long dimOut) :
        NVector<double>(0),
        _domainIn(domainIn), _dimOut(dimOut),
        h(NVector<double>::scalar(0.25, domainIn->dim())),
        _meshIn(domainIn->mesh(NVector<double>::scalar(0.25, domainIn->dim()))) {
}

NVector<double> NPField::operator()(const NVector<double> &u) {
    const std::vector<unsigned long> arroundIndex = meshArround(u);
    double min = std::numeric_limits<double>::infinity();
    unsigned long minIndex;
    for (unsigned long k = 0; k < arroundIndex.size(); ++k) {
        if (u / _meshIn[arroundIndex[k]] < min) {
            min = u / _meshIn[arroundIndex[k]];
            minIndex = k;
        }
    }
    return ((const NVector<double>) *this)(_dimOut * arroundIndex[minIndex],
                                           _dimOut * (arroundIndex[minIndex] + 1) - 1);
}

std::vector<NVector<double>> NPField::meshVectors() {
    return meshMatrix().rows();
}

NPMatrix<double> NPField::meshMatrix() {
    mesh();
    return NPMatrix<double>((*this), dim() / _dimOut, _dimOut);
}


void NPField::mesh() {
    const auto dim = _meshIn.size() * _dimOut;
    NVector<double> res;
    (*this).clear();
    (*this).resize(dim);
    for (unsigned long k = 0; k < dim; ++k) {
        if (k % _dimOut == 0) {
            res = g(_meshIn[k / _dimOut]);
        }
        (*this)[k] = res(k % _dimOut);
    }
}

std::vector<unsigned long> NPField::meshArround(const NVector<double> &x) {
    std::vector<unsigned long> arroundIndex{};
    NVector<double> res;
    if (dim() > 0) {
        //mémoriser un tableau d'index les plus proche à un rayon près
        for (unsigned long k = 0; k < _meshIn.size(); ++k) {
            if (x / _meshIn[k] <= !h) {
                arroundIndex.push_back(k);
            }
        }
        for (unsigned long k = 0; k < arroundIndex.size(); ++k) {
            res = g(_meshIn[arroundIndex[k]]);
            ((NVector<double>) *this)(_dimOut * arroundIndex[k], _dimOut * (arroundIndex[k] + 1) - 1) = res;
        }
    } else {
        mesh();
    }
    return arroundIndex;
}






