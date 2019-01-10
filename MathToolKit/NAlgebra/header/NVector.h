#ifndef MATHTOOLKIT_VECTOR_H
#define MATHTOOLKIT_VECTOR_H

#include "thirdparty.h"

#define MAX_SIZE 4294967295
#define EPSILON (std::numeric_limits<T>::epsilon())

/**
 * @ingroup NAlgebra
 * @{
 * @class   NVector
 * @copyright Dahoux Sami 2018 All rights reserved.
 * @date    03/05/2018
 * @author  samiBendou
 *
 * @brief   A `NVector<T>` object represents the coordinates of a finite dimension dense vector \f$ x \f$.
 *
 * @details Coordinates are stored in the form `[` \f$ x_0, x_1, ..., x_{(n-1)} \f$ `]`. where `[...]` is a `std::vector<T>`,
 *          \f$ n \f$ is the dimension and \f$ (x_0, x_1, ..., x_{(n-1)}) \f$ are the coordinates.
 *
 *          This object inherits from `std::vector<T>`, it is a STL container, iterators and STL library functions can be
 *          used.
 *
 *          @section Features
 *
 *          Featuring algebraical operations \f$ (E, +, *) \f$, swaps, shifts and
 *          classic vectors generator such as ones, zeros...
 *
 *          @subsection FuncOpVec Sub-range operators
 *
 *          The `NVector` class provides a function operator which behaves like a classic array subscript operator
 *          of `std::vector` except that it comes on two version detailed further in the documentation.
 *          It allows operations on sub-ranges.
 *
 *          @section Definitions
 *          We will often refer to the following variables in this page :
 *              - `x`/`u`/`v` : An arbitrary given NVector. By default, \f$ x \f$ denotes `this` vector
 *              - `n`/`dim` : Size of this vector, can be seen as the dimension of the underlying vector space
 *              - `s` : a scalar of type `T`
 *              - `k` : index of vector \f$ u_k \f$
 *              - \f$ |.| \f$ : Absolute value, if meaningfull with scalar type `T`
 *
 */


template<typename T>


class NVector : public std::vector<T> {

    typedef typename std::vector<T>::iterator iterator;

    typedef typename std::vector<T>::const_iterator const_iterator;


public:

    /**
     * @param data `std::vector` source.
     * @brief Construct a vector using a `std::vector`. \f$ x_k \f$ represents `data[k]`.
     */
    NVector(const std::vector<T> &data) : NVector(data, 0, 0) {}

    /**
     * @param list `std::initializer_list` source.
     * @brief Construct a vector using an initializer list `{}`.
     * @details Convert `list` and uses @ref NVector(const std::vector<T> &data) "array constructor".
     */
    NVector(std::initializer_list<T> list) : NVector(std::vector<T>(list)) {}

    /**
     * @param dim vector size
     * @brief Construct a vector of a given size.
     */
    explicit NVector(size_t dim = 0) : NVector(std::vector<T>((size_t) dim), 0, 0) {}

    /**
     *
     * @param u `NVector` source.
     * @brief Construct a vector by using `copy()` method.
     */
    NVector(const NVector<T> &u) : NVector(0) { copy(u); }

    // SERIALIZATION

    /**
     * @brief Creates a string representing the vector.
     *
     * @details The returned string has the following form :
     *
     *  ```commandline
     *  "(x(0), x(1), ..., x((n-1)))"
     *  ```
     * Each `x(k)` is formatted using the default `<<` operator of the type `T`.
     *
     * @return Returns a string representing the vector.
     */
    virtual std::string str() const;

    /**
     * @brief Dimension of the vector.
     * @return \f$ dim \f$
     */
    size_t dim() const;

    /**
     * @brief Creates an array with `this` vector.
     * @return a `std::vector` representing `this`.
     */
    std::vector<T> array() const;

    /**
     *
     * @name Extremums
     * @brief Methods related to maximum minimum value research. They all use `std::max` or `std::min`.
     * @{
     */

