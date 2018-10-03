/**
 * @class   NVector
 * @date    03/05/2018
 * @author  samiBendou
 *
 * @details A NVector object stores the coordinates of a finite dimension vector x in an arbitrary base.
 *          Theses are stored in the form [x0, x1, ..., x(n-1)]. where [...] is a std::vector<double>,
 *          n is the dimension and (x0, x1, ..., x(n-1)) are the coordinates.
 *          We will be using the following definitions :
 *              - x/u : this vector.
 *              - s : a scalar (double)
 *
 *          Representation of a finite dimension vector space. This object is the base object of every
 *          other object in NAlgebra module. It inherits from std::vector<double> so it's kind of memory
 *          support for every object in NAlgebra module.
 *
 *          Featuring algebraical operations (E, +, *), swaps, shifts and
 *          classic vectors generator such as ones, zeros...
 *
 * @license Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_VECTOR_H
#define MATHTOOLKIT_VECTOR_H

#define MAX_SIZE 4294967295

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdarg>
#include <cassert>

class NVector : public std::vector<double> {

public:
    // CONSTRUCTORS

    /**
     *
     * @return a NVector with an array of data. The dimension is the size of the array.
     */
    NVector(const std::vector<double>& data);

    NVector(const NVector &u);
    /**
     *
     * @return  a NVector by giving the dimension. This method uses the std::vector constructor
     *          to create a vector.
     */
    explicit NVector(unsigned long dim = 0);

    /**
     *
     * @param   str a string containing the components of vector in the form "(0 1 2)".
     *          The character '(' and ')' can be replaced by any one. Don't use comma at all.
     */
    explicit NVector(const std::string& str);

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
    unsigned long dim() const;

    /**
     *
     * @return an std::vector representing the base object of this instance of NVector.
     */
    std::vector<double> array() const;

    // MAX / MIN

    /**
     *
     * @return Respectively max and min of the coordinates of the vector (x0, x1, .. x(n-1)).
     */
    double max() const;

    double min() const;

    /**
     *
     * @return Respectively the index of max and min of the coordinates of vector (x0, x1, .. x(n-1)).
     */
    unsigned long maxIndex() const;

    unsigned long minIndex() const;

    // ABSOLUTE VALUE MAX / MIN

    /**
     *
     * @return Respectively min and max of absolute value of vector ie. (|x0|, |x1|, ..., |x(n-1)|)
     */
    double maxAbs() const;

    double minAbs() const;


    /**
     *
     * @return Respectively index of min and max of absolute value of vector ie. (|x0|, |x1|, ..., |x(n-1)|)
     */
    unsigned long maxAbsIndex() const;

    unsigned long minAbsIndex() const;

    // MANIPULATORS

    /**
     *
     * @param k1 First index to swap
     * @param k2 Second index to swap
     * @details Permutation of two elements (x(k1 - 1), xk2, ..., x(k2 - 1), xk1, ..., x(n-1))
     */
    void swap(unsigned long k1, unsigned long k2);

    /**
     *
     * @param iterations :  number of times to shift. If iterations is > 0, shift is powered to the left,
     *                      else to the right.
     * @details : Shifts vector iterations times. ie. with iterations = 2 : (x2, x3, ..., x(n-1), x0, x1).
     */
    void shift(long iterations);

    /**
     *
     * @param s : value to fill the vector with
     * @details : Fill vector with a scalar : ie. with scalar = 3, (3, 3, 3, ..., 3).
     */
    void fill(double s);

    // OPERATORS

    // ALGEBRAICAL OPERATORS

    /**
     * @return result of u + v where + is the usual addition (u0 + v0, u1 + v1, ...).
     */
    NVector operator+(const NVector &u) const;


    /**
     * @return return u - v where - is difference based on usual addition.
     */
    NVector operator-(const NVector &u) const;


    /**
     * @return opposite of u (-u0, -u1, ...).
     */
    NVector operator-() const;

    /**
     * @return s * u where * is usual scalar multiplication (s * u0, s * u1, ...).
     */
    friend NVector operator*(double s, const NVector &u);

    friend NVector operator*(const NVector &u, double s);

    /**
     * @return return (1 / s) * u where * is the usual scalar multiplication (s * u0, s * u1, ...).
     */
    friend NVector operator/(const NVector &u, double s);

    // SCALAR PRODUCT BASED OPERATIONS

    /**
     *
     * @return u * v where * is usual dot product u0 * v0 + u1 * v1 + ... + u(n-1) * v(n-1)
     */
    friend double operator|(const NVector &u, const NVector &v);

    /**
     *
     * @return the norm of vector ||.|| dervied from dot product.
     */
    friend double operator!(const NVector& u);


    /**
     *
     * @return distance between u & v, ||u - v||.
     */
    friend double operator/(const NVector &u, const NVector &v);


    // COMPOUND OPERATORS


    NVector& operator+=(const NVector &u);

    NVector& operator-=(const NVector &u);

    virtual NVector& operator*=(double s);

    virtual NVector& operator/=(double s);


    // ACCES OPERATOR


    /**
     *
     * @param k : index of the coordinate. Between -(dim() - 1) and dim() - 1
     * @return  the kth coordinate of the vector xk if k < 0, returns x(n - 1 - k).
     *          Operator can be used to read/write values.
     */
    double& operator()(long k);

    double operator()(long k) const;

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
    NVector operator()(unsigned long k1, unsigned long k2) const;

    NVector& operator()(unsigned long k1, unsigned long k2);


    // STREAM EXTRACT/INSERT

    friend std::ostream& operator<<(std::ostream &os, const NVector &vector);


    // AFFECTATION

    /**
     *
     * @param u source NVector object
     * @return reference to this.
     * @details Copy source object on this object using copy().
     */
    NVector& operator=(const NVector& u);

    NVector& operator=(const std::string& str);

    // NORM BASED COMPARISON OPERATORS

    /**
     *
     * @return return true if ||u - v|| < epsilon.
     */

    friend bool operator==(const NVector& u, const NVector& v);

    friend bool operator==(const NVector& u, const std::string& str);

    friend bool operator==(const std::string& str, const NVector& u);

    /**
     *
     * @return true if s is 0 and u is null vector.
     */
    friend bool operator==(const NVector& u, double s);

    /**
     *
     * @return return true if ||v1 - v2|| >= epsilon.
     */
    friend bool operator!=(const NVector& u, const NVector& v);

    friend bool operator!=(const NVector& u, const std::string& str);

    friend bool operator!=(const std::string& str, const NVector& u);

    friend bool operator!=(const NVector& u, double s);


    // STATIC FUNCTIONS

    /**
     *
     * @param dim : dimension of the vector
     * @return a 0 vector (0, 0, ..., 0).
     */
    static NVector zeros(unsigned long dim);

    /**
     *
     * @param dim : dimension of the vector
     * @return Returns vector filled with 1 (1, 1, ..., 1).
     */
    static NVector ones(unsigned long dim);

    /**
     *
     * @param s : value of the scalar vector
     * @param dim dimension of the scalar vector
     * @return a vector filled with s (s, s, ..., s).
     */
    static NVector scalar(double s, unsigned long dim);

    /**
     *
     * @param k : index of vector in base
     * @param dim : dimension of vector space represented by the base.
     * @return  return the kth vector of canonical base. ie (e0, e1, ..., e(n-1)) where :
     *          e0 = (1, 0, ..., 0), e1 = (0, 1, 0, ..., 0), ..., e(n - 1) = (0, 0, ..., 1).
     */
    static NVector canonical(unsigned long k, unsigned long dim);

    /**
     *
     * @param vectors : an array of vectors [u0, u1, ..., u(r-1)] where r is the size of the array
     * @return the sum of the vectors : u0 + u1 + ... + u(r-1). where + is usual addition
     */
    static NVector sum(const std::vector<NVector>& vectors);

    /**
     *
     * @param scalars : coefficients of linear combination [s0, s1, ..., s(r-1)] where r is the size of the array
     * @param vectors : vectors of linear combination (u0, u1, ..., u(r-1))
     * @return  the linear combination s0 * u0 + s1 * u1 + ... + s(r-1) * u(r-1). where + and * are
     *          usual addition and scalar multiplication.
     */
    static NVector sumProd(const std::vector<double>& scalars, const std::vector<NVector>& vectors);

protected:

    // VECTOR SPACE OPERATIONS

    virtual void add(const NVector &u);

    virtual void sub(const NVector &u);

    virtual void opp();

    virtual void prod(double s);

    virtual void div(double s);

    // EUCLIDEAN SPACE OPERATIONS

    double dotProduct(const NVector &u) const;

    double norm() const;

    double distance(const NVector &u) const;

    //CHARACTERIZATION

    bool isValidIndex(unsigned long k) const;

    bool isBetweenK12(unsigned long k) const;

    bool isNull() const;

    bool isEqual(const NVector &u) const;

    bool isCompatible(const NVector &u) const;

    virtual bool hasDefaultBrowseIndices() const;

    virtual void setDefaultBrowseIndices() const;

    // AFFECTATION

    void copy(const NVector &u);

    virtual void parse(const std::string& str);

    //SUB-VECTORS

    NVector subVector(unsigned long k1, unsigned long k2) const;

    void setSubVector(const NVector &u);

    //BROWSE INDICES

    mutable unsigned long _k1;

    mutable unsigned long _k2;
};


#endif //MATHTOOLKIT_VECTOR_H
