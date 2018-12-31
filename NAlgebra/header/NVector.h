/**
 * @class   NVector
 * @date    03/05/2018
 * @author  samiBendou
 *
 * @details A NVector<T> object stores the coordinates of a finite dimension vector x in an arbitrary base.
 *          Theses are stored in the form [x0, x1, ..., x(n-1)]. where [...] is a std::vector<T>,
 *          n is the dimension and (x0, x1, ..., x(n-1)) are the coordinates.
 *          We will be using the following definitions :
 *              - x/u : this vector.
 *              - s : a scalar (T)
 *
 *          This object is the base object of every other object in NAlgebra module.
 *          It inherits from std::vector<T> so it's kind of memory
 *          support for every object in NAlgebra module.
 *
 *          Featuring algebraical operations (E, +, *), swaps, shifts and
 *          classic vectors generator such as ones, zeros...
 *
 * @license Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_VECTOR_H
#define MATHTOOLKIT_VECTOR_H

#include "thirdparty.h"

#define MAX_SIZE 4294967295
#define EPSILON (std::numeric_limits<T>::epsilon())


template<typename T>


class NVector : public std::vector<T> {

    typedef typename std::vector<T>::iterator iterator;

    typedef typename std::vector<T>::const_iterator const_iterator;


public:

    // CONSTRUCTORS

    /**
     *
     * @return a NVector<T> with an array of data. The dimension is the size of the array.
     */
    NVector(const std::vector<T> &data) : NVector(data, 0, 0) {}

    NVector(std::initializer_list<T> list) : NVector(list, 0, 0) {}
    /**
     *
     * @return  a NVector<T> by giving the dimension. This method uses the std::vector constructor
     *          to create a vector.
     */
    explicit NVector(ul_t dim = 0) : NVector(std::vector<T>(dim), 0, 0) {}

    NVector(const NVector<T> &u) : NVector(0) { copy(u); }

    // SERIALIZATION

    /**
     *
     * @return a string representing the coordinates of the vector in the format "[x0, x1, ..., x(n-1)]".
     * xi is formatted with exponential notation with 2 decimals.
     */
    virtual std::string str() const;

    // GETTERS

    /**
     *
     * @return n, the dimension of the vector which is the size of this std::vector instance.
     */
    ul_t dim() const;

    /**
     *
     * @return an std::vector representing the base object of this instance of NVector.
     */
    std::vector<T> array() const;

    // MAX / MIN

    /**
     *
     * @return Respectively max and min of the coordinates of the vector (x0, x1, .. x(n-1)).
     */
    T max() const;

    T min() const;

    /**
     *
     * @return Respectively the index of max and min of the coordinates of vector (x0, x1, .. x(n-1)).
     */
    ul_t maxIndex() const;

    ul_t minIndex() const;

    // ABSOLUTE VALUE MAX / MIN

    /**
     *
     * @return Respectively min and max of absolute value of vector ie. (|x0|, |x1|, ..., |x(n-1)|)
     */
    T maxAbs() const;

    T minAbs() const;


    /**
     *
     * @return Respectively index of min and max of absolute value of vector ie. (|x0|, |x1|, ..., |x(n-1)|)
     */
    ul_t maxAbsIndex() const;

    ul_t minAbsIndex() const;

    // MANIPULATORS

    /**
     *
     * @param k1 First index to swap
     * @param k2 Second index to swap
     * @details Permutation of two elements (x(k1 - 1), xk2, ..., x(k2 - 1), xk1, ..., x(n-1))
     */
    NVector<T> &swap(ul_t k1, ul_t k2);

    /**
     *
     * @param iterations :  number of times to shift. If iterations is > 0, shift is powered to the left,
     *                      else to the right.
     * @details : Shifts vector iterations times. ie. with iterations = 2 : (x2, x3, ..., x(n-1), x0, x1).
     */
    NVector<T> &shift(long iterations);

    /**
     *
     * @param s : value to fill the vector with
     * @details : Fill vector with a scalar : ie. with scalar = 3, (3, 3, 3, ..., 3).
     */
    NVector<T> &fill(T s);

    // OPERATORS

    // ALGEBRAICAL OPERATORS

    /**
     * @return result of u + v where + is the usual addition (u0 + v0, u1 + v1, ...).
     */
    inline friend NVector<T> operator+(NVector<T> u, const NVector<T> &v) {
        u += v;
        return u;
    }


    /**
     * @return return u - v where - is difference based on usual addition.
     */
    inline friend NVector<T> operator-(NVector<T> u, const NVector<T> &v) {
        u -= v;
        return u;
    }


    /**
     * @return opposite of u (-u0, -u1, ...).
     */
    inline friend NVector<T> operator-(NVector<T> u) {
        u.opp();
        return u;
    }

    /**
     * @return s * u where * is usual scalar multiplication (s * u0, s * u1, ...).
     */
    inline friend NVector<T> operator*(T s, NVector<T> u) {
        u *= s;
        return u;
    }

    inline friend NVector<T> operator*(const NVector<T> &u, T s) {
        return s * u;
    }

    /**
     * @return return (1 / s) * u where * is the usual scalar multiplication (s * u0, s * u1, ...).
     */
    inline friend NVector<T> operator/(NVector<T> u, T s) {
        u /= s;
        return u;
    }

    // SCALAR PRODUCT BASED OPERATIONS

    /**
     *
     * @return u * v where * is usual dot product u0 * v0 + u1 * v1 + ... + u(n-1) * v(n-1)
     */

    inline friend T operator|(const NVector<T> &u, const NVector<T> &v) {
        return u.dotProduct(v);
    }

    /**
     *
     * @return the norm of vector ||.|| dervied from dot product.
     */

    inline friend T operator!(const NVector<T> &u) {
        return u.norm();
    }

    /**
     *
     * @return distance between u & v, ||u - v||.
     */

    inline friend T operator/(const NVector<T> &u, const NVector<T> &v) {
        return u.distance(v);
    }


    // COMPOUND OPERATORS


    inline NVector<T> &operator+=(const NVector<T> &u) {
        return add(u);
    }

    inline NVector<T> &operator-=(const NVector<T> &u) {
        return sub(u);
    }

    inline virtual NVector<T> &operator*=(T s) {
        return prod(s);
    }

    inline virtual NVector<T> &operator/=(T s) {
        return div(s);
    }


    // ACCES OPERATOR


    /**
     *
     * @param k : index of the coordinate. Between -(dim() - 1) and dim() - 1
     * @return  the kth coordinate of the vector xk if k < 0, returns x(n - 1 - k).
     *          Operator can be used to read/write values.
     */
    T &operator()(long k);

    inline T operator()(long k) const;

    /**
     *
     * @param k1 : start index for sub-range.
     * @param k2 : end index for sub-range.
     * @return  a sub vector in representing coordinates from k1 to k2, (xk1, x(k1+1), ...,xk2).
     *
     *          - 0 <= |k1| <= |k2| <= dim() - 1.
     *
     *          - Operator can be used to read/write values.
     *
     *          - Allows operations such as u(0, 1) + v(1, 2) or u(1, 4).max(), ...
     *
     *          - Const version returns a sub-vector.
     *
     *          - See unit tests for more details.
     */
    inline NVector<T> operator()(ul_t k1, ul_t k2) const {
        return subVector(k1, k2);
    }

    NVector<T> &operator()(ul_t k1, ul_t k2);


    // STREAM EXTRACT/INSERT

    friend std::ostream &operator<<(std::ostream &os, const NVector<T> &vector) {
        os << vector.str();
        return os;
    }


    // AFFECTATION

    /**
     *
     * @param u source NVector<T> object
     * @return reference to this.
     * @details Copy source object on this object using copy().
     */
    NVector<T> &operator=(const NVector<T> &u) {
        return copy(u);
    }

    // NORM BASED COMPARISON OPERATORS

    /**
     *
     * @return return true if ||u - v|| < epsilon.
     */

    friend bool operator==(const NVector<T> &u, const NVector<T> &v) {
        bool result = u.isEqual(v);
        return result;
    }

    /**
     *
     * @return true if s is 0 and u is null vector.
     */
    friend bool operator==(const NVector<T> &u, T s) {
        bool res = s < EPSILON && u.isNull();
        u.setDefaultBrowseIndices();
        return res;
    }

    /**
     *
     * @return return true if ||v1 - v2|| >= epsilon.
     */
    inline friend bool operator!=(const NVector<T> &u, const NVector<T> &v) { return !(u == v); }

    inline friend bool operator!=(const NVector<T> &u, const std::string &str) { return !(u == str); }

    inline friend bool operator!=(const std::string &str, const NVector<T> &u) { return u != str; }

    inline friend bool operator!=(const NVector<T> &u, T s) { return !(u == s); }

    // ITERATORS

    inline iterator begin() {
        return this->std::vector<T>::begin() + _k1;
    };

    inline const_iterator begin() const {
        return this->std::vector<T>::begin() + _k1;
    };

    inline iterator end() {
        return this->std::vector<T>::begin() + _k2 + 1;
    };

    inline const_iterator end() const {
        return this->std::vector<T>::begin() + _k2 + 1;
    };

    // STATIC FUNCTIONS

    /**
     *
     * @param dim : dimension of the vector
     * @return a 0 vector (0, 0, ..., 0).
     */
    inline static NVector<T> zeros(ul_t dim) {
        return scalar(0, dim);
    }

    /**
     *
     * @param dim : dimension of the vector
     * @return Returns vector filled with 1 (1, 1, ..., 1).
     */
    inline static NVector<T> ones(ul_t dim) {
        return scalar(1, dim);
    }

    /**
     *
     * @param s : value of the scalar vector
     * @param dim dimension of the scalar vector
     * @return a vector filled with s (s, s, ..., s).
     */
    static NVector<T> scalar(T s, ul_t dim);

    /**
     *
     * @param k : index of vector in base
     * @param dim : dimension of vector space represented by the base.
     * @return  return the kth vector of canonical base. ie (e0, e1, ..., e(n-1)) where :
     *          e0 = (1, 0, ..., 0), e1 = (0, 1, 0, ..., 0), ..., e(n - 1) = (0, 0, ..., 1).
     */
    static NVector<T> canonical(ul_t k, ul_t dim);

    /**
     *
     * @param vectors : an array of vectors [u0, u1, ..., u(r-1)] where r is the size of the array
     * @return the sum of the vectors : u0 + u1 + ... + u(r-1). where + is usual addition
     */
    static NVector<T> sum(const std::vector<NVector> &vectors);

    /**
     *
     * @param scalars : coefficients of linear combination [s0, s1, ..., s(r-1)] where r is the size of the array
     * @param vectors : vectors of linear combination (u0, u1, ..., u(r-1))
     * @return  the linear combination s0 * u0 + s1 * u1 + ... + s(r-1) * u(r-1). where + and * are
     *          usual addition and scalar multiplication.
     */
    static NVector<T> sumProd(const std::vector<T> &scalars, const std::vector<NVector> &vectors);

