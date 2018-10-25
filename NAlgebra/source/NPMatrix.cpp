//
// Created by Sami Dahoux on 04/05/2018.
//

#include <NPMatrix.h>

using namespace std;

template<typename T>
NPMatrix<T>::NPMatrix(ul_t n, ul_t p) : NVector<T>(n * ((p > 0) ? p : n)),
                                        _n(n), _p((p > 0) ? p : n),
                                        _i1(0), _j1(0), _i2(0), _j2(0),
                                        _a(nullptr), _perm(nullptr) {

    setDefaultBrowseIndices();
}

template<typename T>
NPMatrix<T>::NPMatrix(const vector<vector<T> > &data) : NVector<T>((data.size() * data[0].size())),
                                                        _n(data.size()), _p(data[0].size()),
                                                        _i1(0), _j1(0), _i2(0), _j2(0),
                                                        _a(nullptr), _perm(nullptr) {

    for (ul_t i = 0; i < _n; ++i) {

        assert(data[i].size() == data[0].size());

        for (ul_t j = 0; j < _p; ++j) {
            (*this)(i, j) = data[i][j];
        }
    }
    setDefaultBrowseIndices();
}

template<typename T>
NPMatrix<T>::NPMatrix(const NPMatrix<T> &m) : NVector<T>(0),
                                              _n(0), _p(0),
                                              _i1(0), _j1(0), _i2(0), _j2(0),
                                              _a(nullptr), _perm(nullptr) {
    copy(m);
}

template<typename T>
NPMatrix<T>::NPMatrix(const string &str) : NVector<T>(0),
                                           _n(0), _p(0),
                                           _i1(0), _j1(0), _i2(0), _j2(0),
                                           _a(nullptr), _perm(nullptr) {

    parse(str);
    setDefaultBrowseIndices();

}

template<typename T>
NPMatrix<T>::NPMatrix(const NVector<T> &u) : NVector<T>(u),
                                             _n(1), _p(u.dim()),
                                             _i1(0), _j1(0), _i2(0), _j2(0),
                                             _a(nullptr), _perm(nullptr) {

    setDefaultBrowseIndices();
}

template<typename T>
NPMatrix<T>::NPMatrix(const NVector<T> &u, ul_t n, ul_t p) : NVector<T>(u),
                                                             _n(n), _p((p > 0) ? p : n),
                                                             _i1(0), _j1(0), _i2(0), _j2(0),
                                                             _a(nullptr), _perm(nullptr) {

    assert(this->dim() == _n * _p);
    setDefaultBrowseIndices();
}

template<typename T>
NPMatrix<T>::NPMatrix(const vector<NVector<T> > &vectors) : NVector<T>((vectors.size() * vectors[0].dim())),
                                                            _n(vectors.size()), _p(vectors[0].dim()),
                                                            _i1(0), _j1(0), _i2(0), _j2(0),
                                                            _a(nullptr), _perm(nullptr) {

    for (ul_t i = 0; i < _n; ++i) {

        assert(vectors[i].dim() == vectors[0].dim());

        setRow(vectors[i], i);
    }
    setDefaultBrowseIndices();
}

template<typename T>
NPMatrix<T>::~NPMatrix() {
    lupClear();
}


template<typename T>
string NPMatrix<T>::str() const {
    stringstream stream;

    for (ul_t i = _i1; i <= _i2; ++i) {
        stream << "\n";
        stream << row(i)(_j1, _j2);
    }
    setDefaultBrowseIndices();
    return stream.str();
}




// CHARACTERIZATION


template<typename T>
bool NPMatrix<T>::isSquare() const {
    return _j2 - _j1 == _i2 - _i1;
}

template<typename T>
bool NPMatrix<T>::isUpper() const {
    for (ul_t i = _i1; i <= _i2; ++i) {
        for (ul_t j = _j1; j <= i; ++j) {
            if (abs((*this)(i, j)) > EPSILON) {
                setDefaultBrowseIndices();
                return false;
            }
        }
    }

    setDefaultBrowseIndices();

    return true;
}

