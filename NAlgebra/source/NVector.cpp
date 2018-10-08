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

NVector::NVector(const std::vector<double> &data) :
        vector<double>(data), _k1(0), _k2(0) {
    setDefaultBrowseIndices();
}

NVector::NVector(const NVector &u) :
        vector<double>(0), _k1(0), _k2(0) {
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
    for (auto k = _k1; k <= _k2; ++k) {
        sprintf(buffer, "%.2e", abs((*this)[k]));
        str += ((*this)[k] >= 0 ? "  " : " -");
        str += buffer;
    }
    str += "  )";
    setDefaultBrowseIndices();
    return str;
}

// GETTERS


unsigned long NVector::dim() const {
    auto res = _k2 - _k1 + 1;
    setDefaultBrowseIndices();
    return res;
}

std::vector<double> NVector::array() const {
    std::vector<double> res(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return res;
}

// MAX / MIN


double NVector::max() const {
    auto res_it = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return *res_it;
}

double NVector::min() const {
    auto res_it = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    setDefaultBrowseIndices();
    return *res_it;
}

unsigned long NVector::maxIndex() const {
    auto max_it = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto res = (unsigned long) std::distance(this->begin() + _k1, max_it);
    setDefaultBrowseIndices();
    return res;
}

unsigned long NVector::minIndex() const {
    auto min_it = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);
    unsigned long res = (unsigned long) std::distance(this->begin() + _k1, min_it);
    setDefaultBrowseIndices();
    return res;
}

// ABSOLUTE VALUE MAX / MIN


double NVector::maxAbs() const {

    auto max_it = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto min_it = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);

    setDefaultBrowseIndices();

    return abs(*max_it) > abs(*min_it) ? abs(*max_it) : abs(*min_it);
}

double NVector::minAbs() const {

    auto max_it = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto min_it = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);

    setDefaultBrowseIndices();

    return abs(*max_it) <= abs(*min_it) ? abs(*max_it) : abs(*min_it);
}

unsigned long NVector::maxAbsIndex() const {

    auto max_it = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto min_it = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);

    unsigned long res;
    if (abs(*max_it) > abs(*min_it)) {
        res = (unsigned long) std::distance(this->begin() + _k1, max_it);
    } else {
        res = (unsigned long) std::distance(this->begin() + _k1, min_it);
    }

    setDefaultBrowseIndices();

    return res;
}

unsigned long NVector::minAbsIndex() const {

    auto max_it = std::max_element(this->begin() + _k1, this->begin() + _k2 + 1);
    auto min_it = std::min_element(this->begin() + _k1, this->begin() + _k2 + 1);

    unsigned long res;
    if (abs(*max_it) <= abs(*min_it)) {
        res = (unsigned long) std::distance(this->begin() + _k1, max_it);
    } else {
        res = (unsigned long) std::distance(this->begin() + _k1, min_it);
    }

    setDefaultBrowseIndices();

    return res;
}


// MANIPULATORS


// SWAP


void NVector::swap(unsigned long k1, unsigned long k2) {
    assert(isBetweenK12(k1) && isBetweenK12(k2));

    auto temp = (*this)[k1];
    (*this)[k1] = (*this)[k2];
    (*this)[k2] = temp;

    setDefaultBrowseIndices();
}


// SHIFT


void NVector::shift(long iterations) {
    auto sized_dim = _k2 - _k1 + 1;
    auto sized_iterations = (abs(iterations) % sized_dim);
    auto shift_index = (iterations >= 0 ? sized_iterations : sized_dim - sized_iterations);

    std::rotate(this->begin() + _k1, this->begin() + _k1 + shift_index, this->begin() + _k2 + 1);

    setDefaultBrowseIndices();
}


// FILL


void NVector::fill(double s) {
    std::fill(this->begin() + _k1, this->begin() + _k2 + 1, s);
    setDefaultBrowseIndices();
}



// OPERATORS


NVector NVector::operator+(const NVector &u) const {
    NVector res{*this};
    res += u;
    return res;
}

NVector NVector::operator-(const NVector &u) const {
    NVector res{*this};
    res -= u;
    return res;
}

NVector NVector::operator-() const {
    NVector res{*this};
    res.opp();
    return res;
}


NVector operator*(double s, const NVector &u) {
    NVector res{u};
    res *= s;
    return res;
}

NVector operator*(const NVector &u, double s) {
    return operator*(s, u);
}


NVector operator/(const NVector &u, double s) {
    NVector res{u};
    res /= s;
    return res;
}


// SCALAR PRODUCT BASED OPERATIONS

double operator|(const NVector &u, const NVector &v) {
    return u.dotProduct(v);
}

double operator!(const NVector &u) {
    return u.norm();
}

double operator/(const NVector &u, const NVector &v) {
    return u.distance(v);
}


// COMPOUND OPERATORS


NVector &NVector::operator+=(const NVector &u) {
    this->add(u);
    return *this;
}

NVector &NVector::operator-=(const NVector &u) {
    this->sub(u);
    return *this;
}

NVector &NVector::operator*=(double s) {
    this->prod(s);
    return *this;
}

NVector &NVector::operator/=(double s) {
    this->div(s);
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
    assert(isValidIndex(k1) && isValidIndex(k2));
    assert(k2 >= k1);

    _k1 = k1;
    _k2 = k2;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const NVector &vector) {
    os << vector.str();
    return os;
}


// AFFECTATION

