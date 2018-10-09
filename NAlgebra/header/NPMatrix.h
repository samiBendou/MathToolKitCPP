/**
 * @class          : NPMatrix
 * @date           : 04/05/2018
 * @author         : samiBendou
 * @description    : A NPMatrix inherits from NVector. It's a representation of a numerical matrices of arbitrary
 *                   size. We will use the following definitions :
 *
 *                      - n : Number of Rows
 *                      - p : Number of Columns
 *                      - i : Row Index between 0 <= i < n
 *                      - j : Column Index 0 <= j < p
 *                      - k, l : either compound index or underlying std::vector array index.
 *                      - A/m : This NPMatrix. the components of the matrix in a certain base are noted Aij.
 *                      - R/C : Rows/Columns of A
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


#include "NVector.h"

using namespace std;

enum ElementEnum {
    Row, Col
};

class NPMatrix : public NVector {

public:
    // CONSTRUCTION

    /**
     *
     * @return a n x p matrix constructed using a std::vector of size n * p.
     */
    explicit NPMatrix(ul_t n = 0, ul_t p = 0);

    /**
     *
     * @return a n x p matrix constructed using a bi-dimensional std::vector such as Aij = data[i][j]. all the data[i]
     * must have the same length. They represent the rows of A matrix.
     */
    explicit NPMatrix(const vector<vector<double> > &data);

    NPMatrix(const NPMatrix &m);

    /**
     *
     * @param str an array of string containing the rows of the matrix in a form like "|0 2 3|".
     * @details initialize a NPMatrix by parsing a string representing matrix rows. Use the following
     *          syntax : {"(A00  A01  ...  A0(P-1)) \
     *                     (A10  A1   ...  A1(P-1)) \
     *                     (...  ...   A(N-1)(P-1))"}
     *          The separation character | can be replaced by any one. Don't use comma at all.
     */
    explicit NPMatrix(const string &str);

    /**
     *
     * @return a 1 x p row matrix constructed using a std::vector of size 1 * vector.dim().
     */
    explicit NPMatrix(const NVector &u);

    /**
     *
     * @return a n x p matrix constructed using a NVector having u.dim() = n * p
     */
    NPMatrix(const NVector &u, ul_t n, ul_t p = 0);

    /**
     *
     * @return a n x p matrix constructed using a std::vector<NVector>. All the vectors must have the same dimension.
     * They represent the rows of the matrix.
     */

    explicit NPMatrix(const vector<NVector> &vectors);



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

    /**
     *
     * @return true if n = p.
     */
    bool isSquare() const;


    // GETTERS

    ul_t n() const;

    ul_t p() const;

    /**
     *
     * @return return the ith row Ri of (resp. the jth col Cj) the matrix as a NVector.
     */
    NVector row(ul_t i) const;

    NVector col(ul_t j) const;

    /**
     *
     * @param i1/j1 start index of rows/cols
     * @param i2/j2 end index i2/j2 >= i1/j1 of rows/cols
     * @return the rows/cols of the matrix in the form of std::vector<NVector>.
     *          -rows()/cols() return all the rows/cols.
     *          -rows(i1)/cols(j1) returns the rows [Ri1, R(i1+1),..., R(n-1)]/ cols [Rj1, R(j1+1),..., C(p-1)]
     *          -rows(i1, i2)/cols(j1, j2) returns the rows [Ri1, R(i1+1),..., Ri2]/ cols [Cj1, C(j1+1),..., Cj2]
     */
    std::vector<NVector> rows(ul_t i1 = 0, ul_t i2 = MAX_SIZE) const;

    std::vector<NVector> cols(ul_t j1 = 0, ul_t j2 = MAX_SIZE) const;


    // SETTERS

    /**
     *
     * @param u row/col seen as NVector. The dimension of the vector must be equal to the number of cols/rows
     * @param i1/j1 index of row/col to set
     */
    void setRow(const NVector &u, ul_t i1);


    void setCol(const NVector &u, ul_t j1);

    /**
     *
     * @param vectors : std::vector of NVector representing rows/cols to set on the matrix.
     *                  - The length of each row/col must be inferior or equal to the number of cols/rows.
     *                  - The total number of rows/cols must be inferior or equal to the number of rows/cols.
     * @param i1/j1 :   start index to set row/col. If i1/j1 + vectors.size() > n/p Then the algorithm truncate the
     *                  array of NVector.
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
    void setRows(const std::vector<NVector> &vectors, ul_t i1 = 0);

    void setCols(const std::vector<NVector> &vectors, ul_t j1 = 0);




    // MANIPULATORS

    // SWAP

    /**
     *
     * @param i1/j1 first row/col indices to swap
     * @param i2/j2 second row/col indices to swap
     * @description : Swap Ai1j1 and Ai2j2.
     */
    void swap(ul_t i1, ul_t j1, ul_t i2, ul_t j2);

    /**
     *
     * @param i1/j1 first row/col indices to swap
     * @param i2/j2 second row/col indices to swap
     * @description : Swap Ri1/Cj1 and Ri2/Cj2.
     */
    void swapRow(ul_t i1, ul_t i2);

    void swapCol(ul_t j1, ul_t j2);


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
    void shiftRow(ul_t i, long iterations = 1);

    void shiftCol(ul_t j, long iterations = 1);

    // TRANSPOSED

    NPMatrix transposed();

    // ALGEBRA

    /**
     * @return Returns the shifted matrix m1 | m2 which is the matrix obtained after concatenation of m1 columns
     * and m2 columns. m1 and m2 must have the same number of rows.
     */
    NPMatrix shifted(const NPMatrix &m) const;


    /**
     * @description :   Apply Gauss Jordan elimination on matrix to calculate inverse for non square matrix.
     *                  To perform this, shift the matrix you want to invert than apply this function.
     */
    void reduce();


    // OPERATORS

    // ALGEBRAICAL OPERATORS

    /**
     * @return this + m where + is usual addition for matrices. The matrices must have the length.
     */
    NPMatrix operator+(const NPMatrix &m) const;

    /**
     * @return m1 - m2 where - is substraction based on + for matrices. The matrices must have the length.
     */
    NPMatrix operator-(const NPMatrix &m) const;

    /**
     * @return the usual opposite of the matrix -m.
     */
    NPMatrix operator-() const;

    /**
     *
     * @return s * m where * is usual scalar multiplication
     */
    friend NPMatrix operator*(double s, const NPMatrix &m);

    friend NPMatrix operator*(const NPMatrix &m, double s);

    /**
     * @return  m1 * m2 where * is usual matrix multiplication. The matrices must have the length.
     *          Natural O(n3) matrix product is used.
     */
    NPMatrix operator*(const NPMatrix &m) const;

    /**
     *
     * @return  m * v where * is usual matrix vector product (linear mapping). The number of rows of m must
     *          be equal to the dimension of v. Natural O(n2) linear mapping is used.
     */
    NVector operator*(const NVector &v) const;

    /**
     *
     * @return (1 / s) * m
     */
    NPMatrix operator/(double s) const;

    // SCALAR PRODUCT BASED OPERATIONS

    friend double operator|(const NPMatrix &m1, const NPMatrix &m2);

    friend double operator!(const NPMatrix &m);

    friend double operator/(const NPMatrix &m1, const NPMatrix &m2);

    // COMPOUND OPERATORS

    NPMatrix &operator+=(const NPMatrix &m);

    NPMatrix &operator-=(const NPMatrix &m);

    NPMatrix &operator*=(const NPMatrix &m);

    NPMatrix &operator*=(double s) override;

    NPMatrix &operator/=(double s) override;

    // BI-DIMENSIONAL ACCESSORS

    /**
     *
     * @return component ij of matrix. Operator can be used to read/write values.
     */
    double &operator()(ul_t i, ul_t j);

    double operator()(ul_t i, ul_t j) const;

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
     * Operations on a sub matrix can be applied this way matrix(i1, j1, i2, j2).shift(0, 1)
     * See unit tests for mor details.
     */
    NPMatrix operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const;

    NPMatrix &operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2);

    // AFFECTATION

    NPMatrix &operator=(const NPMatrix &m);

    NPMatrix &operator=(const string &str);

    // COMPARAISON OPERATORS

    friend bool operator==(const NPMatrix &m1, const NPMatrix &m2);

    friend bool operator!=(const NPMatrix &m1, const NPMatrix &m2);

    // STATIC FUNCTIONS

    /**
     *
     * @return zero nxp matrix, ie. filled with 0.
     */
    static NPMatrix zeros(ul_t n, ul_t p = 0);

    /**
     *
     * @return nxp matrix filled with 1
     */
    static NPMatrix ones(ul_t n, ul_t p = 0);

    /**
     * @param i row where to put 1.
     * @param j col where to put 1.
     *
     * @return canonical matrices Eij  of Mnp(R) which contains 1 in position ij and 0 elsewhere.
     */
    static NPMatrix canonical(ul_t i, ul_t j, ul_t n, ul_t p = 0);

