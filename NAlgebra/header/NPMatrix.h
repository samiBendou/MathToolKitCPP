/**
 * @class          : NPMatrix
 * @date           : 04/05/2018
 * @author         : samiBendou
 * @description    : A NPMatrix<T> inherits from NVector<T>. It's a representation of a numerical matrices of arbitrary
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
 *                   The underlying NVector<T> is (A00, A01, ..., A0(P - 1), A10, ..., A1(P - 1), ..., A(N-1)0, ...).
 *
 *                   Featuring algebraical operations such as matrix product, linear map, gauss jordan elimination.
 *                   setters & getters, swappers and classic matrix generators such as ones, zeros...
 *
 *                   The LU decomposition is stored as property if the matrix is square. It is auto-updated only on need.
 *                   It allow to reduce complexity to get inverse or determinant. Precisely the LU decomposition is
 *                   represented by :

 *                      -a : is matrix A = L * U where PA = LU = this. a points to the A NMatrix or points to nullptr if
 *                           the matrix has never calculated LU decomposition or if the decomposition failed.
 *                      -permu : permutation vector P such as PA = LU. Represented as ul_t array.
 *
 *                  The *a object never is protected and pointer m->a always points to nullptr.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */


#ifndef MATHTOOLKIT_NPMATRIX_H
#define MATHTOOLKIT_NPMATRIX_H


#include <NVector.h>

using namespace std;

enum ElementEnum {
    Row, Col
};

template<typename T>
class NPMatrix : public NVector<T> {

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
    explicit NPMatrix(const vector<vector<T> > &data);

    NPMatrix(const NPMatrix<T> &m);

    /**
     *
     * @param str an array of string containing the rows of the matrix in a form like "|0 2 3|".
     * @details initialize a NPMatrix<T> by parsing a string representing matrix rows. Use the following
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
    explicit NPMatrix(const NVector<T> &u);

    /**
     *
     * @return a n x p matrix constructed using a NVector<T> having u.dim() = n * p
     */
    NPMatrix(const NVector<T> &u, ul_t n, ul_t p = 0);

    /**
     *
     * @return a n x p matrix constructed using a std::vector<NVector<T> >. All the vectors must have the same dimension.
     * They represent the rows of the matrix.
     */

    explicit NPMatrix(const vector<NVector<T> > &vectors);

    ~NPMatrix();


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
     * @return true if n = p.
     */
    bool isSquare() const;

    bool isUpper() const;

    bool isLower() const;

    bool isDiagonal() const;

    // GETTERS

    ul_t n() const;

    ul_t p() const;

    /**
     *
     * @return return the ith row Ri of (resp. the jth col Cj) the matrix as a NVector<T>.
     */
    NVector<T> row(ul_t i) const;

    NVector<T> col(ul_t j) const;

    /**
     *
     * @param i1/j1 start index of rows/cols
     * @param i2/j2 end index i2/j2 >= i1/j1 of rows/cols
     * @return the rows/cols of the matrix in the form of std::vector<NVector<T> >.
     *          -rows()/cols() return all the rows/cols.
     *          -rows(i1)/cols(j1) returns the rows [Ri1, R(i1+1),..., R(n-1)]/ cols [Rj1, R(j1+1),..., C(p-1)]
     *          -rows(i1, i2)/cols(j1, j2) returns the rows [Ri1, R(i1+1),..., Ri2]/ cols [Cj1, C(j1+1),..., Cj2]
     */
    std::vector<NVector<T> > rows(ul_t i1 = 0, ul_t i2 = MAX_SIZE) const;

    std::vector<NVector<T> > cols(ul_t j1 = 0, ul_t j2 = MAX_SIZE) const;

    /**
     *
     * @return upper part of this matrix as a upper matrix.
     */
    NPMatrix<T> upper() const;

    /**
     *
     * @return lower part of this matrix as a lower matrix.
     */
    NPMatrix<T> lower() const;

    /**
     *
     * @return L/U matrix of LU decomposition of this matrix
     */
    NPMatrix<T> lupL() const;

    NPMatrix<T> lupU() const;


    // SETTERS

    /**
     *
     * @param u row/col seen as NVector<T>. The dimension of the vector must be equal to the number of cols/rows
     * @param i1/j1 index of row/col to set
     */
    void setRow(const NVector<T> &u, ul_t i1);


    void setCol(const NVector<T> &u, ul_t j1);

