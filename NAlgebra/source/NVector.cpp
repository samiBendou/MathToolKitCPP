//
// Created by Sami Dahoux on 03/05/2018.
//

#include "../header/NVector.h"

using namespace std;

// CONSTRUCTORS

NVector::NVector(unsigned long dim) :
    std::vector<double>(dim), _k1(0), _k2(dim > 0 ? dim - 1 : 0) {}

NVector::NVector(const std::vector<double>& data) :
    std::vector<double>(data), _k1(0), _k2(data.size() - 1 > 0 ? data.size() - 1 : 0) {}

NVector::NVector(const NVector& vector) :
    std::vector<double>(vector), _k1(0), _k2(vector.dim() - 1 > 0 ? vector.dim() - 1 : 0) {
    copy(vector);
}

// SERIALIZATION

string NVector::str() const {
    string str = "(";
    char buffer[6];
    for (unsigned long k = _k1; k <= _k2; ++k) {
        sprintf(buffer, "%.2e", abs((*this)[k]));
        str += ((*this)(k) >= 0 ? "  " : " -");
        str += buffer;
    }
    str += "  )";
    return str;
}

std::string NVector::str() {
    const NVector& constThis = (const NVector&) (*this);
    string str = constThis.str();
    _k1 = 0; _k2 = dim() - 1;
    return str;
}


// CHARACTERIZATION


bool NVector::isValidIndex(unsigned long k) const {
    return k < dim();
}


// GETTERS


unsigned long NVector::dim() const {
    return this->size();
}

std::vector<double> NVector::array() {
    return *this;
}


// SWAP


void NVector::swap(unsigned long k1, unsigned long k2) {
    assert(isValidIndex(k1) && isValidIndex(k2));

    const double temp = (*this)[k1];
    (*this)[k1] = (*this)[k2];
    (*this)[k2] = temp;
}


// SHIFT


void NVector::shift(long iterations) {

    auto sizedDim = (long long) dim();
    long sizedIterations = iterations % sizedDim;
    auto shiftIndex = (unsigned long) (iterations >= 0 ? sizedIterations : sizedDim + sizedIterations);

    if(shiftIndex > 0) {
        long index;
        vector<double> temp(dim());

        for (unsigned long k = 0; k < dim(); ++k) {
            index = (k + shiftIndex) % sizedDim;
            temp[k] = (*this)[index];
        }
        (*this) = NVector(temp);
    }
}


// FILL


void NVector::fill(const double scalar) {
    for (unsigned long k = 0; k < dim(); ++k) {
        (*this)[k] = scalar;
    }
}


// MAX / MIN


double NVector::max() const{
    return getExtremum(true);
}

double NVector::min() const{
    return getExtremum(false);
}

unsigned long NVector::maxIndex() const{
    return getExtremumIndex(true);
}

unsigned long NVector::minIndex() const{
    return getExtremumIndex(false);
}


// ABSOLUTE VALUE MAX / MIN


double NVector::maxAbs() const{
    return getExtremumAbs(true);
}

double NVector::minAbs() const{
    return getExtremumAbs(false);
}

unsigned long NVector::maxAbsIndex() const{
    return getExtremumAbsIndex(true);
}

unsigned long NVector::minAbsIndex() const{
    return getExtremumAbsIndex(false);
}





// OPERATORS


NVector operator+(const NVector &u, const NVector &v){
    NVector res{u};
    res.add(v);
    return res;
}

NVector operator-(const NVector &u, const NVector &v){
    NVector res{u};
    res.sub(v);
    return res;
}

NVector operator*(double s, const NVector &u){
    NVector res{u};
    res.prod(s);
    return res;
}

NVector operator*(const NVector &u, double s){
    return operator*(s, u);
}

NVector operator/(const NVector &u, double s){
    NVector res{u};
    res.div(s);
    return res;
}

NVector operator-(const NVector &u) {
    NVector res{u};
    res.opp();
    return res;
}


// COMPOUND OPERATORS


NVector &NVector::operator+=(const NVector &vector) {
    this->add(vector);
    return *this;
}

NVector &NVector::operator-=(const NVector &vector) {
    this->sub(vector);
    return *this;
}

NVector &NVector::operator*=(const double scalar) {
    this->prod(scalar);
    return *this;
}

NVector &NVector::operator/=(const double scalar) {
    this->div(scalar);
    return *this;
}


// ACCES OPERATOR


double &NVector::operator()(long k) {
    assert(isValidIndex(k));
    return (*this)[(k >= 0) ? k : dim() + k - 1];
}

double NVector::operator()(long k) const {
    assert(isValidIndex(k));
    return (*this).at((k >= 0) ? k : dim() + k - 1);
}

NVector NVector::operator()(unsigned long k1, unsigned long k2) const {
    return subVector(k1, k2);
}

NVector &NVector::operator()(unsigned long k1, unsigned long k2) {
    _k1 = k1; _k2 = k2;
    assert(isValidIndex(_k1) && isValidIndex(_k2) && _k2 >= _k1);
    return *this;
}


