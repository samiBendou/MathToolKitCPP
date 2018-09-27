//
// Created by Sami Dahoux on 03/05/2018.
//

#include <NVector.h>

#include "../header/NVector.h"

using namespace std;


// CONSTRUCTORS


NVector::NVector(unsigned long dim) :
    vector<double>(dim), _k1(0), _k2(0) {
    setDefaultBrowseIndices();
}

NVector::NVector(const std::vector<double>& data) :
    vector<double>(data), _k1(0), _k2(0) {
    setDefaultBrowseIndices();
}

NVector::NVector(const NVector &u) :
    vector<double>(u), _k1(0), _k2(0) {
    copy(u);
}

NVector::NVector(const std::string &str) :
    std::vector<double>(0), _k1(0), _k2(0) {
    parse(str);
    setDefaultBrowseIndices();
}


// SERIALIZATION


string NVector::str() const {
    string str = "(";
    char buffer[6];
    for (auto it = this->begin() + _k1; it != this->begin() + _k2 + 1; ++it) {
        sprintf(buffer, "%.2e", abs(*it));
        str += (*it >= 0 ? "  " : " -");
        str += buffer;
    }
    str += "  )";
    setDefaultBrowseIndices();
    return str;
}

// GETTERS


unsigned long NVector::dim() const {
    unsigned long res = _k2 - _k1 + 1;
    setDefaultBrowseIndices();
    return res;
}

std::vector<double> NVector::array() const {
    std::vector<double> res(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return res;
}


// SWAP


void NVector::swap(unsigned long k1, unsigned long k2) {
    assert(isBetweenK12(k1) && isBetweenK12(k2));

    const double temp = (*this)[k1];
    (*this)[k1] = (*this)[k2];
    (*this)[k2] = temp;

    setDefaultBrowseIndices();
}


// SHIFT


void NVector::shift(long iterations) {

    auto sizedDim = _k2 - _k1 + 1;
    auto sizedIterations = (abs(iterations) % sizedDim);
    auto shiftIndex = (iterations >= 0 ? sizedIterations : sizedDim - sizedIterations);

    if(shiftIndex > 0) {
        long index;
        NVector temp{this->subVector(0, this->size() - 1)};

        for (unsigned long k = _k1; k <= _k2; ++k) {
            index = (k + shiftIndex) % sizedDim;
            temp[k] = (*this)[index];
        }
        setDefaultBrowseIndices();
        (*this) = temp;
    }
    setDefaultBrowseIndices();
}


// FILL


void NVector::fill(const double scalar) {
    for (auto it = this->begin() + _k1; it != this->begin() + _k2 + 1; ++it) {
        *it = scalar;
    }
    setDefaultBrowseIndices();
}

// MAX / MIN


double NVector::max() const{
    auto resIt = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return *resIt;
}

double NVector::min() const{
    auto resIt = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return *resIt;
}

unsigned long NVector::maxIndex() const{
    auto maxIt = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    unsigned long res = (unsigned long) std::distance(this->begin() + _k1, maxIt);
    setDefaultBrowseIndices();
    return res;
}

unsigned long NVector::minIndex() const{
    auto minIt = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    unsigned long res = (unsigned long) std::distance(this->begin() + _k1, minIt);
    setDefaultBrowseIndices();
    return res;
}

// ABSOLUTE VALUE MAX / MIN


double NVector::maxAbs() const{
    auto maxIt = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto minIt = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return abs(*maxIt) > abs(*minIt) ? abs(*maxIt) : abs(*minIt);
}

double NVector::minAbs() const{
    auto maxIt = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto minIt = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return abs(*maxIt) <= abs(*minIt) ? abs(*maxIt) : abs(*minIt);
}

unsigned long NVector::maxAbsIndex() const{
    auto maxIt = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto minIt = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    unsigned long res;

    if(abs(*maxIt) > abs(*minIt)) {
        res = (unsigned long) std::distance(this->begin() + _k1, maxIt);
    } else {
        res = (unsigned long) std::distance(this->begin() + _k1, minIt);
    }
    setDefaultBrowseIndices();
    return res;
}

unsigned long NVector::minAbsIndex() const{
    auto maxIt = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto minIt = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    unsigned long res;

    if(abs(*maxIt) <= abs(*minIt)) {
        res = (unsigned long) std::distance(this->begin() + _k1, maxIt);
    } else {
        res = (unsigned long) std::distance(this->begin() + _k1, minIt);
    }
    setDefaultBrowseIndices();
    return res;
}




// OPERATORS


NVector NVector::operator+(const NVector &u) const{
    NVector res{*this};
    res += u;
    return res;
}

NVector NVector::operator-(const NVector &u) const{
    NVector res{*this};
    res -= u;
    return res;
}

NVector NVector::operator-() const {
    NVector res{*this};
    res.opp();
    return res;
}


NVector operator*(double s, const NVector &u){
    NVector res{u};
    res *= s;
    return res;
}

NVector operator*(const NVector &u, double s){
    return operator*(s, u);
}


NVector operator/(const NVector &u, double s){
    NVector res{u};
    res /= s;
    return res;
}


// SCALAR PRODUCT BASED OPERATIONS


double operator!(const NVector &vector) {
    return vector.norm();
}

double operator*(const NVector &u, const NVector &v) {
    return u.dot(v);
}

double operator/(const NVector &u, const NVector &v) {
    return u.distance(v);
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
    auto index = (k >= 0 ? k : _k2 - k);
    assert(isValidIndex(index));
    return (*this)[index];
}

double NVector::operator()(long k) const {
    auto index = (k >= 0 ? k : _k2 - k);
    assert(isValidIndex(index));
    return (*this).at(index);
}

NVector NVector::operator()(unsigned long k1, unsigned long k2) const {
    return subVector(k1, k2);
}

NVector &NVector::operator()(unsigned long k1, unsigned long k2) {
    assert(isValidIndex(k1) && isValidIndex(k2) && k2 >= k1);
    _k1 = k1; _k2 = k2;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const NVector &vector) {
    os << vector.str();
    return os;
}


// AFFECTATION


NVector &NVector::operator=(const NVector &vector) {
    copy(vector);
    return *this;
}

NVector &NVector::operator=(const std::string &str) {
    parse(str);
    return *this;
}

// NORM BASED COMPARISON OPERATORS

bool operator==(const NVector &u, const NVector &v) {
    bool result = u.isEqual(v);
    return result;
}

bool operator==(const NVector &u, double s) {
    bool res = s < std::numeric_limits<double>::epsilon() && u.isNull();
    u.setDefaultBrowseIndices();
    return res;
}

bool operator!=(const NVector &u, const NVector &v) { return !(u == v); }

bool operator!=(const NVector &u, double s) { return !(u == s); }

// STATIC METHODS

NVector NVector::zeros(unsigned long dim) {
    return scalar(0.0, dim);
}

NVector NVector::ones(unsigned long dim) {
    return scalar(1.0, dim);
}

NVector NVector::scalar(double s, unsigned long dim) {
    NVector scalarVector = NVector(dim);
    scalarVector.fill(s);
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

    assert(scalars.size() == vectors.size());

    for (unsigned long k = 0; k < scalars.size(); ++k) {
        sumProd += scalars[k] * vectors[k];
    }
    return sumProd;
}

// PROTECTED METHODS


// VECTOR SPACE METHODS

void NVector::add(const NVector& vector) {
    assert(isCompatible(vector));

    for(unsigned long k = 0; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] += vector[k + vector._k1];
    }
    setDefaultBrowseIndices();
    vector.setDefaultBrowseIndices();
}

