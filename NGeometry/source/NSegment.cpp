//
// Created by Sami Dahoux on 06/05/2018.
//

#include "../header/NSegment.h"


NSegment::NSegment(const NVector &a, const NVector &b) : NCompact(1), _a(a), _b(b)
{

}
std::string NSegment::str() const {
    return "[ " + _a.str() + ", " + _b.str() + " ]";
}


NVector NSegment::a() const {
    return NVector(_a);
}

NVector NSegment::b() const {
    return NVector(_b);
}

void NSegment::setA(const NVector &a) {
    _a = NVector(a);
}

void NSegment::setB(const NVector &b) {
    _b = NVector(b);
}

// CHARACTERIZATION

bool NSegment::isIn(const NVector &x) const {
    const NVector u = (x - _a);
    const NVector l = (_b - _a);
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

std::vector<NVector> NSegment::mesh(double h) const {
    const NVector v = h * (_b - _a) / !NVector(_b - _a);
    NVector u = NVector(_a);
    std::vector<NVector> mesh;
    while (u / _b > h) {
        mesh.push_back(u);
        u += v;
    }
    return mesh;

}

std::vector<NVector> NSegment::mesh(const NVector& h) const {
    return mesh(h(0));
}

int NSegment::card() const {
    return std::numeric_limits<int>::infinity();
}