protected:

    // MANIPULATORS

    void swap(ElementEnum element, ul_t k1, ul_t k2);

    void shift(ElementEnum element, ul_t k, long iterations);

    // MAX/MIN

    ul_t maxAbsIndex(ElementEnum element, ul_t k, ul_t r) const;

    // MAX / MIN

    ul_t maxAbsIndexRow(ul_t i, ul_t r = 0) const;

    ul_t maxAbsIndexCol(ul_t j, ul_t r = 0) const;

    // ALGEBRAICAL OPERATIONS

    void vectorProduct(NVector &u) const;

    virtual void matrixProduct(const NPMatrix &m);

    // OPERATIONS

    // CHARACTERIZATION

    bool isValidRowIndex(ul_t i) const;

    bool isValidColIndex(ul_t j) const;

    bool isValidIndex(ul_t i, ul_t j) const;

    bool isBetweenI12(ul_t i) const;

    bool isBetweenJ12(ul_t j) const;

    bool isCompatible(const NVector &u) const;

    bool isCompatible(const NPMatrix &u) const;

    bool hasSameSize(const NPMatrix &m) const;

    bool hasDefaultBrowseIndices() const override;

    void setDefaultBrowseIndices() const override;

    // AFFECTATION

    virtual void copy(const NPMatrix &m);

    void parse(const string &str) override;

    // INDEX GETTERS

    ul_t getVectorIndex(ul_t i, ul_t j) const;

    ul_t getRowFromVectorIndex(ul_t k) const;

    ul_t getColFromVectorIndex(ul_t k) const;

    // SUB-MATRICES

    NPMatrix subMatrix(ul_t i1 = 0, ul_t j1 = MAX_SIZE,
                       ul_t i2 = 0, ul_t j2 = MAX_SIZE) const;

    void setSubMatrix(const NPMatrix &m);

    // SIZE

    ul_t _n;

    ul_t _p;

    // BROWSE INDICES

    mutable ul_t _i1;

    mutable ul_t _j1;

    mutable ul_t _i2;

    mutable ul_t _j2;
};


#endif //MATHTOOLKIT_NPMATRIX_H