    /**
     *
     * @brief Maximum of the coordinates of the vector \f$ (x_0, x_1, .. x_{(n-1)}) \f$.
     * @return value of maximum
     */
    T max() const;

    /**
     *
     * @brief Minimum of the coordinates of the vector \f$ (x_0, x_1, .. x_{(n-1)}) \f$.
     * @return value of minimum
     */
    T min() const;

    /**
     *
     * @brief Index of maximum of the coordinates of vector \f$ (x_0, x_1, ..., x_{(n-1)}) \f$.
     * @return index of maximum
     */
    size_t maxIndex() const;

    /**
     *
     * @brief Index of minimum of the coordinates of vector \f$ (x_0, x_1, ..., x_{(n-1)}) \f$.
     * @return index of minimum
     */
    size_t minIndex() const;

    /**
     *
     * @brief Maximum of the coordinates of the vector  \f$ (|x_0|, |x_1|, ..., |x_{(n-1)}|) \f$.
     * @return absolute value of absolute maximum
     */
    T maxAbs() const;

    /**
     *
     * @brief Minimum of the coordinates of the vector  \f$ (|x_0|, |x_1|, ..., |x_{(n-1)}|) \f$.
     * @return absolute value of absolute minimum
     */
    T minAbs() const;

    /**
     *
     * @brief Index of maximum of the coordinates of vector \f$ (|x_0|, |x_1|, ..., |x_{(n-1)}|) \f$.
     * @return index of absolute maximum
     */
    size_t maxAbsIndex() const;

    /**
     *
     * @brief Index of minimum of the coordinates of vector \f$ (|x_0|, |x_1|, ..., |x_{(n-1)}|) \f$.
     * @return index of absolute minimum
     */
    size_t minAbsIndex() const;

    /** @} */

    /**
     * @name Manipulators
     * @brief Manipulators such as swap, shift...
     * @details All the manipulator return a reference to `*this` in order to allow cascade calls eg `swap().shift()`.
     * @{
     */

    /**
     *
     * @param k1 First index to swap
     * @param k2 Second index to swap
     * @brief Permutation of two elements.
     * @details The vector is set to \f$ (x_0, ..., x_{(k_1 - 1)}, x_{k_2}, ..., x_{(k_2 - 1)}, x_{k_1}, ..., x_{(n-1)}) \f$.
     * \f$ x_{k_1} \f$ and \f$ x_{k_2} \f$ have been swaped used `std::swap`.
     */
    NVector<T> &swap(size_t k1, size_t k2);

    /**
     *
     * @param iterations number of times to shift.
     * @brief Shifts `this` vector `iterations` times.
     * @details If iterations is positive, shift is powered to the left, else to the right.
     * For example `shift(2)` will set \f$ (x_2, x_3, ..., x_{(n-1)}, x_0, x_1) \f$.
     */
    NVector<T> &shift(long iterations);

    /**
     *
     * @param s value to fill the vector with
     * @brief Fill vector with a scalar. For example `fill(3)` will set \f$ (3, 3, 3, ..., 3) \f$.
     */
    NVector<T> &fill(T s);

    /** @} */

    /**
     * @name Algebra
     * @brief Vector algebraical operations.
     * @details Represent euclidean vector space operations such as sum, inner product, distance...
     * @{
     */

    /**
     * @brief Add two vectors.
     * @details Using usual addition \f$ (u_0 + v_0, u_1 + v_1, ...) \f$.
     * @return value of \f$ u + v \f$
     */
    inline friend NVector<T> operator+(NVector<T> u, const NVector<T> &v) {
        u += v;
        return u;
    }

    /**
     * @brief Substract two vectors.
     * @details Using usual difference \f$ (u_0 - v_0, u_1 - v_1, ...) \f$.
     * @return value of \f$ u - v \f$
     */
    inline friend NVector<T> operator-(NVector<T> u, const NVector<T> &v) {
        u -= v;
        return u;
    }