    /**
     *
     * @param vectors : std::vector of NVector<T> representing rows/cols to set on the matrix.
     *                  - The length of each row/col must be inferior or equal to the number of cols/rows.
     *                  - The total number of rows/cols must be inferior or equal to the number of rows/cols.
     * @param i1/j1 :   start index to set row/col. If i1/j1 + vectors.size() > n/p Then the algorithm truncate the
     *                  array of NVector<T>.
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
    void setRows(const std::vector<NVector<T> > &vectors, ul_t i1 = 0);

    void setCols(const std::vector<NVector<T> > &vectors, ul_t j1 = 0);




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

    // ALGEBRA

    NPMatrix<T> transposed() const;

    /**
     *
     * @return trace of this matrix A00 + A11 + ... + A(n-1)(n-1)
     */
    T trace() const;

    /**
     * @return Returns the shifted matrix m1 | m2 which is the matrix obtained after concatenation of m1 columns
     * and m2 columns. m1 and m2 must have the same number of rows.
     */
    NPMatrix<T> shifted(const NPMatrix<T> &m) const;

    /**
     * @description :   Apply Gauss Jordan elimination on matrix to calculate inverse for non square matrix.
     *                  To perform this, shift the matrix you want to invert than apply this function.
     */
    void reduce();

    /**
     *
     * @return determinant of this matrix det(A). Using the LU decomposition O(n).
     */
    T det() const;


    // OPERATORS

    // ALGEBRAICAL OPERATORS

    NPMatrix<T> operator+(const NPMatrix<T> &m) const;

    NPMatrix<T> operator-(const NPMatrix<T> &m) const;

    NPMatrix<T> operator-() const;

    friend NPMatrix<T> operator*(T s, const NPMatrix<T> &m) {
        NPMatrix<T> res{m};
        res *= s;
        return res;
    }

    friend NPMatrix<T> operator*(const NPMatrix<T> &m, T s) {
        return s * m;
    }

    /**
     * @return  m1 * m2 where * is usual matrix multiplication. The matrices must have the length.
     *          Natural O(n3) matrix product is used.
     */
    NPMatrix<T> operator*(const NPMatrix<T> &m) const;

    /**
     *
     * @return  m * v where * is usual matrix vector product (linear mapping). The number of rows of m must
     *          be equal to the dimension of v. Natural O(n2) linear mapping is used.
     */
    NVector<T> operator*(const NVector<T> &v) const;

    /**
     *
     * @return (1 / s) * m
     */
    NPMatrix<T> operator/(T s) const;

    /**
     *
     * @param m matrix to exponentiate.
     * @param exp long integer exponent. If exp < 0 we calculate the power of the inverse matrix m^-1 (O(n3)).
     * @return m^exp using fast exponentiation algorithm.
     */
    friend NPMatrix<T> operator^(const NPMatrix<T> &m, long exp) {
        NPMatrix<T> res{m};
        res ^= exp;
        return res;
    }

    /**
     * @param m matrix of the equation system.
     * @param v second member of the equation system.
     * @return the solution of m * x = v by inverting the m matrix.
     */
    friend NVector<T> operator%(NPMatrix<T> &m, const NVector<T> &v) {
        NVector<T> b{v};
        m.solve(b);
        m.setDefaultBrowseIndices();
        return b;
    }


    // SCALAR PRODUCT BASED OPERATIONS

    friend T operator|(const NPMatrix<T> &m1, const NPMatrix<T> &m2) {
        NVector<T> sub_m1 = m1(m1._i1, m1._j1, m1._i2, m1._j2);
        NVector<T> sub_m2 = m2(m2._i1, m2._j1, m2._i2, m2._j2);
        auto res = sub_m1 | sub_m2;

        m1.setDefaultBrowseIndices();
        m2.setDefaultBrowseIndices();
        return res;
    }

    friend T operator!(const NPMatrix<T> &m) {
        return sqrt(m | m);
    }

    friend T operator/(const NPMatrix<T> &m1, const NPMatrix<T> &m2) {
        return !(m1 - m2);
    }

    // COMPOUND OPERATORS

    NPMatrix<T> &operator+=(const NPMatrix<T> &m);

    NPMatrix<T> &operator-=(const NPMatrix<T> &m);

    NPMatrix<T> &operator*=(const NPMatrix<T> &m);

    NPMatrix<T> &operator*=(T s) override;

    NPMatrix<T> &operator/=(T s) override;

    NVector<T> &operator^=(long exp);

    // BI-DIMENSIONAL ACCESSORS

    /**
     *
     * @return component ij of matrix. Operator can be used to read/write values.
     */
    T &operator()(ul_t i, ul_t j);

    T operator()(ul_t i, ul_t j) const;

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
    NPMatrix<T> operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const;

