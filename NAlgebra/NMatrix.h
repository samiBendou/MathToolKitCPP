//
// Created by Sami Dahoux on 05/05/2018.
//
//
//@license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
//@class          : NMatrix
//@description    : Representation of numerical N x N Matrix vector space. Featuring LU decomposition, classic matrix
//                  recognition & generation (lower, upper, diag, eye...), linear systems solving,
//                  matrix inversion and determinant, fast exponentiation...
//
//                  The LU decomposition is stored as member of square matrices. It is auto-updated only on need.
//
//                  a : is matrix A = L + U where PA = LU = this
//                  permutation : permutation vector P

#ifndef MATHTOOLKIT_NMATRIX_H
#define MATHTOOLKIT_NMATRIX_H

#include "ENVector.h"
#include "NPMatrix.h"

class NMatrix : public NPMatrix {
public:
    NMatrix(const NPMatrix& matrix);

    NMatrix(const NMatrix& matrix);


    // CHARACTERIZATION

    bool isUpper() const;

    bool isLower() const;

    bool isDiagonal() const;

    // GETTERS

    NMatrix upper() const;
    // Returns upper part of this matrix

    NMatrix lower() const;
    // Returns lower part of this matrix

    NMatrix lupL();
    // Returns L matrix of LU decomposition of this matrix

    NMatrix lupU();
    // Returns U matrix of LU decomposition of this matrix

    // OPERATIONS / OPERATORS

    double trace() const;
    // Trace of this matrix
    double det();
    // Determinant of this

    void matrixProduct(const NPMatrix &matrix);
    
    // OPERATIONS

    friend NMatrix operator^(const NPMatrix &matrix, long exp);
    // Returns matrix elevated to power exp;

    friend ENVector operator%(NMatrix &matrix, const NVector &vector);
    // Returns result of linear application represented by matrix at vector.
    
    NVector& operator^=(long exp);

    friend NMatrix operator+(const NMatrix& m1, const NMatrix& m2);

    friend NMatrix operator-(const NMatrix& m1, const NMatrix& m2);

    friend NMatrix operator*(double scalar, const NMatrix& matrix);

    friend NMatrix operator*(const NMatrix& matrix, double scalar);

    friend NMatrix operator*(const NMatrix& m1, const NMatrix& m2);

    friend NMatrix operator/(const NMatrix& matrix, double scalar);


    friend NMatrix operator-(const NMatrix& matrix);

    friend NMatrix operator!(const NMatrix& matrix);

    // STATIC FUNCTIONS

    static NMatrix eye(unsigned long n);
    //Returns n-th order Identity matrix

    static NMatrix diag(const std::vector<double> &data, unsigned long  n);
    //Returns diagonal n-th order matrix  filled with arr Array

    static NMatrix scalar(double scalar, unsigned long n);
    //Returns a scalar n-th order matrix filled with value

    static NMatrix nDiag(const std::vector< ENVector > & data);
    //Returns a n-diagonal matrix filled with arr bi-dimensional array :
    // -data[l] is the values of coefficients of the l-th diagonal from the left
    // -data[middle] is the values of coefficients on the diagonal.


    static NMatrix nScalar(const std::vector<double> & scalars, unsigned long n);
    //Returns a n-scalar Matrix filled with values. If values.length = 2, the matrix is tri-diagonal. and values[1] is
    //the value of the diagonal.

protected:
    NMatrix* _a;

    unsigned long* _permutation;

    // ALGEBRAICAL OPERATIONS

    void add(const NVector& vector) override ;

    void sub(const NVector& vector) override ;

    void opp() override ;

    void prod(double scalar) override ;

    void div(double scalar) override ;

    void rPow(long n);
    // Exponentiation by squaring of this matrix : O(log(exp) * n3)

    void pow(long n);
    // Exponentiation for relative integers

    void inv();
    // Inversion of this matrix (O(n3))

    void solve(ENVector& vector);
    //Solve this * X = b stores X in b vector


    // LUP MANAGEMENT

    void lupUpdate();
    //LUP decomposition of a Matrix
    //Stores P (_permutation) and A (_a) such as PA = LU where P is a row permutation array and A = L + U;

    void lupClear();
    //Clears _a and _permutation
};


#endif //MATHTOOLKIT_NMATRIX_H