protected:

    explicit NVector(const std::vector<T> data, ul_t k1, ul_t k2);

    // VECTOR SPACE OPERATIONS

    inline NVector<T> &add(const NVector<T> &u) {
        return forEach(u, [](T x, T y) { return x + y; });
    }

    inline NVector<T> &sub(const NVector<T> &u) {
        return forEach(u, [](T x, T y) { return x - y; });
    }

    inline NVector<T> &opp() {
        return prod(-1);
    }

    inline NVector<T> &prod(T s) {
        return forEach(s, [](T x, T s) { return x * s; });
    }

    inline NVector<T> &div(T s) {
        return forEach(s, [](T x, T s) { return x / s; });
    }

    // EUCLIDEAN SPACE OPERATIONS

    T dotProduct(const NVector<T> &u) const;

    T norm() const {
        return sqrt(dotProduct(*this));
    }

    T distance(const NVector<T> &u) const;

    //CHARACTERIZATION

    inline bool isValidIndex(ul_t k) const {
        return k < this->size();
    }

    inline bool isBetweenK12(ul_t k) const {
        return k >= _k1 && k <= _k2;
    }

    inline bool isNull() const {
        return norm() <= EPSILON;

    }

    bool isEqual(const NVector<T> &u) const;


    inline bool hasSameSize(const NVector<T> &u) const {
        return _k2 - _k1 == u._k2 - u._k1;
    }

    inline virtual bool hasDefaultBrowseIndices() const {
        return _k1 == 0 && (_k2 == this->size() - 1 || _k2 == 0);
    }

    inline virtual void setDefaultBrowseIndices() const {
        _k1 = 0;
        _k2 = (!this->empty()) ? this->size() - 1 : 0;
    }

    // MANIPULATORS

    NVector<T> &forEach(const NVector<T> &u, std::function<T(T, T)> binaryOp);

    NVector<T> &forEach(T s, std::function<T(T, T)> binaryOp);


    // AFFECTATION

    NVector<T> &copy(const NVector<T> &u);

    //SUB-VECTORS

    NVector<T> subVector(ul_t k1, ul_t k2) const;

    void setSubVector(const NVector<T> &u);

    //BROWSE INDICES

    mutable ul_t _k1;

    mutable ul_t _k2;
};

typedef NVector<double> vec_t;
typedef NVector<char> vec_char_t;
typedef NVector<AESByte> vec_aes_t;
typedef NVector<Pixel> vec_pix_t;

#endif //MATHTOOLKIT_VECTOR_H
