/**
 * @class          : NPMatrix
 * @date           : 04/05/2018
 * @author         : samiBendou
 * @description    : A NPMatrix inherits from ENVector. It's a representation of a numerical matrices of arbitrary
 *                   size. We will use the following definitions :
 *
 *                      - n : Number of Rows
 *                      - p : Number of Columns
 *                      - i : Row Index between 0 <= i < n
 *                      - j : Column Index 0 <= j < p
 *                      - k, l : either compound index or underlying std::vector array index.
 *                      - A : This NPMatrix. the components of the matrix in a certain base are noted Aij.
 *                      - R : This NVec
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

using namespace std;

enum ElementEnum{Row, Col};

class NPMatrix : public ENVector {
public:
    // CONSTRUCTION

    /**
     *
     * @return a n x p matrix constructed using a std::vector of size n * p.
     */
    explicit NPMatrix(unsigned long n, unsigned long p = 0);

    /**
     *
     * @return a 1 x p row matrix constructed using a std::vector of size 1 * vector.dim().
     */
    explicit NPMatrix(const ENVector& vector);

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

    NPMatrix(const vector< std::string >& vectors);

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


    /**
     *
     * @param i1/j1 : start index of rows/cols
     * @param i2/j2 : end index i2/j2 >= i1/j1 of rows/cols
     * @return a sub matrix with rows starting at i1 and ending at i2 and cols starting at j1 and ending at j2 :
     *
     *  |Ai1j1, ..., Ai2j1|
     *  |...  , ..., ...  |
     *  |Ai2j1, ..., Ai2j2|
     *
     *  Start indices are by default 0 and end indices are by default n or p.
     */
    NPMatrix subMatrix(unsigned long i1 = 0, unsigned long j1 = MAX_SIZE, unsigned long i2 = 0, unsigned long j2 = MAX_SIZE);


    // SETTERS

    /**
     *
     * @param vector row/col seen as ENVector. The dimension of the vector must be equal to the number of cols/rows
     * @param i1/j1 index of row/col to set
     */
    void setRow(const ENVector& vector, unsigned long i1 = 0);


    void setCol(const ENVector& vector, unsigned long j1 = 0);

    /**
     *
     * @param vectors : std::vector of ENVector representing rows/cols to set on the matrix.
     *                  - The length of each row/col must be inferior or equal to the number of cols/rows.
     *                  - The total number of rows/cols must be inferior or equal to the number of rows/cols.
     * @param i1/j1 :   start index to set row/col. If i1/j1 + vectors.size() > n/p Then the algorithm truncate the
     *                  array of ENVector.
     * @description :   Replace the components of the matrix with the array of vectors. For example setCols will change
     *                  the matrix this way :
     *
     *                  |A00, ..., A0(j1 - 1), v[0]0, ..., v[q-1]0, ..., A0(p-1)|
     *                  |A00, ..., A0(j1 - 1), v[0]1, ..., v[q-1]1, ..., A0(p-1)|
     *                  |Ai0, ..., Ai(j1 - 1), v[0]i, ..., v[q-1]i, ..., Ai(p-1)|
     *                  |A(n-1)0, ..., A(n-1)(j1 - 1), v[0](n-1), ..., ..., ... |
     *
     *                  Where q is the size of the vector array.
     */
    void setRows(const std::vector<ENVector>& vectors, unsigned long i1 = 0);

    void setCols(const std::vector<ENVector>& vectors, unsigned long j1 = 0);

    void setSubMatrix(const NPMatrix& matrix, unsigned long i1 = 0, unsigned long j1 = 0);


    // SWAP

    /**
     *
     * @param i1/j1 first row/col indices to swap
     * @param i2/j2 second row/col indices to swap
     * @description : Swap Ai1j1 and Ai2j2.
     */
    void swap(unsigned long i1, unsigned long j1, unsigned long i2, unsigned long j2);

    /**
     *
     * @param i1/j1 first row/col indices to swap
     * @param i2/j2 second row/col indices to swap
     * @description : Swap Ri1/Cj1 and Ri2/Cj2.
     */
    void swapRow(unsigned long i1, unsigned long i2);

    void swapCol(unsigned long j1, unsigned long j2);


    // SHIFT

   /**
   *
   * @param i index of row/col to shift
   * @param iterations number of times to shift. If iterations is > 0, shift is powered to the left/up,
   *                   else to the right/down.
   * @desciption : shift a i/j row/col. For example shiftCol(0, 2) will return :
   *
   *                  |A20, ..., ...|
   *                  |A30, ..., ...|
   *                  |..., ..., ...|
   *                  |A(n-1)0,  ...|
   *                  |A00, ..., ...|
   *                  |A10, ..., ...|
   */
    void shiftRow(unsigned long i, long iterations = 1);

    void shiftCol(unsigned long j, long iterations = 1);


    // MAX / MIN


    /**
     *
     * @param i/j row/col where to search max
     * @param r start index in the row/col to search.
     * @return  the index of the maximum value in the row/col.
     *          maxAbsIndexRow(i, r) will search the max in [Air, Ai(r+1), ..., Ai(n-1)].
     */
    unsigned long maxAbsIndexRow(unsigned long i, unsigned long r = 0) const;

    unsigned long maxAbsIndexCol(unsigned long j, unsigned long r = 0) const;


    // OPERATORS

    /**
     * @return m1 + m2 where + is usual addition for matrices. The matrices must have the length.
     */
    friend NPMatrix operator+(const NPMatrix& m1, const NPMatrix& m2);
    /**
     * @return m1 - m2 where - is substraction based on + for matrices. The matrices must have the length.
     */
    friend NPMatrix operator-(const NPMatrix& m1, const NPMatrix& m2);
    /**
     * @return s * m where * is usual scalar multiplication for matrices.
     */
    friend NPMatrix operator*(double s, const NPMatrix &m);

    friend NPMatrix operator*(const NPMatrix &m, double s);
    /**
     * @return  m1 * m2 where * is usual matrix multiplication. The matrices must have the length.
     *          Natural O(n3) matrix product is used.
     */
    friend NPMatrix operator*(const NPMatrix& m1, const NPMatrix& m2);

    /**
     *
     * @return  m * v where * is usual matrix vector product (linear mapping). The number of rows of m must
     *          be equal to the dimension of v. Natural O(n2) linear mapping is used.
     */
    friend ENVector operator*(const NPMatrix &m, const ENVector &v);

    /**
     * @return Returns the shifted matrix m1 | m2 which is the matrix obtained after concatenation of m1 columns
     * and m2 columns. m1 and m2 must have the same number of rows.
     */
    friend NPMatrix operator|(const NPMatrix& m1, const NPMatrix& m2);

    /**
     * @return (1 / s) * m where * is usual scalar multiplicationb.
     */
    friend NPMatrix operator/(const NPMatrix &m, double s);

    /**
     * @return the usual opposite of the matrix -m.
     */
    friend NPMatrix operator-(const NPMatrix &m);

    /**
     *
     * @return the the transposed of m.
     */
    friend NPMatrix operator!(const NPMatrix &m);
    // Returns transposed of matrix


    // COMPOUND OPERATORS

    NPMatrix& operator*=(const NPMatrix& matrix);
    // Store matrix product with matrix in this matrix

    NPMatrix& operator*=(double scalar) override;


    // BI-DIMENSIONAL ACCESSORS

    /**
     *
     * @return component ij of matrix. Operator can be used to read/write values.
     */
    double& operator()(unsigned long i, unsigned long j);

    double operator()(unsigned long i, unsigned long j) const;

    // ALGEBRA

    /**
     * @description :   Apply Gauss Jordan elimination on matrix to calculate inverse for non square matrix.
     *                  To perform this, shift the matrix you want to invert than apply this function.
     */
    void reduce();

    // STATIC FUNCTIONS

    /**
     *
     * @return zero nxp matrix, ie. filled with 0.
     */
    static NPMatrix zeros(unsigned long n, unsigned long p = 0);

    /**
     *
     * @return nxp matrix filled with 1
     */
    static NPMatrix ones(unsigned long n, unsigned long p = 0);
    /**
     * @param i row where to put 1.
     * @param j col where to put 1.
     *
     * @return canonical matrices Eij which contains 1 in position ij and 0 elsewhere.
     */
    static NPMatrix canonical(unsigned long i, unsigned long j, unsigned long n, unsigned long p = 0);
    // Returns canonical matrix Eij of Mnp(R)

protected:

    // AFFECTATION

    void parse(const vector<string> &str);

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

    virtual void matrixProduct(const NPMatrix& matrix);

    NPMatrix shifted(const NPMatrix& matrix) const;
    //Get a shifted matrix used in Gauss Jordan algorithm.
    //  Shifted = [THIS | MATRIX] where Shifted is a N x (PThis + PMatrix)

    unsigned long _n;

    unsigned long _p;
};


#endif //MATHTOOLKIT_NPMATRIX_H
