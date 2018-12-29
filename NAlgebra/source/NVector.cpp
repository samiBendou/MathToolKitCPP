//
// Created by Sami Dahoux on 03/05/2018.
//

#include <NVector.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wabsolute-value"

using namespace std;

// CONSTRUCTORS

template<typename T>
NVector<T>::NVector(const std::vector<T> &data) :
        vector<T>(data), _k1(0), _k2(0) {
    setDefaultBrowseIndices();
}

template<typename T>
NVector<T>::NVector(initializer_list<T> list) :
        vector<T>(list), _k1(0), _k2(0) {
    setDefaultBrowseIndices();
}

template<typename T>
NVector<T>::NVector(ul_t dim) :
        vector<T>(dim), _k1(0), _k2(0) {
    setDefaultBrowseIndices();
}

template<typename T>
NVector<T>::NVector(const NVector<T> &u) :
        vector<T>(0), _k1(0), _k2(0) {
    copy(u);
}

// SERIALIZATION

template<typename T>
string NVector<T>::str() const {
    stringstream stream;

    stream << '(';
    for (auto k = _k1; k <= _k2; ++k) {
        stream << ((*this)[k] >= 0 ? ' ' : '-') << abs((*this)[k]);
    }
    stream << " )";
    setDefaultBrowseIndices();
    return stream.str();
}

// GETTERS

template<typename T>
ul_t NVector<T>::dim() const {
    auto res = _k2 - _k1 + 1;
    setDefaultBrowseIndices();
    return res;
}

template<typename T>
std::vector<T> NVector<T>::array() const {
    std::vector<T> res(begin(), end());
    setDefaultBrowseIndices();
    return res;
}

// MAX / MIN

template<typename T>
T NVector<T>::max() const {
    auto res_it = std::max_element(begin(), end());
    setDefaultBrowseIndices();
    return *res_it;
}

template<typename T>
T NVector<T>::min() const {
    auto res_it = std::min_element(begin(), end());
    setDefaultBrowseIndices();
    return *res_it;
}

template<typename T>
ul_t NVector<T>::maxIndex() const {
    auto max_it = std::max_element(begin(), end());
    auto res = (ul_t) std::distance(begin(), max_it);
    setDefaultBrowseIndices();
    return res;
}

template<typename T>
ul_t NVector<T>::minIndex() const {
    auto min_it = std::min_element(begin(), end());
    ul_t res = (ul_t) std::distance(begin(), min_it);
    setDefaultBrowseIndices();
    return res;
}

// ABSOLUTE VALUE MAX / MIN

template<typename T>
T NVector<T>::maxAbs() const {

    auto minmax_it = std::minmax_element(begin(), end());

    setDefaultBrowseIndices();
    return abs(*minmax_it.second) > abs(*minmax_it.first) ? abs(*minmax_it.second) : abs(*minmax_it.first);
}

template<typename T>
T NVector<T>::minAbs() const {

    auto minmax_it = std::minmax_element(begin(), end());

    setDefaultBrowseIndices();
    return abs(*minmax_it.second) <= abs(*minmax_it.first) ? abs(*minmax_it.second) : abs(*minmax_it.first);
}

template<typename T>
ul_t NVector<T>::maxAbsIndex() const {
    auto min_it = std::min_element(begin(), end()), max_it = std::max_element(begin(), end());

    ul_t res = (ul_t) std::distance(begin(), (abs(*min_it) > abs(*max_it)) ? min_it : max_it);
    setDefaultBrowseIndices();

    return res;
}

template<typename T>
ul_t NVector<T>::minAbsIndex() const {
    auto min_it = std::min_element(begin(), end()), max_it = std::max_element(begin(), end());

    ul_t res = (ul_t) std::distance(begin(), (abs(*min_it) <= abs(*max_it)) ? min_it : max_it);
    setDefaultBrowseIndices();

    return res;
}


// MANIPULATORS


// SWAP

template<typename T>
NVector<T> &NVector<T>::swap(ul_t k1, ul_t k2) {
    assert(isBetweenK12(k1) && isBetweenK12(k2));
    std::iter_swap(begin() + k1, begin() + k2);
    setDefaultBrowseIndices();
    return *this;
}


// SHIFT

template<typename T>
NVector<T> &NVector<T>::shift(long iterations) {
    auto sized_dim = _k2 - _k1 + 1;
    auto sized_iterations = (abs(iterations) % sized_dim);
    auto shift_index = (iterations >= 0 ? sized_iterations : sized_dim - sized_iterations);

    std::rotate(begin(), begin() + shift_index, end());

    setDefaultBrowseIndices();
    return *this;
}