NVector &NVector::operator=(const NVector &u) {
    copy(u);
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

bool operator==(const NVector &u, const std::string &str) {
    return u == NVector(str);
}

bool operator==(const std::string &str, const NVector &u) {
    return u == str;
}


bool operator==(const NVector &u, double s) {
    bool res = s < std::numeric_limits<double>::epsilon() && u.isNull();
    u.setDefaultBrowseIndices();
    return res;
}

bool operator!=(const NVector &u, const NVector &v) { return !(u == v); }

bool operator!=(const NVector &u, const std::string &str) {
    return !(u == str);
}

bool operator!=(const std::string &str, const NVector &u) {
    return u != str;
}

bool operator!=(const NVector &u, double s) { return !(u == s); }

// STATIC METHODS

NVector NVector::zeros(unsigned long dim) {
    return scalar(0.0, dim);
}

NVector NVector::ones(unsigned long dim) {
    return scalar(1.0, dim);
}

NVector NVector::scalar(double s, unsigned long dim) {
    NVector scalar{dim};
    scalar.fill(s);
    return scalar;
}

NVector NVector::canonical(unsigned long k, unsigned long dim) {
    assert(k < dim);

    NVector canonical = NVector::zeros(dim);
    canonical(k) = 1.0;
    return canonical;
}

NVector NVector::sum(const std::vector<NVector> &vectors) {
    NVector sum = NVector::zeros(vectors[0].dim());

    for (const auto &vector : vectors) {
        sum += vector;
    }
    return sum;
}

NVector NVector::sumProd(const std::vector<double> &scalars, const std::vector<NVector> &vectors) {
    NVector sum_prod = NVector::zeros(vectors[0].dim());

    assert(scalars.size() == vectors.size());

    for (unsigned long k = 0; k < scalars.size(); ++k) {
        sum_prod += scalars[k] * vectors[k];
    }
    return sum_prod;
}

// PROTECTED METHODS

// VECTOR SPACE METHODS

void NVector::add(const NVector &u) {
    assert(hasSameSize(u));

    for (unsigned long k = 0; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] += u[k + u._k1];
    }
    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
}

void NVector::sub(const NVector &u) {
    assert(hasSameSize(u));

    for (unsigned long k = _k1; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] -= u[k + u._k1];
    }
    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
}

void NVector::opp() {
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] = -(*this)[k];
    }
    setDefaultBrowseIndices();
}

void NVector::prod(double s) {
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] *= s;
    }
    setDefaultBrowseIndices();
}

void NVector::div(double s) {
    for (unsigned long k = _k1; k <= _k2; ++k) {
        (*this)[k] /= s;
    }
    setDefaultBrowseIndices();
}

// EUCLIDEAN SPACE OPERATIONS

double NVector::dotProduct(const NVector &u) const {
    double dot = 0.0;

    assert(hasSameSize(u));
    for (unsigned long k = 0; k <= _k2 - _k1; ++k) {
        dot += u[k + u._k1] * (*this)[k + _k1];
    }
    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
    return dot;
}

double NVector::norm() const {
    return sqrt(dotProduct(*this));
}

double NVector::distance(const NVector &u) const {
    double d = (*this - u).norm();

    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();

    return d;
}

//CHARACTERIZATION

bool NVector::isValidIndex(unsigned long k) const {
    return k < this->size();
}

bool NVector::isNull() const {
    return norm() < numeric_limits<double>::epsilon();
}

bool NVector::isEqual(const NVector &u) const {
    if (!hasSameSize(u))
        return false;
    return distance(u) < numeric_limits<double>::epsilon();
}

bool NVector::isBetweenK12(unsigned long k) const {
    return k >= _k1 && k <= _k2;
}

bool NVector::hasSameSize(const NVector &u) const {
    return _k2 - _k1 == u._k2 - u._k1;
}

bool NVector::hasDefaultBrowseIndices() const {
    return _k1 == 0 && (_k2 == this->size() - 1 || _k2 == 0);
}

void NVector::setDefaultBrowseIndices() const {
    _k1 = 0;
    _k2 = (this->size() > 0) ? this->size() - 1 : 0;
}

// AFFECTATION

void NVector::copy(const NVector &u) {
    if (this != &u && u.size() > 0) {
        if (hasDefaultBrowseIndices() && u.hasDefaultBrowseIndices()) {
            this->std::vector<double>::operator=(u);
        } else if (hasDefaultBrowseIndices()) {
            this->std::vector<double>::operator=(u.subVector(u._k1, u._k2));
        } else {
            setSubVector(u);
        }
        setDefaultBrowseIndices();
        u.setDefaultBrowseIndices();
    }
}

void NVector::parse(const std::string &str) {
    vector<double> data{};
    string::size_type sz = 1;
    unsigned long i = 0;

    assert(str.find(",") == string::npos);

    while (i < str.size() && str[i] != ')') {
        try {
            data.push_back(std::stod(str.substr(i, str.size() - i), &sz));
            i += sz;
        }
        catch (const std::exception &e) {
            i++;
        }
    }

    this->copy(NVector(data));
}

// SUB-VECTORS

NVector NVector::subVector(unsigned long k1, unsigned long k2) const {
    unsigned long dim = k2 - k1 + 1;

    assert(isValidIndex(k1) && isValidIndex(k2) && dim > 0);

    vector<double> data(dim);
    std::copy(this->begin() + k1, this->begin() + k2 + 1, data.begin());

    return data;
}

void NVector::setSubVector(const NVector &u) {

    assert(hasSameSize(u));

    std::copy(u.begin() + u._k1, u.begin() + u._k2 + 1, this->begin() + _k1);

    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
}

















































