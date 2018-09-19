/**
 * @class          : ENVector
 * @date           : 03/05/2018
 * @author         : samiBendou
 * @description    : A ENVector object inherit from NVector. It is a euclidean space vector. In this class,
 *                   we will use the following definitions :
 *
 *                   -epsilon : the smallest strictly positive double quantity
 *                              representable in memory which is std::numeric_limits<double>::epsilon().
 *
 *                   -||.||    : the norm base on dot product * which is usual dot product.
 *
 *
 *                   Featuring norm, comparison between vectors and distance.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */


#ifndef MATHTOOLKIT_ENVECTOR_H
#define MATHTOOLKIT_ENVECTOR_H

#include "NVector.h"

class ENVector : public NVector {
public:

    // CONSTRUCTORS

    explicit ENVector(unsigned long dim = 0);

    ENVector(const NVector& vector);

    ENVector(const ENVector& vector);


    // OPERATORS


    friend ENVector operator+(const ENVector& v1, const ENVector& v2);

    friend ENVector operator-(const ENVector& v1, const ENVector& v2);

    friend ENVector operator*(double scalar, const ENVector& vector);

    friend ENVector operator*(const ENVector& vector, double scalar);

    friend ENVector operator/(const ENVector& vector, double scalar);
    

    // NORM BASED COMPARISON OPERATORS

    /**
     *
     * @return return true if ||v1 - v2|| < epsilon.
     */
    friend bool operator==(const ENVector& v1, const ENVector& v2);

    friend bool operator==(const ENVector& vector, double scalar);

    /**
     *
     * @return return true if ||v1 - v2|| >= epsilon.
     */
    friend bool operator!=(const ENVector& v1, const ENVector& v2);

    friend bool operator!=(const ENVector& vector, double scalar);

    /**
     *
     * @return return true if ||v1|| > ||v2||.
     */
    friend bool operator<(const ENVector& v1, const ENVector& v2);

    friend bool operator>(const ENVector& v1, const ENVector& v2);

    /**
     *
     * @return return true if ||v1|| >= ||v2||.
     */
    friend bool operator<=(const ENVector& v1, const ENVector& v2);

    friend bool operator>=(const ENVector& v1, const ENVector& v2);


    // SCALAR PRODUCT BASED OPERATIONS

    /**
     *
     * @return the norm of vector ||.||
     */
    friend double operator!(const ENVector& vector);
    // Returns norm of vector !v1 = ||v1||


    /**
     *
     * @return u * v where * is usual dot product u0 * v0 + u1 * v1 + ... + u(n-1) * v(n-1)
     */
    friend double operator*(const ENVector &u, const ENVector &v);

    /**
     *
     * @return distance between v1 & v2, ||v1 - v2||.
     */
    friend double operator/(const ENVector& v1, const ENVector& v2);

    // STATIC METHODS
    static ENVector sum(const std::vector<ENVector>& vectors);

    static ENVector sumProd(const std::vector<double>& scalars, const std::vector<ENVector>& vectors);



protected:

    bool isNull() const;
    // Returns true if the two norm and the vector is less than epsilon constant

    bool isEqual(const ENVector& vector) const;

    double dot(const ENVector& vector) const;
    // Canonical scalar product x * y = x1 * y1 + x2 * y2 + ...

    double norm() const;
    // Norm derived from scalar product

    double distance(const ENVector& vector) const;
    // Distance derived from scalar product
};


#endif //MATHTOOLKIT_ENVECTOR_H