    NPMatrix<T> &operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2);

    // AFFECTATION

    NPMatrix<T> &operator=(const NPMatrix<T> &m);

    NPMatrix<T> &operator=(const string &str);

    // COMPARAISON OPERATORS

    friend bool operator==(const NPMatrix<T> &m1, const NPMatrix<T> &m2) {
        bool res = m1(m1._i1, m1._j1, m1._i2, m1._j2).isEqual(m2(m2._i1, m2._j1, m2._i2, m2._j2));

        m1.setDefaultBrowseIndices();
        m2.setDefaultBrowseIndices();
        return res;
    }

    friend bool operator!=(const NPMatrix<T> &m1, const NPMatrix<T> &m2) {
        return !(m1 == m2);
    }

    // STATIC FUNCTIONS

    /**
     *
     * @return zero nxp matrix, ie. filled with 0.
     */
    static NPMatrix<T> zeros(ul_t n, ul_t p = 0);

    /**
     *
     * @return nxp matrix filled with 1
     */
    static NPMatrix<T> ones(ul_t n, ul_t p = 0);

    /**
     * @param i row where to put 1.
     * @param j col where to put 1.
     *
     * @return canonical matrices Eij  of Mnp(R) which contains 1 in position ij and 0 elsewhere.
     */
    static NPMatrix<T> canonical(ul_t i, ul_t j, ul_t n, ul_t p = 0);

    /**
     *
     * @param n size of the matrix
     * @return n-th order Identity matrix
     */
    static NPMatrix<T> eye(ul_t n);

    /**
     *
     * @param data values of diagonal [d0, d1, ..., d(n-1)]
     * @param n size of the matrix
     * @return Returns diagonal n-th order diagonal matrix filled with data array
     */
    static NPMatrix<T> diag(const std::vector<T> &data, ul_t n);


    /**
     *
     * @return a scalar n-th order matrix with s value. This is a diagonal matrix filled with s.
     */
    static NPMatrix<T> scalar(T s, ul_t n);

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
    static NPMatrix<T> ndiag(const std::vector<NVector<T> > &data);


    /**
     *
     * @param scalars array of scalars values to fill diagonals [s0, s1, ..., sq]
     * @param n size of the matrix
     * @return  a n-scalar Matrix filled with values. If values.length = 2, the matrix is tri-diagonal.
     *          Center diagonal is filled with s1 and the other diagonal are filled with s0.
     */
    static NPMatrix<T> nscalar(const std::vector<T> &scalars, const ul_t n);

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

    void vectorProduct(NVector<T> &u) const;

    virtual void matrixProduct(const NPMatrix<T> &m);

    void add(const NPMatrix<T> &m);

    void sub(const NPMatrix<T> &m);

    void opp() override;

    void prod(T s) override;

    void div(T s) override;

    void pow(long n);

    void rPow(long n);

    void inv();

    void solve(NVector<T> &vector);

    // LUP MANAGEMENT

    void lupCopy() const;

    void lupUpdate() const;

    void lupClear() const;

    // CHARACTERIZATION

    bool isValidRowIndex(ul_t i) const;

    bool isValidColIndex(ul_t j) const;

    bool isValidIndex(ul_t i, ul_t j) const;

    bool isBetweenI12(ul_t i) const;

    bool isBetweenJ12(ul_t j) const;

    bool isCompatible(const NVector<T> &u) const;

    bool isCompatible(const NPMatrix<T> &u) const;

    bool hasSameSize(const NPMatrix<T> &m) const;

    bool hasDefaultBrowseIndices() const override;

    void setDefaultBrowseIndices() const override;

    // AFFECTATION

    virtual void copy(const NPMatrix<T> &m);

    void parse(const string &str) override;

    // INDEX GETTERS

    ul_t vectorIndex(ul_t i, ul_t j) const;

    ul_t getRowFromVectorIndex(ul_t k) const;

    ul_t getColFromVectorIndex(ul_t k) const;

    // SUB-MATRICES

    NPMatrix<T> subMatrix(ul_t i1 = 0, ul_t j1 = MAX_SIZE,
                          ul_t i2 = 0, ul_t j2 = MAX_SIZE) const;

    void setSubMatrix(const NPMatrix<T> &m);

    // SIZE

    ul_t _n;

    ul_t _p;

    // BROWSE INDICES

    mutable ul_t _i1;

    mutable ul_t _j1;

    mutable ul_t _i2;

    mutable ul_t _j2;

    // LU STORAGE

    mutable NPMatrix<T> *_a;

    mutable std::vector<ul_t> *_perm;

};

typedef NPMatrix<double> mat_t;
typedef NPMatrix<char> mat_char_t;
typedef NPMatrix<AESByte> mat_aes_t;

#endif //MATHTOOLKIT_NPMATRIX_H