template<typename T>
bool NPMatrix<T>::isLower() const {
    for (ul_t i = _i1; i <= _i2; ++i) {
        for (ul_t j = i + 1; j <= _j2; ++j) {
            if (abs((*this)(i, j)) > EPSILON) {
                setDefaultBrowseIndices();
                return false;
            }
        }
    }

    setDefaultBrowseIndices();

    return true;
}

template<typename T>
bool NPMatrix<T>::isDiagonal() const {
    for (ul_t i = _i1; i <= _i2; i++) {
        for (ul_t j = _j1; j <= _j2; j++) {
            if (i != j && abs((*this)(i, j)) > EPSILON) {
                setDefaultBrowseIndices();
                return false;
            }
        }
    }

    setDefaultBrowseIndices();

    return true;
}

// GETTERS

template<typename T>
ul_t NPMatrix<T>::n() const {
    auto res = _i2 - _i1 + 1;
    setDefaultBrowseIndices();
    return res;
}

template<typename T>
ul_t NPMatrix<T>::p() const {
    auto res = _j2 - _j1 + 1;
    setDefaultBrowseIndices();
    return res;
}

template<typename T>
NVector<T> NPMatrix<T>::row(ul_t i) const {
    assert(isValidRowIndex(i));

    vector<T> data{this->begin() + _p * i, this->begin() + _p * (i + 1)};
    return NVector<T>(data);
}

template<typename T>
NVector<T> NPMatrix<T>::col(ul_t j) const {
    assert(isValidColIndex(j));

    vector<T> data(_n);
    for (ul_t k = 0; k < _n; ++k) {
        data[k] = (*this)(k, j);
    }
    return NVector<T>(data);
}

template<typename T>
vector<NVector<T> > NPMatrix<T>::rows(ul_t i1, ul_t i2) const {

    auto end = i2 == MAX_SIZE ? _n - 1 : i2;

    assert(end >= i1 && isValidRowIndex(i1) && isValidRowIndex(end));

    vector<NVector<T> > rows(end - i1 + 1);
    for (auto i = i1; i <= end; ++i) {
        rows[i - i1] = row(i);
    }
    return rows;
}

template<typename T>
vector<NVector<T> > NPMatrix<T>::cols(ul_t j1, ul_t j2) const {

    auto end = j2 == MAX_SIZE ? _p - 1 : j2;

    assert(end >= j1 && isValidColIndex(j1) && isValidColIndex(end));

    vector<NVector<T> > cols(end - j1 + 1);
    for (auto j = j1; j <= end; ++j) {
        cols[j - j1] = col(j);
    }
    return cols;
}


