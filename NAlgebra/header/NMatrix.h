/**
 * @class          : NMatrix
 * @date           : 05/05/2018
 * @author         : samiBendou
 * @description    : A NMatrix inherits from NPMatrix<double>. It's a representation of a numerical square matrices.
 *                   The LU decomposition is stored as property of square matrices. It is auto-updated only on need.
 *                   It allow to reduce complexity to get invert or determinant. Precisely the LU decomposition is
 *                   represented by :
 *
 *                      -a : is matrix A = L * U where PA = LU = this. a points to the A NMatrix or points to nullptr if
 *                           the matrix has never calculated LU decomposition or if the decomposition failed.
 *                      -permutation : permutation vector P such as PA = LU. Represented as ul_t array.
 *
*                    The *a object never is never used directly so it's own a pointer a->a always points to nullptr.
 *
 *                   Featuring LU decomposition, classic matrix recognition & generation (lower, upper, diag, eye...),
 *                   linear systems solving, matrix inversion and determinant, fast exponentiation...
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_NMATRIX_H
#define MATHTOOLKIT_NMATRIX_H

#include "NVector.h"
#include "NPMatrix.h"

class NMatrix : public NPMatrix<double> {
public:

    using NPMatrix<double>::operator=;

    // CONSTRUCTION

    explicit NMatrix(ul_t n = 0);

    explicit NMatrix(const std::string& str);

    NMatrix(const NPMatrix<double>& matrix);

    NMatrix(const NMatrix& matrix);

   ~NMatrix();


    // CHARACTERIZATION

    bool isUpper() const;

    bool isLower() const;

    bool isDiagonal() const;

    // GETTERS

    /**
     *
     * @return upper part of this matrix as a upper matrix.
     */
    NMatrix upper() const;

    /**
     *
     * @return lower part of this matrix as a lower matrix.
     */
    NMatrix lower() const;

    /**
     *
     * @return L/U matrix of LU decomposition of this matrix
     */
    NMatrix lupL();

    NMatrix lupU();

    // OPERATIONS / OPERATORS

    /**
     *
     * @return trace of this matrix A00 + A11 + ... + A(n-1)(n-1)
     */
    double trace() const;
    /**
     *
     * @return determinant of this matrix det(A). Using the LU decomposition O(n).
     */
    double det();
    // Determinant of this


    
    // OPERATIONS

    NMatrix operator+(const NMatrix &m) const;

    NMatrix operator-(const NMatrix &m) const;

    NMatrix operator-() const;

    using NPMatrix<double>::operator*;

    friend NMatrix operator*(double s, const NMatrix &m);

    friend NMatrix operator*(const NMatrix &m, double s);

    NMatrix operator*(const NMatrix &m) const;

    NMatrix operator/(double s) const;

    /**
     *
     * @param m matrix to exponentiate.
     * @param exp long integer exponent. If exp < 0 we calculate the power of the inverse matrix m^-1 (O(n3)).
     * @return m^exp using fast exponentiation algorithm.
     */
    friend NMatrix operator^(const NPMatrix<double> &m, long exp);

    /**
     * @param m matrix of the equation system.
     * @param v second member of the equation system.
     * @return the solution of m * x = v by inverting the m matrix.
     */
    friend NVector<double> operator%(NMatrix &m, const NVector<double> &v);
    
    NVector<double>& operator^=(long exp);

    double &operator()(ul_t i, ul_t j);

    double operator()(ul_t i, ul_t j) const;

    NMatrix operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const;

    NMatrix &operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2);

    // STATIC FUNCTIONS

    /**
     *
     * @param n size of the matrix
     * @return n-th order Identity matrix
     */
    static NMatrix eye(ul_t n);

    /**
     *
     * @param data values of diagonal [d0, d1, ..., d(n-1)]
     * @param n size of the matrix
     * @return Returns diagonal n-th order diagonal matrix filled with data array
     */
    static NMatrix diag(const std::vector<double> &data, ul_t  n);


    /**
     *
     * @return a scalar n-th order matrix with s value. This is a diagonal matrix filled with s.
     */
    static NMatrix scalar(double s, ul_t n);

    /**
     *
     * @param data values of multiple diagonal such as :
     *          -data[l] is the values of coefficients of the l-th diagonal from the left.
     *          -data[middle] is the values of coefficients on the diagonal.
     *
     * @return a n-diagonal matrix filled with data bi-dimensional array which looks like :
     *
     *          |d[middle]0,    d[middle+1]0,   ...|
     *          |d[middle-1]0,  d[middle]1,     ...|
     *          |               ...                |
     *          |d[0]0, d[1]1,  ..., d[middle](n-1)|
     *
     *          The input data must be ordered such as d[0] has size equal to 1, d[1] to 2, ..., d[middle] to n,
     *          d[middle+1] to n-1, ..., d[end] to 0.
     */
    static NMatrix ndiag(const std::vector<NVector<double> > &data);


    /**
     *
     * @param scalars array of scalars values to fill diagonals [s0, s1, ..., sq]
     * @param n size of the matrix
     * @return  a n-scalar Matrix filled with values. If values.length = 2, the matrix is tri-diagonal.
     *          Center diagonal is filled with s1 and the other diagonal are filled with s0.
     */
    static NMatrix nscalar(const std::vector<double> &scalars, const ul_t n);

protected:
    NMatrix* _a;

    std::vector<ul_t>* _perm;

    // ALGEBRAICAL OPERATIONS

    void add(const NVector<double>& vector) override ;

    void sub(const NVector<double>& vector) override ;

    void opp() override ;

    void prod(double scalar) override ;

    void div(double scalar) override ;

    void matrixProduct(const NPMatrix<double> &m) override ;

    void pow(long n);

    void rPow(long n);
    // Exponentiation by squaring of this matrix : O(log(exp) * n3)

    void inv();
    // Inversion of this matrix (O(n3))

    void solve(NVector<double>& vector);
    //Solve this * X = b stores X in b vector


    // LUP MANAGEMENT

    void lupUpdate();
    //LUP decomposition of a Matrix
    //Stores P (_perm) and A (_a) such as PA = LU where P is a row permutation array and A = L + U;

    void lupClear();
    //Clears _a and _perm

    // SERIALIZATION

    void copy(const NPMatrix<double>& m) override;
};


#endif //MATHTOOLKIT_NMATRIX_H
