//
// Created by Sami Dahoux on 04/05/2018.
//
//
//@license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
//@class          : NPMatrix
//description     : Representation of numerical N x P Matrix vector space. Featuring algebraical operations,
//                  setters & getters, swappers and classic matrix generator such as ones, zeros...
//                  The matrix is a vector with the following index transformation k = p * i + j
//
//                  - n : Number of Rows
//                  - p : Number of Columns
//                  - i : Row Index
//                  - j : Column Index
//                  - k, l : either compound index or inherited _data array index.

#ifndef MATHTOOLKIT_NPMATRIX_H
#define MATHTOOLKIT_NPMATRIX_H


#include "ENVector.h"

using namespace std;

enum ElementEnum{Row, Col};

class NPMatrix : public ENVector {
public:
    NPMatrix(unsigned long n, unsigned long p = 0);

    NPMatrix(const ENVector& vector);

    NPMatrix(const ENVector& vector, unsigned long n, unsigned long p = 0);

    NPMatrix(const NPMatrix& matrix);


    explicit NPMatrix(const vector< vector<double> >& data);

    explicit NPMatrix(const vector< ENVector >& vectors);


    std::string str() const override;


    // CHARACTERIZATION

    bool isValidRowIndex(unsigned long i) const;

    bool isValidColIndex(unsigned long j) const;

    bool isValidIndex(unsigned long i, unsigned long j) const;

    bool isSquare() const;


    // GETTERS

    unsigned long n() const;

    unsigned long p() const;

    ENVector row(unsigned long i) const;

    ENVector col(unsigned long j) const;

    std::vector<ENVector> rows(unsigned long i1 = 0, unsigned long i2 = -1) const;

    std::vector<ENVector> cols(unsigned long j1 = 0, unsigned long j2 = -1) const;

    NPMatrix subMatrix(unsigned long i1 = 0, unsigned long j1 = -1, unsigned long i2 = 0, unsigned long j2 = -1);


    // SETTERS

    void setRow(const ENVector& vector, unsigned long i1 = 0);

    void setCol(const ENVector& vector, unsigned long j1 = 0);

    void setRows(const std::vector<ENVector>& vectors, unsigned long i1 = 0);

    void setCols(const std::vector<ENVector>& vectors, unsigned long j1 = 0);

    void setSubMatrix(const NPMatrix& matrix, unsigned long i1 = 0, unsigned long j1 = 0);


    // SWAP


    void swap(unsigned long i1, unsigned long j1, unsigned long i2, unsigned long j2);

    void swapRow(unsigned long i1, unsigned long i2);

    void swapCol(unsigned long j1, unsigned long j2);


    // SHIFT


    void shiftRow(unsigned long i, long iterations = 1);

    void shiftCol(unsigned long j, long iterations = 1);


    // MAX / MIN


    unsigned long maxAbsIndexRow(unsigned long i, unsigned long r = 0) const;

    unsigned long maxAbsIndexCol(unsigned long j, unsigned long r = 0) const;


    // OPERATORS


    friend NPMatrix operator+(const NPMatrix& m1, const NPMatrix& m2);

    friend NPMatrix operator-(const NPMatrix& m1, const NPMatrix& m2);

    friend NPMatrix operator*(double scalar, const NPMatrix& matrix);

    friend NPMatrix operator*(const NPMatrix& matrix, double scalar);

    friend NPMatrix operator*(const NPMatrix& m1, const NPMatrix& m2);
    //Returns Natural O(n3) matrix product m1 * m2.

    friend ENVector operator*(const NPMatrix& matrix, const ENVector& vector);
    //Returns Natural O(n2) matrix apply to vector.

    friend NPMatrix operator|(const NPMatrix& m1, const NPMatrix& m2);
    // Returns the shifted matrix m1 | m2

    friend NPMatrix operator/(const NPMatrix& matrix, double scalar);


    friend NPMatrix operator-(const NPMatrix& matrix);

    friend NPMatrix operator!(const NPMatrix& matrix);
    // Returns transposed of matrix

    NPMatrix& operator*=(const NPMatrix& matrix);
    // Store matrix product with matrix in this matrix

    NPMatrix& operator*=(double scalar);


    // BI-DIMENSIONAL ACCESSORS


    double& operator()(unsigned long i, unsigned long j);

    double operator()(unsigned long i, unsigned long j) const;


    // STATIC FUNCTIONS


    static NPMatrix zeros(unsigned long n, unsigned long p = 0);

    static NPMatrix ones(unsigned long n, unsigned long p = 0);

    static NPMatrix canonical(unsigned long i, unsigned long j, unsigned long n, unsigned long p = 0);
    // Returns canonical matrix Eij of Mnp(R)

protected:


    // INDEX GETTERS


    unsigned long getVectorIndex(unsigned long i, unsigned long j) const;

    unsigned long getRowFromVectorIndex(unsigned long k) const;

    unsigned long getColFromVectorIndex(unsigned long k) const;


    // OPERATIONS


    void swap(ElementEnum element, unsigned long k1, unsigned long k2);

    void shift(ElementEnum element, unsigned long k, long iterations);

    unsigned long maxAbsIndex(ElementEnum element, unsigned long k, unsigned long r) const;

    void transpose();

    void vectorProduct(NVector& vector) const;

    void matrixProduct(const NPMatrix& matrix);


    void reduce();
    //Apply Gauss Jordan elimination algorithm

    NPMatrix shifted(const NPMatrix& matrix) const;
    //Get a shifted matrix according to Gauss Jordan algorithm.
    //  Shifted = [THIS | MATRIX] where Shifted is a N x (PThis + PMatrix)

    unsigned long _n;

    unsigned long _p;
};


#endif //MATHTOOLKIT_NPMATRIX_H
