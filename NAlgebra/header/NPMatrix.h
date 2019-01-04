/**
 * @class          : NPMatrix
 * @date           : 04/05/2018
 * @author         : samiBendou
 * @description    : A NPMatrix<T> inherits from NVector<T>. It's a representation of matrices of arbitrary
 *                   size in a tempate field T (reals, complex, modular arithemics...).
 *                   Over this file we will use the following definitions :
 *
 *                      - n : Number of Rows
 *                      - p : Number of Columns
 *                      - i : Row Index between 0 <= i < n
 *                      - j : Column Index 0 <= j < p
 *                      - k, l : either compound index or underlying std::vector array index.
 *                      - A/m : This NPMatrix. the components of the matrix in a certain base are noted Aij.
 *                      - R/C : Rows/Columns of A
 *
 *                   The matrix components are stored in a linear form using the index transformation k = p * i + j.
 *                   The underlying std::vector is represented as t[p * i + j].
 *                   The underlying NVector<T> is (A00, A01, ..., A0(P - 1), A10, ..., A1(P - 1), ..., A(N-1)0, ...).
 *
 *                   Featuring algebraical operations such as matrix product, linear map, gauss jordan elimination.
 *                   setters & getters, swappers and classic matrix generators such as ones, zeros...
 *
 *                   The LU decomposition is stored as a property if the matrix is square. It is auto-updated only when needed.
 *                   It allow to reduce complexity to get inverse or determinant. Precisely the LU decomposition is
 *                   represented by :

 *                      -a : is matrix A = L * U where PA = LU = this. a points to the A NMatrix or points to nullptr if
 *                           the matrix has never calculated LU decomposition or if the decomposition failed.
 *                      -perm : permutation vector P such as PA = LU. Represented as ul_t array.
 *
 *                  The *a object never is protected and pointer a->a always points to nullptr (no infinite recursion).
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */


#ifndef MATHTOOLKIT_NPMATRIX_H
#define MATHTOOLKIT_NPMATRIX_H