    /**
     * @brief Opposite of vector.
     * @return value of \f$ (-u_0, -u_1, ...). \f$
     */
    inline friend NVector<T> operator-(NVector<T> u) {
        u.opp();
        return u;
    }

    /**
     * @brief Multiply vector by scalar.
     * @details Using usual scalar multiplication difference \f$ (s \cdot u_0, s \cdot u_1, ...) \f$.
     * @return value of \f$ s \cdot u \f$
     */
    inline friend NVector<T> operator*(T s, NVector<T> u) {
        u *= s;
        return u;
    }

    inline friend NVector<T> operator*(const NVector<T> &u, T s) {
        return s * u;
    }

    /**
     * @brief Divide vector by scalar.
     * @details Usual scalar division based on multiplication.
     * @return value of \f$ s^{-1} \cdot u \f$
     */
    inline friend NVector<T> operator/(NVector<T> u, T s) {
        u /= s;
        return u;
    }

    /**
     * @brief Dot product of two vectors.
     * @details Usual inner product \f$ u_0 \cdot v_0 + u_1 \cdot v_1 + ... + u_{(n-1)} \cdot v_{(n-1)} \f$.
     * @return value of \f$ u \cdot v \f$
     */
    inline friend T operator|(const NVector<T> &u, const NVector<T> &v) { return u.dotProduct(v); }

    /**
     * @brief Norm of the vector.
     * @details The norm of vector \f$ ||u|| = \sqrt{u \cdot u} \f$ derived from dot product.
     * @return value of \f$ ||u|| \f$.
     */
    inline friend T operator!(const NVector<T> &u) { return u.norm(); }

    /**
     * @brief Distance between two vectors.
     * @return value of \f$ ||u - v|| \f$.
     */
    inline friend T operator/(const NVector<T> &u, const NVector<T> &v) { return u.distance(v); }


    /** @} */

    inline NVector<T> &operator+=(const NVector<T> &u) { return add(u); }

    inline NVector<T> &operator-=(const NVector<T> &u) { return sub(u); }

    inline virtual NVector<T> &operator*=(T s) { return prod(s); }

    inline virtual NVector<T> &operator/=(T s) { return div(s); }


    /**
     * @name Function Operator
     * @brief Access to components and sub-matrix
     * @details C++ function operator are here used to give intuitive access to the vector. It behaves like numpy `[:]`.
     *
     */

    /**
     * @brief Simple access operator
     * @details Access operator equivalent to `[k]` on `std::vector`.
     * Operator can be used to read or write values. `const` version returns `const` reference to the element.
     * For example, `x(-1)` returns the last element, `x(0)` returns the first element.
     * @return component \f$ x_{k} \f$ of the vector.
     * @{
     */
    T &operator()(long k);

    T operator()(long k) const;

    /**
     *
     * @param k1 first element to take
     * @param k2 last element to take \f$ n \gt k_2 \geq k_1 \geq 0 \f$
     * @brief Manipulate sub-vector.
     *
     * @details Allows operations on a restricted range of the vector \f$ (x_{k_1}, x_{(k_1+1)}, ...,x_{k_2}) \f$ .
     *          The two arguments function operator has the following behavior :
     *          - It can be used to read/write values.
     *
     *          - It Allows chaining operations : `u(0, 1) + v(1, 2)`, `x(1, 4).max()`, ...
     *
     *          Most of methods or operators can be chained. It will be explicitly specified if it's not the case.
     *          For example `x(1, 3)` will return the value of \f$ (x_1, x_2, x_3) \f$.
     *
     * @return value of the sub-vector.
     *
     *
     */
    inline NVector<T> operator()(size_t k1, size_t k2) const { return subVector(k1, k2); }

