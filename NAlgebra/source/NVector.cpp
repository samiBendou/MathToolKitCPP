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
    setDefaultBrowseIndices();
    return str;
}


// GETTERS


unsigned long NVector::dim() const {
    return this->size();
}

unsigned long NVector::dim() {
    unsigned long res = _k2 - _k1 + 1;
    setDefaultBrowseIndices();
    return res;
}


std::vector<double> NVector::array() const {
    return *this;
}

std::vector<double> NVector::array() {
    std::vector<double> res = this->subVector(_k1, _k2);
    setDefaultBrowseIndices();
    return res;
}


// SWAP


void NVector::swap(unsigned long k1, unsigned long k2) {
    assert(k1 >= _k1 && k2 <= _k2);

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
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] = scalar;
    }
    setDefaultBrowseIndices();
}


// MAX / MIN


double NVector::max() const{
    return getExtremum(true);
}

double NVector::max() {
    double res = getExtremum(true);
    setDefaultBrowseIndices();
    return res;
}

double NVector::min() const{
    return getExtremum(false);
}

double NVector::min() {
    double res = getExtremum(false);
    setDefaultBrowseIndices();
    return res;
}


unsigned long NVector::maxIndex() const{
    return getExtremumIndex(true);
}

unsigned long NVector::maxIndex() {
    unsigned long res = getExtremumIndex(true);
    setDefaultBrowseIndices();
    return res;
}

unsigned long NVector::minIndex() const{
    return getExtremumIndex(false);
}

unsigned long NVector::minIndex() {
    unsigned long res = getExtremumIndex(false);
    setDefaultBrowseIndices();
    return res;
}


// ABSOLUTE VALUE MAX / MIN


double NVector::maxAbs() const{
    return getExtremumAbs(true);
}

double NVector::maxAbs() {
    double res = getExtremumAbs(true);
    setDefaultBrowseIndices();
    return res;
}

double NVector::minAbs() const{
    return getExtremumAbs(false);
}


double NVector::minAbs() {
    double res = getExtremumAbs(false);
    setDefaultBrowseIndices();
    return res;
}


unsigned long NVector::maxAbsIndex() const{
    return getExtremumAbsIndex(true);
}

unsigned long NVector::maxAbsIndex() {
    unsigned long res = getExtremumAbsIndex(true);
    setDefaultBrowseIndices();
    return res;
}


unsigned long NVector::minAbsIndex() const{
    return getExtremumAbsIndex(false);
}

unsigned long NVector::minAbsIndex() {
    unsigned long res = getExtremumAbsIndex(false);
    setDefaultBrowseIndices();
    return res;
}


// OPERATORS


NVector NVector::operator+(const NVector &u) const{
    NVector res{*this};
    res += u;
    return res;
}

NVector NVector::operator+(const NVector &u) {
    NVector res{*this};
    res += u;
    this->setDefaultBrowseIndices();
    return res;
}

NVector NVector::operator+(NVector &u) {
    NVector res{*this};
    res += u;
    this->setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
    return res;
}

NVector NVector::operator+(NVector &u) const {
    NVector res{*this};
    res += u;
    u.setDefaultBrowseIndices();
    return res;
}


NVector NVector::operator-(const NVector &u) const{
    NVector res{*this};
    res -= u;
    return res;
}

NVector NVector::operator-(const NVector &u) {
    NVector res{u};
    res -= u;
    this->setDefaultBrowseIndices();
    return res;
}

NVector NVector::operator-(NVector &u) {
    NVector res{*this};
    res -= u;
    this->setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
    return res;
}

NVector NVector::operator-(NVector &u) const {
    NVector res{*this};
    res -= u;
    u.setDefaultBrowseIndices();
    return res;
}