std::ostream& operator<<(std::ostream& os, const NVector &vector)
{
    os << vector.str();
    return os;
}


// AFFECTATION


NVector &NVector::operator=(const NVector &vector) {
    copy(vector);
    return *this;
}


NVector &NVector::operator=(NVector &vector) {
    copy(vector);
    vector._k1 = 0; vector._k2 = vector.dim() - 1;
    return *this;
}



// STATIC METHODS


NVector NVector::zeros(unsigned long dim) {
    return scalar(0.0, dim);
}

NVector NVector::ones(unsigned long dim) {
    return scalar(1.0, dim);
}

NVector NVector::scalar(double s, unsigned long dim) {
    NVector scalarVector = NVector(dim);
    for (unsigned long k = 0; k < dim; ++k) {
        scalarVector(k) = s;
    }
    return scalarVector;
}

NVector NVector::canonical(unsigned long k, unsigned long dim) {
    NVector canonical = NVector::zeros(dim);
    if(canonical.isValidIndex(k)) {
        canonical(k) = 1.0;
    }
    return canonical;
}

NVector NVector::sum(const std::vector<NVector> &vectors) {
    NVector sum = NVector::zeros(vectors[0].dim());
    for (const auto &vector : vectors) {
        sum += vector;
    }
    return sum;
}

NVector NVector::sumProd(const std::vector<double>& scalars, const std::vector<NVector> &vectors) {
    NVector sumProd = NVector::zeros(vectors[0].dim());
    for (unsigned long k = 0; k < scalars.size(); ++k) {
        sumProd += scalars[k] * vectors[k];
    }
    return sumProd;
}

// PRIVATE METHODS

// AFFECTATION

void NVector::copy(const NVector &vector) {
    if(this != &vector) {
        if (_k1 == 0 && (_k2 == dim() - 1 || _k2 == 0) && vector._k1 == 0 && vector._k2 == vector.dim() - 1){
            this->std::vector<double>::operator=(vector);
        }
        else if (_k1 == 0 && (_k2 == dim() - 1 || _k2 == 0)) {
            this->std::vector<double>::operator=(vector.subVector(vector._k1, vector._k2));
        }
        else {
            setSubVector(vector);
        }
        _k1 = 0; _k2 = dim() - 1;
    }
}


// EXTREMUMS

double NVector::getExtremum(const bool max) const {
    const double infinity = numeric_limits<double>::infinity();

    double extremum = (max) ? -infinity : infinity;

    for (unsigned long k = 0; k < dim(); ++k) {
        if(max)
            extremum = (extremum < (*this)[k]) ? (*this)[k] : extremum;
        else
            extremum = (extremum > (*this)[k]) ? (*this)[k] : extremum;
    }
    return extremum;

}

unsigned long NVector::getExtremumIndex(const bool max) const {
    double extremum = (max) ? this->max() : this->min();
    for (unsigned long k = 0; k < dim(); ++k) {
        if((*this)[k] == extremum) {
            return k;
        }
    }
    return 0;
}

double NVector::getExtremumAbs(bool max) const {
    double maximum = fabs(this->max());
    double minimum = fabs(this->min());
    if(max) {
        return maximum > minimum ? maximum : minimum;
    }
    else {
        return maximum < minimum ? maximum : minimum;
    }
}

unsigned long NVector::getExtremumAbsIndex(bool max) const {
    double maximum = fabs(this->max());
    double minimum = fabs(this->min());
    if(max) {
        return maximum > minimum ? maxIndex() : minIndex();
    }
    else {
        return maximum < minimum ? maxIndex() : minIndex();
    }
}

// SUB-VECTORS

NVector NVector::subVector(unsigned long k1, unsigned long k2) const {
    unsigned long end = (isValidIndex(k2)) ? k2 : dim() - 1;
    unsigned long dim = end - k1 + 1;

    assert(isValidIndex(k1) && dim > 0);
    vector<double> data(dim);
    for (unsigned long k = k1; k <= end; ++k) {
        data[k - k1] = (*this)[k];
    }
    return data;
}

void NVector::setSubVector(const NVector &vector) {

    assert(_k2 - _k1 == vector._k2 - vector._k1);
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] = vector[k + vector._k1];
    }
}


// VECTOR SPACE METHODS

void NVector::add(const NVector& vector) {
    assert(dim() == vector.dim());
    for(unsigned long k = 0; k < dim(); k++) {
        (*this)[k] += vector[k];
    }
}

void NVector::sub(const NVector& vector) {
    assert(dim() == vector.dim());
    for(unsigned long k = 0; k < dim(); k++) {
        (*this)[k] -= vector[k];
    }
}

void NVector::opp() {
    for(unsigned long k = 0; k < dim(); ++k) {
        (*this)[k] = -(*this)[k];
    }
}

void NVector::prod(const double scalar) {
    for (unsigned long k = 0; k < dim(); ++k) {
        (*this)[k] *= scalar;
    }
}

void NVector::div(const double scalar) {
    for (unsigned long k = 0; k < dim(); ++k) {
        (*this)[k] /= scalar;
    }
}





