    /**
     *
     * @brief Manipulate sub-vector
     * @details This operator is similar to previous @ref operator()(size_t, size_t) const "operator"
     * except that it sets browse indices `_k1` and `_k2` in order to modify efficiently non `const` reference.
     * @return reference to `*this`.
     */
    NVector<T> &operator()(size_t k1, size_t k2);

    /** @} */


    // STREAM EXTRACT/INSERT

    /**
     *
     * @param os output stream
     * @param u vector source
     * @brief Usual stream insertion of vector.
     * @details Inserts `u.str()` into `os` stream.
     * @return reference to `os`.
     */
    friend std::ostream &operator<<(std::ostream &os, const NVector<T> &u) {
        os << u.str();
        return os;
    }


    // AFFECTATION

    /**
     *
     * @param u source `NVector<T>` object
     * @brief Copy source object on this object using `copy()`.
     * @return reference to `this`.
     */
    inline NVector<T> &operator=(const NVector<T> &u) { return copy(u); }

    // NORM BASED COMPARISON OPERATORS


    /**
     * @name Comparaison
     * @brief Norm based comparaison between two vectors.
     * @{
     */

    /**
     * @brief Equality of two vectors.
     * @return return true if \f$ ||u - v|| < \epsilon \f$.
     */
    friend bool operator==(const NVector<T> &u, const NVector<T> &v) {
        bool result = u.isEqual(v);
        return result;
    }

    /**
     * @brief Equality to zero.
     * @return true if `s` is 0 and \f$ u \lt \epsilon \f$.
     */
    friend bool operator==(const NVector<T> &u, T s) {
        bool res = s < EPSILON && u.isNull();
        u.setDefaultBrowseIndices();
        return res;
    }

    inline friend bool operator==(T s, const NVector<T> &u) { return u == s; }

    /**
     * @brief Non equality of two vector.
     * @return return true if \f$ ||u - v|| \geq \epsilon \f$.
     */
    inline friend bool operator!=(const NVector<T> &u, const NVector<T> &v) { return !(u == v); }

    inline friend bool operator!=(const NVector<T> &u, T s) { return !(u == s); }

    inline friend bool operator!=(T s, const NVector<T> &u) { return !(u == s); }

    /** @} */

    // ITERATORS

    /**
     * @name Iterators
     * @brief Similar iterators as `std::vector` except that they allow use of `operator()()`.
     * @{
     */
    inline iterator begin() { return this->std::vector<T>::begin() + _k1; };

    inline const_iterator begin() const { return this->std::vector<T>::begin() + _k1; };

    inline iterator end() { return this->std::vector<T>::begin() + _k2 + 1; };

    inline const_iterator end() const { return this->std::vector<T>::begin() + _k2 + 1; };

    /** @} */

    // STATIC FUNCTIONS

    /**
     *
     * @param dim dimension of the vector
     * @return a `0` vector \f$ (0, 0, ..., 0) \f$.
     */
    inline static NVector<T> zeros(size_t dim) { return scalar(0, dim); }

    /**
     *
     * @param dim dimension of the vector
     * @return Returns vector filled with `1` \f$ (1, 1, ..., 1) \f$.
     */
    inline static NVector<T> ones(size_t dim) { return scalar(1, dim); }

    /**
     *
     * @param s value of the scalar vector
     * @param dim dimension of the scalar vector
     * @return a vector filled with `s` \f$ (s, s, ..., s) \f$.
     */
    static NVector<T> scalar(T s, size_t dim);

    /**
     *
     * @param k index of vector in base
     * @param dim dimension of vector space represented by the base.
     * @return  return the kth vector of canonical base. ie \f$ (e_{0}, e_{1}, ..., e_{(n-1)}) \f$ where :
     *
     *          \f[
     *          \begin{align*}
     *              & e_{0}         &=& (1, 0, 0, ..., 0) \\
     *              & e_{1}         &=& (0, 1, 0, ..., 0) \\
     *              &               &\vdots & \\
     *              &e_{(n - 1)}    &=& (0, 0, 0, ..., 1) \\
     *          \end{align*}
     *          \f]
     */
    static NVector<T> cano(size_t k, size_t dim);

