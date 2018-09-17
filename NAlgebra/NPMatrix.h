/**
 * @class          : NPMatrix
 * @date           : 04/05/2018
 * @author         : samiBendou
 * @description    : A NPMatrix inherits from ENVector. It's a representation of a numerical matrices of arbitrary
 *                   size. We will use the following definitions :

 *                      - n : Number of Rows
 *                      - p : Number of Columns
 *                      - i : Row Index between 0 <= i < n
 *                      - j : Column Index 0 <= j < p
 *                      - k, l : either compound index or underlying std::vector array index.
 *                      - A : This NPMatrix. the components of the matrix in a certain base are noted Aij.
 *
 *                   The matrix components are stored in a linear form with the index transformation k = p * i + j.
 *                   The underlying std::vector is represented as t[p * i + j].
 *                   The underlying NVector is (A00, A01, ..., A0(P - 1), A10, ..., A1(P - 1), ..., A(N-1)0, ...).
 *
 *                   Featuring algebraical operations such as matrix product, linear map, gauss jordan elimination.
 *                   setters & getters, swappers and classic matrix generators such as ones, zeros...
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */


#ifndef MATHTOOLKIT_NPMATRIX_H
#define MATHTOOLKIT_NPMATRIX_H



#include "ENVector.h"

#define DEF

using namespace std;

enum ElementEnum{Row, Col};

class NPMatrix : public ENVector {
public:
    // CONSTRUCTION

    /**
     *
     * @return a n x p matrix constructed using a std::vector of size n * p.
     */
    NPMatrix(unsigned long n, unsigned long p = 0);

    /**
     *
     * @return a 1 x p row matrix constructed using a std::vector of size 1 * vector.dim().
     */
    NPMatrix(const ENVector& vector);

    /**
     *
     * @return a n x p matrix constructed using a std::vector of n * p where vector.dim() must be equal to n * p.
     */
    NPMatrix(const ENVector& vector, unsigned long n, unsigned long p = 0);

    NPMatrix(const NPMatrix& matrix);

    /**
     *
     * @return a n x p matrix constructed using a bi-dimensional std::vector such as Aij = data[i][j]. all the data[i]
     * must have the same length. They represent the rows of A matrix.
     */
    explicit NPMatrix(const vector< vector<double> >& data);

    /**
     *
     * @return a n x p matrix constructed using a std::vector<ENVector>. All the vectors must have the same dimension.
     * They represent the rows of the matrix.
     */

    explicit NPMatrix(const vector< ENVector >& vectors);

    // SERIALIZATION

    /**
     *
     * @return a string representing the matrix in the form :
     *
     *  "
     *  |A00, A01, ..., A0(P-1)|
     *  |A10, A11, ..., A1(P-1)|
     *  |Ai0, ..., Aij, Ai(P-1)|
     *  |A(N-1)0, ..., ..., ...|
     *  "
     *
     *   Aij is formatted with exponential notation with 2 decimals.
     */
    std::string str() const override;


    // CHARACTERIZATION

    /**
     *
     * @return true if i < n resp. j < p.
     */
    bool isValidRowIndex(unsigned long i) const;

    bool isValidColIndex(unsigned long j) const;

    bool isValidIndex(unsigned long i, unsigned long j) const;

    /**
     *
     * @return true if n = p.
     */
    bool isSquare() const;


    // GETTERS

    unsigned long n() const;

    unsigned long p() const;

    /**
     *
     * @return return the ith row Ri of (resp. the jth col Cj) the matrix as a ENVector.
     */
    ENVector row(unsigned long i) const;

    ENVector col(unsigned long j) const;

    /**
     *
     * @param i1/j1 start index of rows/cols
     * @param i2/j2 end index i2/j2 >= i1/j1 of rows/cols
     * @return the rows/cols of the matrix in the form of std::vector<ENVector>.
     *          -rows()/cols() return all the rows/cols.
     *          -rows(i1)/cols(j1) returns the rows [Ri1, R(i1+1),..., R(n-1)]/ cols [Rj1, R(j1+1),..., C(p-1)]
     *          -rows(i1, i2)/cols(j1, j2) returns the rows [Ri1, R(i1+1),..., Ri2]/ cols [Cj1, C(j1+1),..., Cj2]
     */
    std::vector<ENVector> rows(unsigned long i1 = 0, unsigned long i2 = MAX_SIZE) const;

    std::vector<ENVector> cols(unsigned long j1 = 0, unsigned long j2 = MAX_SIZE) const;



    NPMatrix subMatrix(unsigned long i1 = 0, unsigned long j1 = MAX_SIZE, unsigned long i2 = 0, unsigned long j2 = MAX_SIZE);


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