template<typename T>
NPMatrix<T> NPMatrix<T>::upper() const {

    NPMatrix<T> upper = NPMatrix<T>::zeros(_i2 - _i1 + 1);
    for (ul_t i = _i1; i <= _i2; ++i) {
        for (ul_t j = i; j <= _j2; ++j)
            upper(i, j) = (*this)(i, j);
    }

    setDefaultBrowseIndices();
    return upper;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::lower() const {

    NPMatrix<T> lower = NPMatrix<T>::zeros(_i2 - _i1 + 1);
    for (ul_t i = _i1; i <= _i2; ++i) {
        for (ul_t j = _j1; j <= i; ++j)
            lower(i, j) = (*this)(i, j);
    }

    setDefaultBrowseIndices();
    return lower;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::lupL() const {
    if (_a == nullptr) { lupUpdate(); }

    assert(_a != nullptr);

    NPMatrix<T> l = _a->lower();
    for (ul_t i = 0; i < _a->_n; ++i) {
        l(i, i) = 1.0;
    }

    if (_a->_n != _n) {
        lupClear();
        setDefaultBrowseIndices();
    }
    return l;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::lupU() const {
    if (_a == nullptr) { lupUpdate(); }

    assert(_a != nullptr);

    NPMatrix<T> u = _a->upper();

    if (_a->_n != _n) {
        lupClear();
        setDefaultBrowseIndices();
    }
    return u;
}


// ROWS/COLS/SUB SETTERS


template<typename T>
void NPMatrix<T>::setRow(const NVector<T> &u, ul_t i1) {
    assert(u.dim() <= _p && isValidRowIndex(i1));

    std::copy(u.begin(), u.end(), this->begin() + _p * i1);
    lupClear();
}

template<typename T>
void NPMatrix<T>::setCol(const NVector<T> &u, ul_t j1) {
    assert(u.dim() <= _n && isValidColIndex(j1));

    for (ul_t i = 0; i < u.dim(); ++i) {
        (*this)(i, j1) = u(i);
    }
    lupClear();
}

template<typename T>
void NPMatrix<T>::setRows(const vector<NVector<T> > &vectors, ul_t i1) {
    ul_t size = (vectors.size() + i1 < _n) ? vectors.size() + i1 : _n;

    for (auto i = i1; i < size; ++i) {
        setRow(vectors[i - i1], i);
    }
    lupClear();
}

template<typename T>
void NPMatrix<T>::setCols(const vector<NVector<T> > &vectors, ul_t j1) {
    ul_t size = (vectors.size() + j1 <= _p) ? vectors.size() + j1 : _p;

    for (auto j = j1; j < size; ++j) {
        setCol(vectors[j - j1], j);
    }
    lupClear();
}


// MANIPULATORS

// SWAPS


template<typename T>
void NPMatrix<T>::swap(ul_t i1, ul_t j1, ul_t i2, ul_t j2) {
    assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));

    NVector<T>::swap(vectorIndex(i1, j1), vectorIndex(i2, j2));
    lupClear();
}

template<typename T>
void NPMatrix<T>::swapRow(ul_t i1, ul_t i2) {
    swap(Row, i1, i2);
    lupClear();
}

template<typename T>
void NPMatrix<T>::swapCol(ul_t j1, ul_t j2) {
    swap(Col, j1, j2);
    lupClear();
}


// SHIFTS


template<typename T>
void NPMatrix<T>::shiftRow(ul_t i, const long iterations) {
    shift(Row, i, iterations);
    lupClear();
}

template<typename T>
void NPMatrix<T>::shiftCol(ul_t j, const long iterations) {
    shift(Col, j, iterations);
    lupClear();
}

// TRANSPOSED


template<typename T>
NPMatrix<T> NPMatrix<T>::transposed() const {
    NPMatrix<T> temp{_j2 - _j1 + 1, _i2 - _i1 + 1};

    for (auto i = _i1; i <= _i2; ++i) {
        for (auto j = _j1; j <= _j2; ++j) {
            temp(j - _j1, i - _i1) = (*this)(i, j);
        }
    }
    setDefaultBrowseIndices();
    return temp;
}

template<typename T>
T NPMatrix<T>::trace() const {
    T trace = 0.0;
    for (ul_t i = _i1; i <= _i2; i++) {
        trace += (*this)(i, i);
    }
    setDefaultBrowseIndices();
    return trace;
}


// ALGEBRA


template<typename T>
NPMatrix<T> NPMatrix<T>::shifted(const NPMatrix<T> &m) const {
    NPMatrix<T> shifted = NPMatrix<T>::zeros(_n, m._p + _n);
    for (ul_t i = 0; i < _n; i++) {
        for (ul_t j = 0; j < _p; j++) {
            shifted(i, j) = (*this)(i, j);
        }

        for (auto j = _p; j < m._p + _p; j++) {
            shifted(i, j) = m(i, j - _p);
        }
    }
    return shifted;
}

template<typename T>
void NPMatrix<T>::reduce() {
    ul_t r = 0, k, i, j;
    NVector<T> spin;
    for (j = 0; j < floor(_p / 2); ++j) {

        k = maxAbsIndexCol(j, r);
        if (abs((*this)(k, j)) > EPSILON) {
            setRow(row(k) / (*this)(k, j), k);
            swapRow(k, r);

            spin = row(r);
            for (i = 0; i < _n; ++i) {
                if (i != r)
                    setRow(row(i) - (*this)(i, j) * spin, i);
            }
            r++;
        }
    }
    lupClear();
}

template<typename T>
T NPMatrix<T>::det() const {
    T det = 0.0;
    if (_a == nullptr) { lupUpdate(); }

    if (_a != nullptr) {
        det = (*_a)(0, 0);
        for (ul_t i = 1; i < _a->_n; i++) {
            det *= (*_a)(i, i);
        }
        det = (((*_perm)[_a->_n - 1] - (_a->_n - 1)) % 2 == 0) ? det : -det;

        if (_a->_n != _n) {
            lupClear();
        }
    }
    return det;
}

// OPERATORS

// ALGEBRAICAL OPERATORS

template<typename T>
NPMatrix<T> NPMatrix<T>::operator+(const NPMatrix<T> &matrix) const {
    NPMatrix<T> res{*this};
    res += matrix;
    return res;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::operator-(const NPMatrix<T> &matrix) const {
    NPMatrix<T> res{*this};
    res -= matrix;
    return res;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::operator*(const NPMatrix<T> &m) const {
    NPMatrix<T> res{*this};
    NPMatrix<T> sub_m{this != &m ? m : res};
    res *= sub_m;
    return res;
}

template<typename T>
NVector<T> NPMatrix<T>::operator*(const NVector<T> &v) const {
    NVector<T> res{v};
    vectorProduct(res);
    return res;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::operator/(T s) const {
    NPMatrix<T> res{*this};
    res /= s;
    return res;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::operator-() const {
    NPMatrix<T> res{*this};
    res.opp();
    return res;
}

// COMPOUND OPERATORS

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator+=(const NPMatrix<T> &m) {
    add(m);
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator-=(const NPMatrix<T> &m) {
    sub(m);
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator*=(const NPMatrix<T> &m) {
    matrixProduct(m);

    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator*=(T s) {
    prod(s);
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator/=(T s) {
    div(s);
    return *this;
}

template<typename T>
NVector<T> &NPMatrix<T>::operator^=(const long exp) {
    pow(exp);
    return *this;
}


// BI-DIMENSIONAL ACCESSORS

template<typename T>
T &NPMatrix<T>::operator()(ul_t i, ul_t j) {
    assert(isValidIndex(i, j));
    return (*this)[vectorIndex(i, j)];

}

template<typename T>
T NPMatrix<T>::operator()(ul_t i, ul_t j) const {
    assert(isValidIndex(i, j));
    return (*this).at(vectorIndex(i, j));
}

template<typename T>
NPMatrix<T> NPMatrix<T>::operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const {
    return subMatrix(i1, j1, i2, j2);
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) {
    assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));
    assert(i2 >= i1 && j2 >= j1);

    _i1 = i1;
    _j1 = j1;
    _i2 = i2;
    _j2 = j2;

    return *this;
}

// AFFECTATION

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator=(const NPMatrix<T> &m) {
    copy(m);
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator=(const string &str) {
    parse(str);
    return *this;
}

// STATIC FUNCTIONS

template<typename T>
NPMatrix<T> NPMatrix<T>::zeros(ul_t n, ul_t p) {
    p = (p > 0) ? p : n;
    return NPMatrix<T>(NVector<T>::zeros(n * p), n, p);
}

template<typename T>
NPMatrix<T> NPMatrix<T>::ones(ul_t n, ul_t p) {
    p = (p > 0) ? p : n;
    return NPMatrix<T>(NVector<T>::ones(n * p), n, p);
}

template<typename T>
NPMatrix<T> NPMatrix<T>::canonical(ul_t i, ul_t j, ul_t n, ul_t p) {
    p = (p > 0) ? p : n;
    return NPMatrix<T>(NVector<T>::canonical(p * i + j, n * p), n, p);
}

template<typename T>
NPMatrix<T> NPMatrix<T>::eye(ul_t n) {
    NPMatrix<T> eye = NPMatrix<T>::zeros(n);
    for (ul_t k = 0; k < eye.n(); ++k) {
        eye(k, k) = 1.0;
    }
    return eye;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::diag(const std::vector<T> &data, ul_t n) {
    NPMatrix<T> diag = NPMatrix<T>::zeros(n);
    for (ul_t k = 0; k < n; ++k) {
        diag(k, k) = data[k];
    }
    return diag;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::scalar(T s, ul_t n) {
    return s * NPMatrix<T>::eye(n);
}

//Returns a n-diagonal matrix filled with arr bi-dimensional array : arr[l] is the values of coefficients of the l-th
//diagonal from the left. arr[middle] is the values of coefficients on the diagonal.

template<typename T>
NPMatrix<T> NPMatrix<T>::ndiag(const std::vector<NVector<T>> &data) {
    const auto n = (long) data.size();
    const auto middle = (n - 1) / 2;
    const auto dim = data[middle].dim();
    NPMatrix<T> diag = NPMatrix<T>::zeros(dim);

    for (long l = -middle; l <= middle; l++) {
        for (ul_t k = 0; k < dim - abs(l); k++) {
            if (l < 0) {
                diag(k - l, k) = data[l + middle](k);
            } else {
                diag(k, k + l) = data[l + middle](k);
            }
        }
    }
    return diag;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::nscalar(const std::vector<T> &scalars, const ul_t n) {
    const auto scalarSize = (long) scalars.size();
    const long minSize = n - scalarSize;

    std::vector<NVector<T> > diags((ul_t) (2 * scalarSize - 1));
    ul_t size = 1;
    for (ul_t l = 0; l < scalarSize; l++) {
        diags[l] = NVector<T>::scalar(scalars[l], size + minSize);
        if (l > 0) {
            diags[l + scalarSize - 1] = NVector<T>::scalar(scalars[scalarSize - l - 1], n - size + 1);
        }
        size++;
    }
    return NPMatrix<T>::ndiag(diags);
}

// PROTECTED METHODS

// MANIPULATORS

template<typename T>
void NPMatrix<T>::swap(const ElementEnum element, ul_t k1, ul_t k2) {

    NVector<T> temp = (element == Row) ? NPMatrix<T>::row(k1) : col(k1);

    (element == Row) ? setRow(row(k2), k1) : setCol(col(k2), k1);
    (element == Row) ? setRow(temp, k2) : setCol(temp, k2);

    setDefaultBrowseIndices();
}

template<typename T>
void NPMatrix<T>::shift(const ElementEnum element, ul_t k, const long iterations) {

    assert(element == Row ? isBetweenI12(k + _i1) : isBetweenJ12(k + _j1));

    NVector<T> vector = (element == Row) ? row(k + _i1) : col(k + _j1);
    (element == Row) ? vector(_j1, _j2).shift(iterations) : vector(_i1, _i2).shift(iterations);
    (element == Row) ? setRow(vector, k + _i1) : setCol(vector, k + _j1);

    setDefaultBrowseIndices();
}

// MAX/MIN

template<typename T>
ul_t NPMatrix<T>::maxAbsIndex(const ElementEnum element, ul_t k, ul_t r) const {
    NVector<T> elem{(element == Row) ? row(k) : col(k)};
    NVector<T> vector;
    vector = elem(r, (element == Row) ? _p - 1 : _n - 1);
    return r + vector.maxAbsIndex();
}

template<typename T>
ul_t NPMatrix<T>::maxAbsIndexRow(ul_t i, ul_t r) const {
    return maxAbsIndex(Row, i, r);
}

template<typename T>
ul_t NPMatrix<T>::maxAbsIndexCol(ul_t j, ul_t r) const {
    return maxAbsIndex(Col, j, r);
}

// PRIVATE METHODS

// ALGEBRAICAL OPERATIONS

template<typename T>
void NPMatrix<T>::vectorProduct(NVector<T> &u) const {

    NVector<T> res = NVector<T>::zeros(u.dim());
    std::vector<NVector<T> > vector_rows = rows(_i1, _i2);

    assert(isCompatible(res));

    for (ul_t i = _i1; i <= _i2; ++i) {
        res(i - _i1) = vector_rows[i](_j1, _j2) | u;
    }
    u = res;

    setDefaultBrowseIndices();
}

template<typename T>
void NPMatrix<T>::matrixProduct(const NPMatrix<T> &m) {
    assert(isCompatible(m));
    assert(isSquare() || hasDefaultBrowseIndices());

    vector<NVector<T> > vector_rows = rows();
    vector<NVector<T> > vector_cols = m.cols();

    NPMatrix<T> res = NPMatrix<T>::zeros(_i2 - _i1 + 1, m._j2 - m._j1 + 1);

    for (ul_t i = _i1; i <= _i2; ++i) {
        for (ul_t j = m._j1; j <= m._j2; ++j) {
            res(i - _i1, j - m._j1) = vector_rows[i](_j1, _j2) | vector_cols[j](m._i1, m._i2);
        }
    }

    this->copy(res);
    lupClear();
}

// PRIVATE ALGEBRAICAL OPERATIONS

template<typename T>
void NPMatrix<T>::add(const NPMatrix<T> &m) {

    assert(hasSameSize(m));

    for (ul_t i = 0; i <= _i2 - _i1; ++i) {
        for (ul_t j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) += m(i + m._i1, j + m._j1);
        }
    }

    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
    lupClear();
}

template<typename T>
void NPMatrix<T>::sub(const NPMatrix<T> &m) {
    assert(hasSameSize(m));

    typename std::vector<T>::iterator begin, end;

    for (ul_t i = 0; i <= _i2 - _i1; ++i) {
        for (ul_t j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) -= m(i + m._i1, j + m._j1);
        }
    }

    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
    lupClear();
 }

template<typename T>
void NPMatrix<T>::opp() {

    for (ul_t i = 0; i <= _i2 - _i1; ++i) {
        for (ul_t j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) -= (*this)(i + _i1, j + _j1);
        }
    }

    setDefaultBrowseIndices();
    lupClear();
}


template<typename T>
void NPMatrix<T>::prod(T s) {
    for (ul_t i = 0; i <= _i2 - _i1; ++i) {
        for (ul_t j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) *= s;
        }
    }

    setDefaultBrowseIndices();
    lupClear();
}

template<typename T>
void NPMatrix<T>::div(T s) {
    for (ul_t i = 0; i <= _i2 - _i1; ++i) {
        for (ul_t j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) /= s;
        }
    }
    setDefaultBrowseIndices();
    lupClear();
}

template<typename T>
void NPMatrix<T>::pow(const long n) {
    if (n > 0) {
        rPow(n);
    } else if (n < 0) {
        inv();
        rPow(-n);
    } else {
        *this = NPMatrix<T>::eye(_i2 - _i1 + 1);
    }
    setDefaultBrowseIndices();
    lupClear();
}

template<typename T>
void NPMatrix<T>::rPow(const long n) {
    if (n > 1) {
        const NPMatrix<T> copy{this->subMatrix(_i1, _j1, _i2, _j2)};
        (*this)(_i1, _j1, _i2, _j2).matrixProduct(copy);
        if (n % 2 == 0) {
            rPow(n / 2);
        } else if (n % 2 == 1) {
            rPow((n - 1) / 2);
            (*this)(_i1, _j1, _i2, _j2).matrixProduct(copy);
        }
    }
}

template<typename T>
void NPMatrix<T>::inv() {
    ul_t i, j, k, l;

    if (_a == nullptr) { lupUpdate(); }

    if (_a != nullptr) {
        for (j = 0; j < _a->_n; j++) {
            for (i = 0; i < _a->_n; i++) {
                (*this)(i + _i1, j + _j1) = (((*_perm)[i] == j) ? 1.0 : 0.0);
                for (l = 0; l < i; ++l) {
                    (*this)(i + _i1, j + _j1) -= (*_a)(i, l) * (*this)(l, j);
                }
            }
            for (i = 0; i < _a->_n; i++) {
                k = _a->_n - 1 - i;
                for (l = k + 1; l < _a->_n; l++) {
                    (*this)(k + _i1, j + _j1) -= (*_a)(k, l) * (*this)(l, j);
                }
                (*this)(k + _i1, j + _j1) /= (*_a)(k, k);
            }
        }
        if (_a->_n != _n) {
            lupClear();
        }
    }
}

template<typename T>
void NPMatrix<T>::solve(NVector<T> &vector) {
    ul_t i, l, k;

    if (_a == nullptr) { lupUpdate(); }

    if (_i2 - _i1 + 1 == vector.dim() && _a != nullptr) {
        for (i = 0; i < _a->_n; i++) {
            vector(i) = vector((*_perm)[i]);
            for (l = 0; l < i; ++l) {
                vector(i) -= (*_a)(i, l) * vector(l);
            }
        }
        for (i = 0; i < _a->_n; i++) {
            k = _a->_n - 1 - i;
            for (l = k + 1; l < _a->_n; ++l) {
                vector(k) -= (*_a)(k, l) * vector(l);
            }
            vector(k) /= (*_a)(k, k);
        }
        if (_a->_n != _n) {
            lupClear();
        }
    }
}


// LUP MANAGEMENT

template<typename T>
void NPMatrix<T>::lupUpdate() const {
    //Returns PA such as PA = LU where P is a row p array and A = L * U;
    ul_t i, j, k, i_max;

    lupClear();

    _a = new NPMatrix<T>(this->subMatrix(_i1, _j1, _i2, _j2));
    auto *p = new std::vector<ul_t>();

    for (i = 0; i <= _a->_n; ++i)
        p->push_back(i); //Unit p permutation, p[i] initialized with i

    if (!_a->isUpper() || !_a->isLower()) {
        for (i = 0; i < _a->_n; ++i) {
            i_max = _a->col(i)(i, _a->_n - 1).maxAbsIndex() + i;
            if (abs((*_a)(i_max, i)) > EPSILON) { //matrix is not de
                // generate
                if (i_max != i) {
                    j = (*p)[i];
                    (*p)[i] = (*p)[i_max];
                    (*p)[i_max] = j;

                    _a->swapRow(i, i_max);

                    (*p)[_a->_n]++; //counting pivots starting from a->_n (for determinant)
                }
            } else {
                lupClear();
                return;
            }
            for (j = i + 1; j < _a->_n; ++j) {
                (*_a)(j, i) /= (*_a)(i, i);
                for (k = i + 1; k < _a->_n; ++k) {
                    (*_a)(j, k) -= (*_a)(j, i) * (*_a)(i, k);
                }
            }
        }
    }
    _perm = p;
}

template<typename T>
void NPMatrix<T>::lupCopy() const {
    if (_a != nullptr && _perm != nullptr) {
        _a = new NPMatrix<T>(*(_a));
        _perm = new std::vector<ul_t>(_n);
        std::copy(_perm, _perm + _n, _perm);
    }
}

template<typename T>
void NPMatrix<T>::lupClear() const {
    if (_a != nullptr) {
        delete _a;
        delete _perm;
        _a = nullptr;
        _perm = nullptr;
    }
}

// CHARACTERIZATION

template<typename T>
bool NPMatrix<T>::isValidRowIndex(ul_t i) const {
    return i < _n;
}

template<typename T>
bool NPMatrix<T>::isValidColIndex(ul_t j) const {
    return j < _p;
}

template<typename T>
bool NPMatrix<T>::isValidIndex(ul_t i, ul_t j) const {
    return isValidRowIndex(i) && isValidColIndex(j);
}

template<typename T>
bool NPMatrix<T>::isBetweenI12(ul_t i) const {
    return i >= _i1 && i <= _i2;
}

template<typename T>
bool NPMatrix<T>::isBetweenJ12(ul_t j) const {
    return j >= _j1 && j <= _j2;
}

template<typename T>
bool NPMatrix<T>::isCompatible(const NVector<T> &u) const {
    return u.dim() - 1 == _j2 - _j1;
}

template<typename T>
bool NPMatrix<T>::isCompatible(const NPMatrix<T> &m) const {
    return m._i2 - m._i1 == _j2 - _j1;
}

template<typename T>
bool NPMatrix<T>::hasSameSize(const NPMatrix<T> &m) const {
    return m._i2 - m._i1 == _i2 - _i1 && m._j2 - m._j1 == _j2 - _j1;
}

template<typename T>
bool NPMatrix<T>::hasDefaultBrowseIndices() const {
    return _i1 == 0 &&
           _j1 == 0 &&
           (_i2 == _n - 1 || _i2 == 0) &&
           (_j2 == _p - 1 || _j2 == 0) &&
           NVector<T>::hasDefaultBrowseIndices();
}

template<typename T>
void NPMatrix<T>::setDefaultBrowseIndices() const {
    _i1 = 0;
    _j1 = 0;
    _i2 = _n - 1;
    _j2 = _p - 1;
    NVector<T>::setDefaultBrowseIndices();
}

// SERIALIZATION

template<typename T>
void NPMatrix<T>::copy(const NPMatrix<T> &m) {
    if (this != &m) {
        if (hasDefaultBrowseIndices() && m.hasDefaultBrowseIndices()) {
            this->std::vector<T>::operator=(m);
            _n = m._n;
            _p = m._p;
            lupCopy();
        } else if (hasDefaultBrowseIndices()) {
            this->std::vector<T>::operator=(m.subMatrix(m._i1, m._j1, m._i2, m._j2));
            _n = m._i2 - m._i1 + 1;
            _p = m._j2 - m._j1 + 1;
            lupClear();
        } else {
            setSubMatrix(m);
            lupClear();
        }
        setDefaultBrowseIndices();
        m.setDefaultBrowseIndices();
    }
}

template<typename T>
void NPMatrix<T>::parse(const string &str) {

    string copy_str{str};
    std::vector<NVector<T> > rows;

    ul_t pos_par;
    while ((pos_par = copy_str.find(')')) != string::npos) {
        rows.push_back(NVector<T>(copy_str.substr(0, pos_par)));
        copy_str.erase(copy_str.begin(), copy_str.begin() + pos_par + 1);
    }

    this->copy(NPMatrix<T>(rows));
}

template<typename T>
ul_t NPMatrix<T>::vectorIndex(ul_t i, ul_t j) const {
    return _p * i + j;
}

template<typename T>
ul_t NPMatrix<T>::getRowFromVectorIndex(ul_t k) const {
    assert(k < _n * _p);
    return k / _p;
}

template<typename T>
ul_t NPMatrix<T>::getColFromVectorIndex(ul_t k) const {
    assert(k < _n * _p);
    return k % _p;
}


// SUB-MATRICES

template<typename T>
NPMatrix<T> NPMatrix<T>::subMatrix(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const {
    NPMatrix<T> sub_matrix = NPMatrix<T>::zeros(i2 - i1 + 1, j2 - j1 + 1);


    for (ul_t i = 0; i <= i2 - i1; ++i) {
        for (ul_t j = 0; j <= j2 - j1; ++j) {
            sub_matrix(i, j) = (*this)(i + i1, j + j1);
        }
    }
    return sub_matrix;
}

template<typename T>
void NPMatrix<T>::setSubMatrix(const NPMatrix<T> &m) {
    assert(hasSameSize(m));

    for (ul_t i = 0; i <= _i2 - _i1; ++i) {
        for (ul_t j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) = m(i + m._i1, j + m._j1);
        }
    }
    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
}

template
class NPMatrix<double>;

template
class NPMatrix<char>;

template
class NPMatrix<AESByte>;


























