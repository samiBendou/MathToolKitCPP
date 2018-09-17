/**
 * @class          : NVector
 * @date           : 03/05/2018
 * @author         : samiBendou
 * @description    : A NVector object stores the coordinates of a finite dimension vector E in a certain base.
 *                   Theses are stored in the form [x0, x1, ..., x(n-1)]. where [...] is a std::vector<double>,
 *                   n is the dimension and (x0, x1, ..., x(n-1)) are the coordinates.
 *
 *                   Representation of a finite dimension vector space. This object is the base object of every
 *                   other object in NAlgebra module. It inherits from std::vector<double> so it's kind of memory
 *                   support for every object in NAlgebra module.
 *
 *                   Featuring algebraical operations (E, +, *), swaps, shifts and
 *                   classic vectors generator such as ones, zeros...
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_VECTOR_H
#define MATHTOOLKIT_VECTOR_H

#define MAX_SIZE 4294967295

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdarg>

class NVector : public std::vector<double> {

public:
    // CONSTRUCTORS

    /**
     *
     * @return a NVector with an array of data. The dimension is the size of the array.
     */
    NVector(const std::vector<double>& data);

    NVector(const NVector& vector);
    /**
     *
     * @return  a NVector by giving the dimension. This method uses the std::vector constructor
     *          to create a vector.
     */
    explicit NVector(unsigned long dim = 0);

    // SERIALIZATION

    /**
     *
     * @return a string representing the coordinates of the vector in the format "[x0, x1, ..., x(n-1)]".
     * xi is formatted with exponential notation with 2 decimals.
     */
    virtual std::string str() const;

    // CHARACTERIZATION

    /**
     *
     * @param k : Index to test
     * @return true if k is valid, ie. if k is between 0 and dim() - 1.
     */
    bool isValidIndex(long k) const;
    // Returns true

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
    std::vector<double> array();


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
     * @param k1 : First index to swap
     * @param k2 : Second index to swap
     * @description : Permutation of two elements (x(k1 - 1), xk2, ..., x(k2 - 1), xk1, ..., x(n-1))
     */
    void swap(unsigned long k1, unsigned long k2);

    /**
     *
     * @param iterations :  number of times to shift. If iterations is > 0, shift is powered to the left,
     *                      else to the right.
     * @description : Shifts vector iterations times. ie. with iterations = 2 : (x2, x3, ..., x(n-1), x0, x1).
     */
    void shift(long iterations);

    /**
     *
     * @param scalar : value to fill the vector with
     * @description : Fill vector with a scalar : ie. with scalar = 3, (3, 3, 3, ..., 3).
     */
    void fill(double scalar);


    // OPERATORS

    /**
     * @return result of u + v where + is the usual addition (u0 + v0, u1 + v1, ...).
     */
    friend NVector operator+(const NVector &u, const NVector &v);

    /**
     * @return return u - v where - is difference based on usual addition.
     */
    friend NVector operator-(const NVector &u, const NVector &v);

    /**
     * @return s * u where * is usual scalar multiplication (s * u0, s * u1, ...).
     */
    friend NVector operator*(double s, const NVector &u);

    friend NVector operator*(const NVector &u, double s);

    /**
     * @return return (1 / s) * u where * is the usual scalar multiplication (s * u0, s * u1, ...).
     */
    friend NVector operator/(const NVector &u, double s);

    /**
     * @return opposite of u (-u0, -u1, ...).
     */
    friend NVector operator-(const NVector &u);


    // COMPOUND OPERATORS


    NVector& operator+=(const NVector& vector);

    NVector& operator-=(const NVector& vector);

    NVector& operator*=(double scalar);

    NVector& operator/=(double scalar);


    // ACCES OPERATOR


    /**
     *
     * @param k : index of the coordinate. Between -(dim() - 1) and dim() - 1
     * @return the kth coordinate of the vector xk if k < 0, returns x(n - 1 - k).
     */
    double& operator()(long k);

    double operator()(long k) const;

    /**
     *
     * @param k1 : start index for subrange. Between -(dim() - 1) and dim() - 1.
     * @param k2 : end index for subrange. Between -(dim() - 1) and dim() - 1.
     * @return  a sub vector in representing coordinates from k1 to k2. use this function with |k1| <= |k2|.
     *              - If k1 >= 0 returns : (xk1, x(k1+1), ...,xk2).
     *              - If k1 =< 0 returns : (x(n - 1 - k1), ..., x(n - 1 - k2)).
     *          the non const version of function operator is used to affect a subrange
     *          of this instance of NVector.
     */
    NVector operator()(long k1, long k2) const;

    NVector& operator()(long k1, long k2);


    // STREAM EXTRACT/INSERT

    friend std::ostream& operator<<(std::ostream &os, const NVector &vector);


    // AFFECTATION


    NVector& operator=(const NVector& vector);


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
    //

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
    // Returns linear combination of vectors with scalars coefficients

protected:

    // PROTECTED MEMBERS
    unsigned long _k1;

    unsigned long _k2;
    //Indexes used to return sub vector of a vector or to set a sub vector


    // EXTREMUM GETTERS


    double getExtremum(bool max) const;

    unsigned long getExtremumIndex(bool max) const;


    // ABSOLUTE VALUE EXTREMUM GETTERS


    double getExtremumAbs(bool max) const;

    unsigned long getExtremumAbsIndex(bool max) const;


    //SUB-VECTORS

    NVector subVector(unsigned long k1, unsigned long k2 = 0) const;
    // Returns a sub-vector of this vector (xk1, x(k1 +1), ..., x(k2)) where k1 <= k2

    void setSubVector(const NVector& vector);
    // Sets a sub range (x(k1 - 1), v0, v1, ..., v(dim(v)), ...; xDim) of this vector


    // VECTOR SPACE OPERATIONS


    virtual void add(const NVector& vector);
    //Sum of two vectors

    virtual void sub(const NVector& vector);
    //Subtraction of two vectors

    virtual void opp();
    //Opposite of a vector

    virtual void prod(double scalar);
    //Scalar multiplication

    virtual void div(double scalar);
    //Division by a scalar
};


#endif //MATHTOOLKIT_VECTOR_H
