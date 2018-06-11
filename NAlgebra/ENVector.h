//
// Created by Sami Dahoux on 03/05/2018
//
//
//@license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
//@class          : ENVector
//@description    : Module inheriting from NVector which represent Euclidean Space vector. Featuring norm based upon
//                  inner product scalar and distance between two vectors.


#ifndef MATHTOOLKIT_ENVECTOR_H
#define MATHTOOLKIT_ENVECTOR_H

#include "NVector.h"

class ENVector : public NVector {
public:

    ENVector(unsigned long dim = 0);

    ENVector(const NVector& vector);

    ENVector(const ENVector& vector);


    // OPERATORS


    friend ENVector operator+(const ENVector& v1, const ENVector& v2);

    friend ENVector operator-(const ENVector& v1, const ENVector& v2);

    friend ENVector operator*(double scalar, const ENVector& vector);

    friend ENVector operator*(const ENVector& vector, double scalar);

    friend ENVector operator/(const ENVector& vector, double scalar);
    

    // NORM BASED COMPARISON OPERATORS


    friend bool operator==(const ENVector& v1, const ENVector& v2);

    friend bool operator==(const ENVector& vector, double scalar);

    friend bool operator!=(const ENVector& v1, const ENVector& v2);

    friend bool operator!=(const ENVector& vector, double scalar);

    friend bool operator<(const ENVector& v1, const ENVector& v2);

    friend bool operator>(const ENVector& v1, const ENVector& v2);

    friend bool operator<=(const ENVector& v1, const ENVector& v2);

    friend bool operator>=(const ENVector& v1, const ENVector& v2);


    // SCALAR PRODUCT BASED OPERATIONS


    friend double operator!(const ENVector& vector);
    // Returns norm of vector !v1 = ||v1||

    friend double operator*(const ENVector& v1, const ENVector& v2);
    // Returns scalar product of v1 & v2 : v1 * v2 = (v1 | v2)

    friend double operator/(const ENVector& v1, const ENVector& v2);
    // Returns distance between v1 & v2 : v1 / v2 = d(v1, v2)


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