// FILL

template<typename T>
NVector<T> &NVector<T>::fill(T s) {
    std::fill(begin(), end(), s);
    setDefaultBrowseIndices();
    return *this;
}



// OPERATORS

template<typename T>
NVector<T> NVector<T>::operator-() const {
    NVector<T> res{*this};
    res.opp();
    return res;
}

// SCALAR PRODUCT BASED OPERATIONS


template<typename T>
T operator/(const NVector<T> &u, const NVector<T> &v) {
    return u.distance(v);
}


// COMPOUND OPERATORS


template<typename T>
NVector<T> &NVector<T>::operator+=(const NVector<T> &u) {
    return add(u);
}

template<typename T>
NVector<T> &NVector<T>::operator-=(const NVector<T> &u) {
    return sub(u);
}

template<typename T>
NVector<T> &NVector<T>::operator*=(T s) {
    return prod(s);
}

template<typename T>
NVector<T> &NVector<T>::operator/=(T s) {
    return div(s);
}

// ACCES OPERATOR


template<typename T>
T &NVector<T>::operator()(long k) {
    auto index = (k >= 0 ? k : _k2 - k);
    assert(isValidIndex(index));
    return (*this)[index];
}

template<typename T>
T NVector<T>::operator()(long k) const {
    auto index = (k >= 0 ? k : _k2 - k);
    assert(isValidIndex(index));
    return (*this).at(index);
}

template<typename T>
NVector<T> NVector<T>::operator()(ul_t k1, ul_t k2) const {
    return subVector(k1, k2);
}

template<typename T>
NVector<T> &NVector<T>::operator()(ul_t k1, ul_t k2) {
    assert(isValidIndex(k1) && isValidIndex(k2));
    assert(k2 >= k1);

    _k1 = k1;
    _k2 = k2;

    return *this;
}

// AFFECTATION

template<typename T>
NVector<T> &NVector<T>::operator=(const NVector<T> &u) {
    copy(u);
    return *this;
}

// NORM BASED COMPARISON OPERATORS

template<typename T>
bool operator==(const NVector<T> &u, T s) {
    bool res = s < EPSILON && u.isNull();
    u.setDefaultBrowseIndices();
    return res;
}

template<typename T>
bool operator!=(const NVector<T> &u, const NVector<T> &v) {
    return !(u == v);
}

template<typename T>
bool operator!=(const NVector<T> &u, const std::string &str) {
    return !(u == str);
}

template<typename T>
bool operator!=(const std::string &str, const NVector<T> &u) {
    return u != str;
}

template<typename T>
bool operator!=(const NVector<T> &u, T s) { return !(u == s); }

// STATIC METHODS

template<typename T>
NVector<T> NVector<T>::zeros(ul_t dim) {
    return scalar(0, dim);
}

template<typename T>
NVector<T> NVector<T>::ones(ul_t dim) {
    return scalar(1, dim);
}

template<typename T>
NVector<T> NVector<T>::scalar(T s, ul_t dim) {
    NVector<T> scalar(dim);
    scalar.fill(s);
    return scalar;
}

template<typename T>
NVector<T> NVector<T>::canonical(ul_t k, ul_t dim) {
    assert(k < dim);

    NVector<T> canonical = NVector<T>::zeros(dim);
    canonical(k) = 1.0;
    return canonical;
}

template<typename T>
NVector<T> NVector<T>::sum(const std::vector<NVector> &vectors) {
    NVector<T> sum = NVector<T>::zeros(vectors[0].dim());

    for (const auto &vector : vectors) {
        sum += vector;
    }
    return sum;
}

template<typename T>
NVector<T> NVector<T>::sumProd(const std::vector<T> &scalars, const std::vector<NVector> &vectors) {
    NVector<T> sum_prod = NVector<T>::zeros(vectors[0].dim());

    assert(scalars.size() == vectors.size());

    for (ul_t k = 0; k < scalars.size(); ++k) {
        sum_prod += scalars[k] * vectors[k];
    }
    return sum_prod;
}

// PROTECTED METHODS

// VECTOR SPACE METHODS

template<typename T>
NVector<T> &NVector<T>::add(const NVector<T> &u) {
    return forEach(u, [](T x, T y) { return x + y; });
}