NVector NVector::operator-() {
    NVector res{*this};
    res.opp();
    this->setDefaultBrowseIndices();
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

NVector operator*(double s, NVector &u) {
    NVector res{u};
    res *= s;
    u.setDefaultBrowseIndices();
    return res;
}

NVector operator*(const NVector &u, double s){
    return operator*(s, u);
}

NVector operator*(NVector &u, double s) {
    return operator*(s, u);
}



NVector operator/(const NVector &u, double s){
    NVector res{u};
    res /= s;
    return res;
}

NVector operator/(NVector &u, double s) {
    NVector res{u};
    res /= s;
    u.setDefaultBrowseIndices();
    return res;
}


// SCALAR PRODUCT BASED OPERATIONS


double operator!(const NVector &vector) {
    return vector.norm();
}

double operator!(NVector &vector) {
    double res = vector.norm();
    vector.setDefaultBrowseIndices();
    return res;
}


double operator*(const NVector &u, const NVector &v) {
    return u.dot(v);
}

double operator*(const NVector &u, NVector &v) {
    double res = u.dot(v);
    v.setDefaultBrowseIndices();
    return res;
}

double operator*(NVector &u, const NVector &v) {
    return operator*(v, u);
}

double operator*(NVector &u, NVector &v) {
    double res = u.dot(v);
    u.setDefaultBrowseIndices();
    v.setDefaultBrowseIndices();
    return res;
}


double operator/(const NVector &u, const NVector &v) {
    return u.distance(v);
}

double operator/(const NVector &u, NVector &v) {
    double res = u.distance(v);
    v.setDefaultBrowseIndices();
    return res;
}

double operator/(NVector &u, const NVector &v) {
    return operator/(v, u);
}

double operator/(NVector &u, NVector &v) {
    double res = u.distance(v);
    u.setDefaultBrowseIndices();
    v.setDefaultBrowseIndices();
    return res;
}



// COMPOUND OPERATORS


NVector &NVector::operator+=(const NVector &vector) {
    this->add(vector);
    return *this;
}

NVector &NVector::operator+=(NVector &vector) {
    this->add(vector);
    vector.setDefaultBrowseIndices();
    return *this;
}


NVector &NVector::operator-=(const NVector &vector) {
    this->sub(vector);
    return *this;
}

NVector &NVector::operator-=(NVector &vector) {
    this->sub(vector);
    vector.setDefaultBrowseIndices();
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
    assert(isValidIndex((unsigned long) k));
    return (*this)[(k >= 0) ? k : dim() + k - 1];
}

double NVector::operator()(long k) const {
    assert(isValidIndex((unsigned long) k));
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

std::ostream& operator<<(std::ostream& os, const NVector &vector) {
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
    vector.setDefaultBrowseIndices();
    return *this;
}


NVector &NVector::operator=(const std::string &str) {
    *this = NVector(str);
    return *this;
}

// NORM BASED COMPARISON OPERATORS

bool operator==(const NVector &u, const NVector &v) {
    return u.isEqual(v);
}


bool operator==(NVector &u, NVector &v) {
    bool result = u.isEqual(v);
    u.setDefaultBrowseIndices();
    v.setDefaultBrowseIndices();
    return result;
}

bool operator==(NVector &u, const NVector &v) {
    bool result = u.isEqual(v);
    u.setDefaultBrowseIndices();
    return result;
}

bool operator==(const NVector &u, NVector &v) {
    bool result = u.isEqual(v);
    v.setDefaultBrowseIndices();
    return result;
}

bool operator==(const NVector &u, double s) {
    return s < std::numeric_limits<double>::epsilon() && u.isNull();
}

bool operator==(NVector &u, double s) {
    bool res = s < std::numeric_limits<double>::epsilon() && u.isNull();
    u.setDefaultBrowseIndices();
    return res;
}



bool operator!=(const NVector &u, const NVector &v) { return !(u == v); }

bool operator!=(NVector& u, NVector& v) {return !(u == v);}

bool operator!=(NVector& u, const NVector& v) {return !(u == v);}

bool operator!=(const NVector& u, NVector& v) {return !(u == v);}


bool operator!=(const NVector& u, double s) {return !(u == s);}

bool operator!=(NVector& u, double s) {return !(u == s);}

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

// PRIVATE METHODS


//CHARACTERIZATION

bool NVector::isValidIndex(unsigned long k) const {
    return k < dim();
}

bool NVector::isNull() const {
    return norm() < numeric_limits<double>::epsilon();
}

bool NVector::isEqual(const NVector& vector) const {
    if(!isCompatible(vector))
        return false;
    return distance(vector) < numeric_limits<double>::epsilon();
}

bool NVector::isCompatible(const NVector &vector) const {
    return _k2 - _k1 == vector._k2 - vector._k1;
}

bool NVector::haveDefaultBrowseIndices() const {
    return _k1 == 0 && (_k2 == this->size() - 1 || _k2 == 0);
}

void NVector::setDefaultBrowseIndices() {
    _k1 = 0; _k2 = (this->size() > 0) ? this->size() - 1 : 0;
}




// AFFECTATION

void NVector::copy(const NVector &vector) {
    if(this != &vector && vector.dim() > 0) {
        if (haveDefaultBrowseIndices() && vector.haveDefaultBrowseIndices()){
            this->std::vector<double>::operator=(vector);
        }
        else if (haveDefaultBrowseIndices()) {
            this->std::vector<double>::operator=(vector.subVector(vector._k1, vector._k2));
        }
        else {
            setSubVector(vector);
        }
        setDefaultBrowseIndices();
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


// EXTREMUMS

double NVector::getExtremum(const bool max) const {
    const double infinity = numeric_limits<double>::infinity();

    double extremum = (max) ? -infinity : infinity;

    for (unsigned long k = _k1; k <= _k2; ++k) {
        if(max)
            extremum = (extremum < (*this)[k]) ? (*this)[k] : extremum;
        else
            extremum = (extremum > (*this)[k]) ? (*this)[k] : extremum;
    }
    return extremum;
}

unsigned long NVector::getExtremumIndex(bool max) const {
    double extremum = (max) ? this->max() : this->min();
    for (unsigned long k = _k1; k <= _k2; ++k) {
        if((*this)[k] == extremum) {
            return k - _k1;
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
}


// VECTOR SPACE METHODS

void NVector::add(const NVector& vector) {
    assert(isCompatible(vector));

    for(unsigned long k = 0; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] += vector[k + vector._k1];
    }
    setDefaultBrowseIndices();
}

void NVector::sub(const NVector& vector) {
    assert(isCompatible(vector));

    for(unsigned long k = _k1; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] -= vector[k + vector._k1];
    }
    setDefaultBrowseIndices();
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
    return dot;
}

double NVector::norm() const {
    return sqrt(dot(*this));
}

double NVector::distance(const NVector &vector) const {
    return (*this - vector).norm();
}



















