void NVector::sub(const NVector& vector) {
    assert(isCompatible(vector));

    for(unsigned long k = _k1; k <= _k2 - _k1; k++) {
        (*this)(k + _k1) -= vector(k + vector._k1);
    }
    setDefaultBrowseIndices();
    vector.setDefaultBrowseIndices();
}

void NVector::opp() {
    for(unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] = -(*this)[k];
    }
    setDefaultBrowseIndices();
}

void NVector::prod(double scalar) {
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] *= scalar;
    }
    setDefaultBrowseIndices();
}

void NVector::div(double scalar) {
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] /= scalar;
    }
    setDefaultBrowseIndices();
}

// EUCLIDEAN SPACE OPERATIONS

double NVector::dot(const NVector &vector) const {
    double dot = 0.0;

    assert(isCompatible(vector));
    for (unsigned long k = 0; k <= _k2 - _k1; ++k) {
        dot += vector(k + vector._k1) * (*this)(k + _k1);
    }
    setDefaultBrowseIndices();
    vector.setDefaultBrowseIndices();
    return dot;
}

double NVector::norm() const {
    return sqrt(dot(*this));
}

double NVector::distance(const NVector &vector) const {
    double d = (*this - vector).norm();
    setDefaultBrowseIndices();
    vector.setDefaultBrowseIndices();
    return d;
}


// PRIVATE METHODS

//CHARACTERIZATION

bool NVector::isValidIndex(unsigned long k) const {
    return k < this->size();
}

bool NVector::isNull() const {
    return norm() < numeric_limits<double>::epsilon();
}

bool NVector::isEqual(const NVector& vector) const {
    if(!isCompatible(vector))
        return false;
    return distance(vector) < numeric_limits<double>::epsilon();
}

bool NVector::isBetweenK12(unsigned long k) const {
    return k >= _k1 && k <= _k2;
}

bool NVector::isCompatible(const NVector &vector) const {
    return _k2 - _k1 == vector._k2 - vector._k1;
}

bool NVector::hasDefaultBrowseIndices() const {
    return _k1 == 0 && (_k2 == this->size() - 1 || _k2 == 0);
}

void NVector::setDefaultBrowseIndices() const {
    _k1 = 0; _k2 = (this->size() > 0) ? this->size() - 1 : 0;
}




// AFFECTATION

void NVector::copy(const NVector &vector) {
    if(this != &vector && vector.size() > 0) {
        if (hasDefaultBrowseIndices() && vector.hasDefaultBrowseIndices()){
            this->std::vector<double>::operator=(vector);
        }
        else if (hasDefaultBrowseIndices()) {
            this->std::vector<double>::operator=(vector.subVector(vector._k1, vector._k2));
        }
        else {
            setSubVector(vector);
        }
        setDefaultBrowseIndices();
        vector.setDefaultBrowseIndices();
    }
}

void NVector::parse(const std::string &str) {
    vector<double> data{};
    string::size_type sz = 1;
    unsigned long i = 0;

    if(str.find(",") == string::npos) {
        while(i < str.size() || str[i] == '\n') {
            try {
                data.push_back(std::stod(str.substr(i, str.size() - i), &sz));
                i += sz;
            }
            catch(const std::exception& e) {
                i++;
            }
        }
    }
    this->copy(NVector(data));
}

// SUB-VECTORS

NVector NVector::subVector(unsigned long k1, unsigned long k2) const {
    unsigned long dim = k2 - k1 + 1;

    assert(isValidIndex(k1) && isValidIndex(k2) && dim > 0);

    vector<double> data(dim);
    for (unsigned long k = k1; k <= k2; ++k) {
        data[k - k1] = (*this)[k];
    }
    return data;
}

void NVector::setSubVector(const NVector &vector) {

    assert(isCompatible(vector));

    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] = vector[k + vector._k1];
    }
    setDefaultBrowseIndices();
    vector.setDefaultBrowseIndices();
}





















