template<typename T>
NVector<T> &NVector<T>::sub(const NVector<T> &u) {
    return forEach(u, [](T x, T y) { return x - y; });
}

template<typename T>
NVector<T> &NVector<T>::opp() {
    return prod(-1);
}

template<typename T>
NVector<T> &NVector<T>::prod(T s) {
    return forEach(s, [](T x, T s) { return x * s; });
}

template<typename T>
NVector<T> &NVector<T>::div(T s) {
    return forEach(s, [](T x, T s) { return x / s; });
}

// EUCLIDEAN SPACE OPERATIONS

template<typename T>
T NVector<T>::dotProduct(const NVector<T> &u) const {
    T dot = 0.0;

    assert(hasSameSize(u));
    for (ul_t k = 0; k <= _k2 - _k1; ++k) {
        dot += u[k + u._k1] * (*this)[k + _k1];
    }
    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
    return dot;
}

template<typename T>
T NVector<T>::norm() const {
    return sqrt(dotProduct(*this));
}

template<typename T>
T NVector<T>::distance(const NVector<T> &u) const {
    T d = (*this - u).norm();

    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();

    return d;
}

// MANIPULATORS


template<typename T>
NVector<T> &NVector<T>::forEach(const NVector<T> &u, std::function<T(T, T)> binaryOp) {
    assert(hasSameSize(u));
    for (ul_t k = 0; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] = binaryOp((*this)[k + _k1], u[k + u._k1]);
    }
    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
    return *this;
}

template<typename T>
NVector<T> &NVector<T>::forEach(T s, std::function<T(T, T)> binaryOp) {
    for (ul_t k = 0; k <= _k2 - _k1; k++) {
        (*this)[k + _k1] = binaryOp((*this)[k + _k1], s);
    }
    setDefaultBrowseIndices();
    return *this;
}

//CHARACTERIZATION

template<typename T>
bool NVector<T>::isValidIndex(ul_t k) const {
    return k < this->size();
}

template<typename T>
bool NVector<T>::isNull() const {
    return norm() <= EPSILON;
}

template<typename T>
bool NVector<T>::isEqual(const NVector<T> &u) const {
    if (!hasSameSize(u))
        return false;
    return distance(u) <= EPSILON;
}

template<typename T>
bool NVector<T>::isBetweenK12(ul_t k) const {
    return k >= _k1 && k <= _k2;
}

template<typename T>
bool NVector<T>::hasSameSize(const NVector<T> &u) const {
    return _k2 - _k1 == u._k2 - u._k1;
}

template<typename T>
bool NVector<T>::hasDefaultBrowseIndices() const {
    return _k1 == 0 && (_k2 == this->size() - 1 || _k2 == 0);
}

template<typename T>
void NVector<T>::setDefaultBrowseIndices() const {
    _k1 = 0;
    _k2 = (!this->empty()) ? this->size() - 1 : 0;
}

// AFFECTATION

template<typename T>
NVector<T> &NVector<T>::copy(const NVector<T> &u) {
    if (this != &u && u.size() > 0) {
        if (hasDefaultBrowseIndices() && u.hasDefaultBrowseIndices()) {
            this->std::vector<T>::operator=(u);
        } else if (hasDefaultBrowseIndices()) {
            this->std::vector<T>::operator=(u.subVector(u._k1, u._k2));
        } else {
            setSubVector(u);
        }
        setDefaultBrowseIndices();
        u.setDefaultBrowseIndices();
    }
    return *this;
}

// SUB-VECTORS

template<typename T>
NVector<T> NVector<T>::subVector(ul_t k1, ul_t k2) const {
    _k1 = k1;
    _k2 = k2;
    ul_t dim = k2 - k1 + 1;

    assert(isValidIndex(k1) && isValidIndex(k2) && dim > 0);

    vector<T> data(dim);
    std::copy(begin(), end(), data.begin());
    setDefaultBrowseIndices();

    return data;
}

template<typename T>
void NVector<T>::setSubVector(const NVector<T> &u) {

    assert(hasSameSize(u));

    std::copy(u.begin() + u._k1, u.begin() + u._k2 + 1, this->begin() + _k1);

    setDefaultBrowseIndices();
    u.setDefaultBrowseIndices();
}


template
class NVector<double>;

template
class NVector<char>;

template
class NVector<uc_t>;

template
class NVector<i_t>;

template
class NVector<AESByte>;

template
class NVector<Pixel>;


#pragma clang diagnostic pop