//
// Created by Sami Dahoux on 06/05/2018.
//

#include "../header/NSegment.h"


NSegment::NSegment(const NVector<double> &a, const NVector<double> &b) : NCompact(1), _a(a), _b(b) {

}

std::string NSegment::str() const {
    return "[ " + _a.str() + ", " + _b.str() + " ]";
}


NVector<double> NSegment::a() const {
    return NVector<double>(_a);
}

NVector<double> NSegment::b() const {
    return NVector<double>(_b);
}

void NSegment::setA(const NVector<double> &a) {
    _a = NVector<double>(a);
}

void NSegment::setB(const NVector<double> &b) {
    _b = NVector<double>(b);
}

// CHARACTERIZATION

bool NSegment::isIn(const NVector<double> &x) const {
    const NVector<double> u = (x - _a);
    const NVector<double> l = (_b - _a);
    const double tol = 1000 * std::numeric_limits<double>::epsilon();

    return (abs((u | l) - !u * !l) < tol) && !u / !l <= 1;
}

bool NSegment::isEmpty() const {
    return false;
}

void NSegment::uni(const NSet *set) {

}

void NSegment::inter(const NSet *set) {

}

NCompact *NSegment::border() const {
    return nullptr;
}

std::vector<NVector<double> > NSegment::mesh(double h) const {
    const NVector<double> v = h * (_b - _a) / !NVector<double>(_b - _a);
    NVector<double> u = NVector<double>(_a);
    std::vector<NVector<double>> mesh;
    while (u / _b > h) {
        mesh.push_back(u);
        u += v;
    }
    return mesh;

}

std::vector<NVector<double> > NSegment::mesh(const NVector<double> &h) const {
    return mesh(h(0));
}

int NSegment::card() const {
    return std::numeric_limits<int>::infinity();
}