    /**
     *
     * @param vectors an array of vectors \f$ (u, v, ..., x) \f$.
     * @brief Sum of multiples vectors.
     * @details Sum of the vectors contained in `vectors` array.
     * @return \f$ u + v + ... + x \f$.
     */
    static NVector<T> sum(const std::vector<NVector> &vectors);

    /**
     *
     * @param scalars coefficients of linear combination `[` \f$ \alpha,  \beta, ..., \lambda \f$`]`.
     * @param vectors vectors of linear combination \f$ (u, v, ..., x) \f$
     * @brief Linear combination of `scalars` and `vectors`.
     * @return  \f$ \alpha u + \beta v + ... + \lambda x \f$.
     */
    static NVector<T> sumProd(const std::vector<T> &scalars, const std::vector<NVector> &vectors);

protected:

    explicit NVector(const std::vector<T> &data, size_t k1, size_t k2);

    // VECTOR SPACE OPERATIONS

    inline NVector<T> &add(const NVector<T> &u) { return forEach(u, [](T &x, const T &y) { x += y; }); }

    inline NVector<T> &sub(const NVector<T> &u) { return forEach(u, [](T &x, const T &y) { x -= y; }); }

    inline virtual NVector<T> &opp() { return prod(-1); }

    inline virtual NVector<T> &prod(T s) { return forEach(s, [](T &x, T t) { return x *= t; }); }

    inline virtual NVector<T> &div(T s) { return forEach(s, [](T &x, T t) { return x /= t; }); }

    // EUCLIDEAN SPACE OPERATIONS

    T dotProduct(const NVector<T> &u) const;

    inline T norm() const { return sqrt(dotProduct(*this)); }

    inline T distance(const NVector<T> &u) const {
        T d = (*this - u).norm();
        setDefaultBrowseIndices();
        u.setDefaultBrowseIndices();
        return d;
    }

    //CHARACTERIZATION

    inline bool isValidIndex(size_t k) const { return k < this->size(); }

    inline bool isBetweenK12(size_t k) const { return k >= _k1 && k <= _k2; }

    inline bool isNull() const { return norm() <= EPSILON; }

    bool isEqual(const NVector<T> &u) const;


    inline bool hasSameSize(const NVector<T> &u) const { return _k2 - _k1 == u._k2 - u._k1; }

    inline virtual bool hasDefaultBrowseIndices() const { return _k1 == 0 && (_k2 == this->size() - 1 || _k2 == 0); }

    inline virtual void setDefaultBrowseIndices() const {
        _k1 = 0;
        _k2 = (!this->empty()) ? this->size() - 1 : 0;
    }

    // MANIPULATORS

    NVector<T> &forEach(const NVector<T> &u, const std::function<void(T &, const T &)> &binary_op);

    virtual NVector<T> &forEach(T s, const std::function<void(T &, T)> &binary_op);


    // AFFECTATION

    NVector<T> &copy(const NVector<T> &u);

    //SUB-VECTORS

    NVector<T> subVector(size_t k1, size_t k2) const;

    void setSubVector(const NVector<T> &u);

    //BROWSE INDICES

    mutable size_t _k1{};

    mutable size_t _k2{};
};

template <>
inline double_t NVector<double_t>::norm() const { return std::sqrt(dotProduct(*this)); }

/** @} */

/**
 * @ingroup NAlgebra
 * @{
 * Real numerical vector
 */
typedef NVector<double_t> vec_t;

/**
 * `char` vector
 */
typedef NVector<char> vec_char_t;

/**
 * AES vector. See `AESByte` for more details.
 */
typedef NVector<AESByte> vec_aes_t;

/**
 * Pixel vector. See `Pixel` for more details.
 */
typedef NVector<Pixel> vec_pix_t;

/** @} */

#endif //MATHTOOLKIT_VECTOR_H