#include "thirdparty.h"
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
    explicit NPMatrix(ul_t n = 0, ul_t p = 0) : NPMatrix(NVector<T>(n * pIfNotNull(n, p)), n, pIfNotNull(n, p)) {}

    /**
     *
     * @return a n x p matrix constructed using a bi-dimensional std::vector such as Aij = data[i][j]. all the data[i]
     * must have the same length. They represent the rows of A matrix.
     */
    NPMatrix(const vector<vector<T> > &data) : NPMatrix(NVector<T>(data.size() * data[0].size()), data.size(),
                                                        data[0].size()) {
        copy(data);
    };

    NPMatrix(const NPMatrix<T> &m) : NPMatrix(NVector<T>(0), 0, 0) {
        copy(m);
    };

    NPMatrix(initializer_list<initializer_list<T>> list) : NPMatrix(vector<vector<T>>(list.begin(), list.end())) {}

    /**
     *
     * @return a n rows matrix constructed using a std::vector of size 1 * vector.dim().
     */
    explicit NPMatrix(const NVector<T> &u, ul_t n = 1) : NPMatrix(u, n, u.dim() / n) {}

    /**
     *
     * @return a n x p matrix constructed using a std::vector<NVector<T> >. All the vectors must have the same dimension.
     * They represent the rows of the matrix.
     */

    explicit NPMatrix(const vector<NVector<T> > &vectors) : NPMatrix(
            vector<vector<T>>(vectors.begin(), vectors.end())) {}

    ~NPMatrix() { lupClear(); }


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
    inline bool isSquare() const {
        bool cond = _j2 - _j1 == _i2 - _i1;
        setDefaultBrowseIndices();
        return cond;
    }

    bool isUpper() const;

    bool isLower() const;

    bool isDiagonal() const;

    // GETTERS

    inline ul_t n() const {
        auto res = _i2 - _i1 + 1;
        setDefaultBrowseIndices();
        return res;
    }

    inline ul_t p() const {
        auto res = _j2 - _j1 + 1;
        setDefaultBrowseIndices();
        return res;
    }

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
    NPMatrix<T> &setRow(const NVector<T> &u, ul_t i1);


    NPMatrix<T> &setCol(const NVector<T> &u, ul_t j1);

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
    NPMatrix<T> &setRows(const std::vector<NVector<T> > &vectors, ul_t i1 = 0);

    NPMatrix<T> &setCols(const std::vector<NVector<T> > &vectors, ul_t j1 = 0);




    // MANIPULATORS

    // SWAP

    /**
     *
     * @param i1/j1 first row/col indices to swap
     * @param i2/j2 second row/col indices to swap
     * @description : Swap Ai1j1 and Ai2j2.
     */
    inline NPMatrix<T> &swap(ul_t i1, ul_t j1, ul_t i2, ul_t j2) {
        assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));

        NVector<T>::swap(vectorIndex(i1, j1), vectorIndex(i2, j2));
        lupClear();
        return *this;
    }

    /**
     *
     * @param i1/j1 first row/col indices to swap
     * @param i2/j2 second row/col indices to swap
     * @description : Swap Ri1/Cj1 and Ri2/Cj2.
     */
    inline NPMatrix<T> &swapRow(ul_t i1, ul_t i2) {
        return swap(Row, i1, i2);
    }

    inline NPMatrix<T> &swapCol(ul_t j1, ul_t j2) {
        return swap(Col, j1, j2);
    }


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
    inline NPMatrix<T> &shiftRow(ul_t i, long iterations = 1) {
        return shift(Row, i, iterations);
    }

    inline NPMatrix<T> &shiftCol(ul_t j, long iterations = 1) {
        return shift(Col, j, iterations);
    }

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

    inline friend NPMatrix<T> operator+(NPMatrix<T> a, const NPMatrix<T> &b) {
        a += b;
        return a;
    }

    inline friend NPMatrix<T> operator-(NPMatrix<T> a, const NPMatrix<T> &b) {
        a -= b;
        return a;
    }

    inline friend NPMatrix<T> operator-(NPMatrix<T> m) {
        m.opp();
        return m;
    }

    inline friend NPMatrix<T> operator*(T s, NPMatrix<T> m) {
        m *= s;
        return m;
    }

    inline friend NPMatrix<T> operator*(NPMatrix<T> m, T s) { return s * m; }

    /**
     * @return  m1 * m2 where * is usual matrix multiplication. The matrices must have the length.
     *          Natural O(n3) matrix product is used.
     */

    inline friend NPMatrix<T> operator*(NPMatrix<T> a, const NPMatrix<T> &b) {
        a *= (&a != &b ? b : a);
        return a;
    }

    /**
     *
     * @return  m * v where * is usual matrix vector product (linear mapping). The number of rows of m must
     *          be equal to the dimension of v. Natural O(n2) linear mapping is used.
     */
    inline friend NVector<T> operator*(const NPMatrix<T> &m, NVector<T> v) {
        m.vectorProduct(v);
        return v;
    }

    /**
     *
     * @return (1 / s) * m
     */
    inline friend NPMatrix<T> operator/(NPMatrix<T> m, T s) {
        m /= s;
        return m;
    }

    /**
     *
     * @param m matrix to exponentiate.
     * @param exp long integer exponent. If exp < 0 we calculate the power of the inverse matrix m^-1 (O(n3)).
     * @return m^exp using fast exponentiation algorithm.
     */
    inline friend NPMatrix<T> operator^(NPMatrix<T> m, long exp) {
        m ^= exp;
        return m;
    }

    /**
     * @param m matrix of the equation system.
     * @param v second member of the equation system.
     * @return the solution of m * x = v by inverting the m matrix.
     */
    inline friend NVector<T> operator%(const NPMatrix<T> &m, NVector<T> v) {
        v %= m;
        return v;
    }


    // SCALAR PRODUCT BASED OPERATIONS

    friend T operator|(const NPMatrix<T> &a, const NPMatrix<T> &b) {
        NVector<T> sub_a{a(a._i1, a._j1, a._i2, a._j2)}, sub_b{b(b._i1, b._j1, b._i2, b._j2)};
        auto res = sub_a | sub_b;

        a.setDefaultBrowseIndices();
        b.setDefaultBrowseIndices();
        return res;
    }

    friend T operator!(const NPMatrix<T> &m) { return sqrt(m | m); }

    friend T operator/(const NPMatrix<T> &a, const NPMatrix<T> &b) { return !(a - b); }

    // COMPOUND OPERATORS

    inline NPMatrix<T> &operator+=(const NPMatrix<T> &m) { return add(m); }

    inline NPMatrix<T> &operator-=(const NPMatrix<T> &m) { return sub(m); }

    inline NPMatrix<T> &operator*=(const NPMatrix<T> &m) {
        matrixProduct(m);
        setDefaultBrowseIndices();
        m.setDefaultBrowseIndices();
        return *this;
    }

    inline NPMatrix<T> &operator*=(T s) override { return prod(s); }

    inline friend NVector<T> &operator*=(NVector<T> &u, const NPMatrix<T> &m) { return m.vectorProduct(u); }

    inline NPMatrix<T> &operator/=(T s) override { return div(s); }

    inline NPMatrix<T> &operator^=(long exp) { return pow(exp); }

    inline friend NVector<T> &operator%=(NVector<T> &u, const NPMatrix<T> &m) { return m.solve(u); }

    // BI-DIMENSIONAL ACCESSORS

    /**
     *
     * @return component ij of matrix. Operator can be used to read/write values.
     */
    inline T &operator()(ul_t i, ul_t j) {
        assert(isValidIndex(i, j));
        return (*this)[vectorIndex(i, j)];
    }

    inline T operator()(ul_t i, ul_t j) const {
        assert(isValidIndex(i, j));
        return (*this).at(vectorIndex(i, j));
    }

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
    inline NPMatrix<T> operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const { return subMatrix(i1, j1, i2, j2); }

    NPMatrix<T> &operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2);

    // AFFECTATION

    inline NPMatrix<T> &operator=(const NPMatrix<T> &m) {
        return copy(m);
    }

    // COMPARAISON OPERATORS

    friend bool operator==(const NPMatrix<T> &a, const NPMatrix<T> &b) {
        bool res = a(a._i1, a._j1, a._i2, a._j2).isEqual(b(b._i1, b._j1, b._i2, b._j2));

        a.setDefaultBrowseIndices();
        b.setDefaultBrowseIndices();
        return res;
    }

    inline friend bool operator!=(const NPMatrix<T> &a, const NPMatrix<T> &b) { return !(a == b); }

    // STATIC FUNCTIONS

    /**
     *
     * @return zero nxp matrix, ie. filled with 0.
     */
    inline static NPMatrix<T> zeros(ul_t n, ul_t p = 0) {
        return NPMatrix<T>(NVector<T>::zeros(n * pIfNotNull(n, p)), n);
    }

    /**
     *
     * @return nxp matrix filled with 1
     */
    inline static NPMatrix<T> ones(ul_t n, ul_t p = 0) {
        return NPMatrix<T>(NVector<T>::ones(n * pIfNotNull(n, p)), n);
    }

    /**
     * @param i row where to put 1.
     * @param j col where to put 1.
     *
     * @return canonical matrices Eij of Mnp(R) which contains 1 in position ij and 0 elsewhere.
     */
    inline static NPMatrix<T> canonical(ul_t i, ul_t j, ul_t n, ul_t p = 0) {
        return NPMatrix<T>(NVector<T>::canonical(p * i + j, n * pIfNotNull(n, p)), n);
    }

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
    inline static NPMatrix<T> scalar(T s, ul_t n) { return s * NPMatrix<T>::eye(n); }

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
    static NPMatrix<T> nscalar(const std::vector<T> &scalars, ul_t n);

