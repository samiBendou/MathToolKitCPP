//
// Created by Sami Dahoux on 03/05/2018.
//
//
//@license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
//@class          : NVector
//@description    : Representation of a finite dimension numerical vector space. Featuring algebraical operations,
//                  setters & getters, swaps, shifts and classic vectors generator such as ones, zeros...
//
//                  -data : Fixed size array storing vector coordinates on canonical base : (x0, x1, ..., xDim)
//                  -dim : Unsigned unsigned longeger representing Dimension of vector space of this vector.

#ifndef MATHTOOLKIT_VECTOR_H
#define MATHTOOLKIT_VECTOR_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdarg>

class NVector : public std::vector<double> {

public:
    NVector(unsigned long dim = 0);

    NVector(const NVector& vector);

    NVector(const std::vector<double>& data);

    virtual std::string str() const;

    // CHARACTERIZATION

    bool isValidIndex(long k) const;
    // Returns true if k is between 0 and dim - 1

    // GETTERS

    unsigned long dim() const;

    std::vector<double> array();


    // MAX / MIN


    double max() const;

    double min() const;

    unsigned long maxIndex() const;

    unsigned long minIndex() const;


    // ABSOLUTE VALUE MAX / MIN


    double maxAbs() const;

    double minAbs() const;

    unsigned long maxAbsIndex() const;

    unsigned long minAbsIndex() const;


    // MANIPULATORS


    void swap(unsigned long k1, unsigned long k2);
    // Permutation of two elements (x(k1 - 1), xk2, ..., x(k2 - 1), xk1, ..., x_dim)

    void shift(long iterations);
    // Shifts vector iterations times. If iterations is > 0, shift is powered to the left, else to the right.
    void fill(double scalar);
    // Fill vector with a scalar


    // OPERATORS


    friend NVector operator+(const NVector& v1, const NVector& v2);

    friend NVector operator-(const NVector& v1, const NVector& v2);

    friend NVector operator*(double scalar, const NVector& vector);

    friend NVector operator*(const NVector& vector, double scalar);

    friend NVector operator/(const NVector& vector, double scalar);


    friend NVector operator-(const NVector& vector);


    // COMPOUND OPERATORS


    NVector& operator+=(const NVector& vector);

    NVector& operator-=(const NVector& vector);

    NVector& operator*=(double scalar);

    NVector& operator/=(double scalar);


    // ACCES OPERATOR


    double& operator()(long k);

    double operator()(long k) const;

    NVector operator()(long k1, long k2) const;

    NVector& operator()(long k1, long k2);


    // STREAM EXTRACT/INSERT

    friend std::ostream& operator<<(std::ostream &os, const NVector &vector);


    // AFFECTATION


    NVector& operator=(const NVector& vector);


    // STATIC FUNCTIONS

    static NVector zeros(unsigned long dim);
    // Returns 0 vector of dimension dim : v = (0, 0, ...)

    static NVector ones(unsigned long dim);
    // Returns vector filled with 1 : v = (1, 1, ...)

    static NVector scalar(double scalar, unsigned long dim);
    // Returns vector filled with scalar : v = (scalar, scalar, ...)

    static NVector canonical(unsigned long k, unsigned long dim);
    // Returns vector ek of canonical base : e0 = (1, 0, ...), e1 = (0, 1, 0, ...), ...

    static NVector sum(const std::vector<NVector>& vectors);

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
    // Returns a sub-vector of this vector (xk1, x(k1 +1), ..., x(k2))

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
