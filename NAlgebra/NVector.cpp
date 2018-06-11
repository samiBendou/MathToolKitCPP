//
// Created by Sami Dahoux on 03/05/2018.
//

#include "NVector.h"

using namespace std;

NVector::NVector(unsigned long dim) : std::vector<double>(dim), _k1(0), _k2(0) {}

NVector::NVector(const std::vector<double>& data) : std::vector<double>(data), _k1(0), _k2(0) {}

NVector::NVector(const NVector& vector) : std::vector<double>(vector), _k1(0), _k2(0) {}

string NVector::str() const{
    string str = "(";
    char buffer[6];
    for (unsigned long k = 0; k < dim(); ++k) {
        sprintf(buffer, "%.2e", abs((*this)[k]));
        str += ((*this)(k) >= 0 ? "  " : " -");
        str += buffer;
    }
    str += "  )";
    return str;
}


// CHARACTERIZATION


bool NVector::isValidIndex(const long k) const{
    return (abs(k) >= 0 && abs(k) < dim());
}


// GETTERS


unsigned long NVector::dim() const {
    return this->size();
}

std::vector<double> NVector::array() {
    return *this;
}


// SWAP


void NVector::swap(const unsigned long k1, const unsigned long k2) {
    if(isValidIndex(k1) && isValidIndex(k2)) {
        const double temp = (*this)[k1];
        (*this)[k1] = (*this)[k2];
        (*this)[k2] = temp;
    }
}


// SHIFT


void NVector::shift(const long iterations) {
    const long shiftIndex = iterations % dim();

    long index;
    vector<double> temp(dim());

    for (unsigned long k = 0; k < dim(); ++k) {
        index = (k + shiftIndex) % dim();
        index = (index < 0) ? index + dim() : index;
        temp[k] = (*this)[index];
    }
    (*this) = temp;
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


NVector operator+(const NVector &v1, const NVector &v2){
    NVector res{v1};
    res.add(v2);
    return res;
}

NVector operator-(const NVector &v1, const NVector &v2){
    NVector res{v1};
    res.sub(v2);
    return res;
}

NVector operator*(const double scalar, const NVector &vector){
    NVector res{vector};
    res.prod(scalar);
    return res;
}

NVector operator*(const NVector &vector, const double scalar){
    return operator*(scalar, vector);
}

NVector operator/(const NVector &vector, const double scalar){
    NVector res{vector};
    res.div(scalar);
    return res;
}

NVector operator-(const NVector &vector) {
    NVector res{vector};
    res.opp();
    return res;
}


// COMPOUND OPERATORS


NVector & NVector::operator+=(const NVector &vector) {
    this->add(vector);
    return *this;
}

NVector & NVector::operator-=(const NVector &vector) {
    this->sub(vector);
    return *this;
}

NVector & NVector::operator*=(const double scalar) {
    this->prod(scalar);
    return *this;
}

NVector &NVector::operator/=(const double scalar) {
    this->div(scalar);
    return *this;
}


// ACCES OPERATOR


double &NVector::operator()(long k) {
    if(isValidIndex(k))
        return (*this)[(k >= 0) ? k : dim() - k - 1];
    else {
        auto* nanValue = new double; *nanValue = nan("");
        return *nanValue;
    }

}

double NVector::operator()(long k) const {
    if(isValidIndex(k)) {
        return (*this).at((k >= 0) ? k : dim() - k - 1);
    }
    else {
        return nan("");
    }
}

NVector NVector::operator()(const long k1, const long k2) const {
    if(isValidIndex(k1) && isValidIndex(k2))
        return subVector((k1 >= 0) ? k1 : dim() - k1 - 1, (k2 >= 0) ? k2 : dim() - k2 - 1);
}

NVector& NVector::operator()(const long k1, const long k2) {
    if(isValidIndex(k1) && isValidIndex(k2) && k2 > k1) {
        _k1 = (k1 >= 0) ? k1 : dim() - k1 - 1;
        _k2 = (k2 >= 0) ? k2 : dim() - k2 - 1;
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const NVector &vector)
{
    os << vector.str();
    return os;
}


// AFFECTATION


NVector & NVector::operator=(const NVector &vector) {
    if (_k1 == 0 && _k2 == 0){
        this->std::vector<double>::operator=(vector);
    }
    else {
        setSubVector(vector);
        _k1 = 0; _k2 = 0;
    }
    return *this;
};


// STATIC METHODS


NVector NVector::zeros(const unsigned long dim) {
    return scalar(0.0, dim);
}

NVector NVector::ones(const unsigned long dim) {
    return scalar(1.0, dim);
}

NVector NVector::scalar(const double scalar, const unsigned long dim) {
    NVector scalarVector = NVector(dim);
    for (unsigned long k = 0; k < dim; ++k) {
        scalarVector(k) = scalar;
    }
    return scalarVector;
}

NVector NVector::canonical(const unsigned long k, const unsigned long dim) {
    NVector canonical = NVector::zeros(dim);
    if(canonical.isValidIndex(k)) {
        canonical(k) = 1.0;
    }
    return canonical;
}

NVector NVector::sum(const std::vector<NVector> &vectors) {
    NVector sum = NVector::zeros(vectors[0].dim());
    for(unsigned long k = 0; k < vectors.size(); ++k) {
        sum += vectors[k];
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

NVector NVector::subVector(const unsigned long k1, const unsigned long k2) const {
    const unsigned long end = (isValidIndex(k2)) ? k2 : dim() - 1;
    const unsigned long dim = end - k1 + 1;

    if(isValidIndex(k1) && dim > 0) {
        vector<double> data(dim);
        for (unsigned long k = k1; k <= end; ++k) {
            data[k - k1] = (*this)[k];
        }
        return data;
    }
    else return NVector(0);
}

void NVector::setSubVector(const NVector &vector) {
    if(isValidIndex(_k1) && isValidIndex(_k2) && vector.dim() >= _k2 - _k1 + 1) {
        for (unsigned long k = _k1; k <= _k2; ++k) {
            (*this)[k] = vector[k - _k1];
        }
    }
}


// VECTOR SPACE METHODS

void NVector::add(const NVector& vector) {
    if(dim() == vector.dim()) {
        for(unsigned long k = 0; k < dim(); k++) {
            (*this)[k] += vector[k];
        }
    }
}

void NVector::sub(const NVector& vector) {
    if(dim() == vector.dim()) {
        for(unsigned long k = 0; k < dim(); k++) {
            (*this)[k] -= vector[k];
        }
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


