protected:

    explicit NPMatrix(const NVector<T> &u, ul_t n, ul_t p, ul_t i1 = 0, ul_t j1 = 0, ul_t i2 = 0, ul_t j2 = 0);

    // MANIPULATORS

    NPMatrix<T> &swap(ElementEnum element, ul_t k1, ul_t k2);

    NPMatrix<T> &shift(ElementEnum element, ul_t k, long iterations);

    // MAX/MIN

    ul_t maxAbsIndex(ElementEnum element, ul_t k, ul_t r) const;

    // MAX / MIN

    inline ul_t maxAbsIndexRow(ul_t i, ul_t r = 0) const { return maxAbsIndex(Row, i, r); }

    inline ul_t maxAbsIndexCol(ul_t j, ul_t r = 0) const { return maxAbsIndex(Col, j, r); }

    // ALGEBRAICAL OPERATIONS

    NVector<T> &vectorProduct(NVector<T> &u) const;

    NPMatrix<T> &matrixProduct(const NPMatrix<T> &m);

    inline NPMatrix<T> &add(const NPMatrix<T> &m) { return forEach(m, [](T &x, const T &y) { x += y; }); }

    inline NPMatrix<T> &sub(const NPMatrix<T> &m) { return forEach(m, [](T &x, const T &y) { x -= y; }); }

    inline NPMatrix<T> &opp() override { return prod(-1); }

    inline NPMatrix<T> &prod(T s) override { return forEach(s, [](T &x, T s) { x *= s; }); }

    inline NPMatrix<T> &div(T s) override { return forEach(s, [](T &x, T s) { x /= s; }); }

    NPMatrix<T> &pow(long n);

    void rPow(long n);

    NPMatrix<T> &inv();

    NVector<T> &solve(NVector<T> &u) const;

    // LUP MANAGEMENT

    void lupCopy() const;

    void lupUpdate() const;

    void lupClear() const;

    // MUTABLE VARIABLES MANAGEMENT

    inline NPMatrix<T> &clean() const {
        setDefaultBrowseIndices();
        lupClear();
        return const_cast<NPMatrix<T> &>(*this);
    }

    inline NPMatrix<T> &cleanBoth(const NPMatrix<T> &m) const {
        setDefaultBrowseIndices();
        m.setDefaultBrowseIndices();
        lupClear();
        return const_cast<NPMatrix<T> &>(*this);
    }

    // CHARACTERIZATION

    inline bool isValidRowIndex(ul_t i) const { return i < _n; }

    inline bool isValidColIndex(ul_t j) const { return j < _p; }

    inline bool isValidIndex(ul_t i, ul_t j) const { return (isValidRowIndex(i) && isValidColIndex(j)); }

    inline bool isBetweenI12(ul_t i) const { return i >= _i1 && i <= _i2; }

    inline bool isBetweenJ12(ul_t j) const { return j >= _j1 && j <= _j2; }

    inline static ul_t pIfNotNull(ul_t n, ul_t p) { return p > 0 ? p : n; }

    inline bool matchSizeForProduct(const NVector<T> &u) const { return u.dim() - 1 == _j2 - _j1; }

    inline bool matchSizeForProduct(const NPMatrix<T> &m) const { return m._i2 - m._i1 == _j2 - _j1; }

    inline bool hasSameSize(const NPMatrix<T> &m) const {
        return m._i2 - m._i1 == _i2 - _i1 && m._j2 - m._j1 == _j2 - _j1;
    }

    // SUB MATRIX INDICES MANAGEMENT

    bool hasDefaultBrowseIndices() const override;

    void setDefaultBrowseIndices() const override;

    // AFFECTATION

    NPMatrix<T> &copy(const NPMatrix<T> &m);

    NPMatrix<T> &copy(const vector<vector<T>> &data);

    // INDEX GETTERS

    inline ul_t vectorIndex(ul_t i, ul_t j) const { return _p * i + j; }

    inline ul_t getRowFromVectorIndex(ul_t k) const {
        assert(k < _n * _p);
        return k / _p;
    }

    inline ul_t getColFromVectorIndex(ul_t k) const {
        assert(k < _n * _p);
        return k % _p;
    }

    // SUB-MATRICES

    NPMatrix<T> subMatrix(ul_t i1 = 0, ul_t j1 = MAX_SIZE,
                          ul_t i2 = 0, ul_t j2 = MAX_SIZE) const;

    NPMatrix<T> &setSubMatrix(const NPMatrix<T> &m);

    // MANIPULATORS

    NPMatrix<T> &forEach(const NPMatrix<T> &m, const std::function<void(T &, const T &)> &binary_op);

    NPMatrix<T> &forEach(T s, const function<void(T &, T)> &binary_op) override;

    // SIZE

    ul_t _n{};

    ul_t _p{};

    // SUB MATRICES INDICES INDICES

    mutable ul_t _i1{};

    mutable ul_t _j1{};

    mutable ul_t _i2{};

    mutable ul_t _j2{};

    // LU STORAGE

    mutable NPMatrix<T> *_a;

    mutable std::vector<ul_t> *_perm{};
};

typedef NPMatrix<double> mat_t;
typedef NPMatrix<char> mat_char_t;
typedef NPMatrix<AESByte> mat_aes_t;
typedef NPMatrix<Pixel> mat_pix_t;

#endif //MATHTOOLKIT_NPMATRIX_H