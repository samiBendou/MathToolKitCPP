//
// Created by Sami Dahoux on 06/05/2018.
//

#include "NSegment.h"


NSegment::NSegment(const ENVector &a, const ENVector &b) : NCompact(1), _a(a), _b(b)
{

}
std::string NSegment::str() const {
    return "[ " + _a.str() + ", " + _b.str() + " ]";
}


ENVector NSegment::a() const {
    return ENVector(_a);
}

ENVector NSegment::b() const {
    return ENVector(_b);
}

void NSegment::setA(const ENVector &a) {
    _a = ENVector(a);
}

void NSegment::setB(const ENVector &b) {
    _b = ENVector(b);
}

// CHARACTERIZATION

bool NSegment::isIn(const ENVector &x) const {
    const ENVector u = (x - _a);
    const ENVector l = (_b - _a);
    const double tol = 1000 * std::numeric_limits<double>::epsilon();

    return (abs(u * l - !u * !l) < tol) &&  !u / !l <= 1;
}

bool NSegment::isEmpty() const {
    return false;
}

void NSegment::uni(const NSet* set) {

}

void NSegment::inter(const NSet* set) {

}

NCompact *NSegment::border() const {
    return nullptr;
}

std::vector<ENVector> NSegment::mesh(double h) const {
    const ENVector v = h * (_b - _a) / !ENVector(_b - _a);
    ENVector u = ENVector(_a);
    std::vector<ENVector> mesh;
    while (u / _b > h) {
        mesh.push_back(u);
        u += v;
    }
    return mesh;

}

std::vector<ENVector> NSegment::mesh(const ENVector& h) const {
    return mesh(h(0));
}

int NSegment::card() const {
    return std::numeric_limits<int>::infinity();
}





