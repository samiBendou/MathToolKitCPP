//
// Created by Sami Dahoux on 04/05/2018.
//

#include <NPMatrix.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wabsolute-value"

using namespace std;

template<typename T>
string NPMatrix<T>::str() const {
    stringstream stream;

    for (size_t i = _i1; i <= _i2; ++i) {
        stream << "\n";
        stream << row(i)(_j1, _j2);
    }
    setDefaultBrowseIndices();
    return stream.str();
}


template<typename T>
vector<vector<T>> NPMatrix<T>::array() const {
    vector<vector<T>> array{_i2 - _i1 + 1};
    for (size_t i = _i1; i <= _i2; ++i) {
        array[i] = row(i);
    }
    setDefaultBrowseIndices();
    return array;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::resizeRow(size_t n) {
    std::vector<T>::resize(n * _p);
    _n = n;
    return clean();
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::resizeCol(size_t p) {
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::resize(size_t n, size_t p) {
    resizeCol(p);
    resizeRow(n);
    return *this;
}


// CHARACTERIZATION

template<typename T>
bool NPMatrix<T>::isUpper() const {
    for (size_t i = _i1; i <= _i2; ++i) {
        for (size_t j = _j1; j <= i; ++j) {
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
    for (size_t i = _i1; i <= _i2; ++i) {
        for (size_t j = i + 1; j <= _j2; ++j) {
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
    for (size_t i = _i1; i <= _i2; i++) {
        for (size_t j = _j1; j <= _j2; j++) {
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
NVector<T> NPMatrix<T>::row(size_t i) const {
    assert(isValidRowIndex(i));
    return vector<T>{this->begin() + _p * i, this->begin() + _p * (i + 1)};
}

template<typename T>
NVector<T> NPMatrix<T>::col(size_t j) const {
    assert(isValidColIndex(j));

    vector<T> data(_n);
    for (size_t k = 0; k < _n; ++k) {
        data[k] = (*this)(k, j);
    }
    return NVector<T>(data);
}

template<typename T>
vector<NVector<T> > NPMatrix<T>::rows(size_t i1, size_t i2) const {

    auto end = i2 == MAX_SIZE ? _n - 1 : i2;

    assert(end >= i1 && isValidRowIndex(i1) && isValidRowIndex(end));

    vector<NVector<T> > rows(end - i1 + 1);
    for (auto i = i1; i <= end; ++i) {
        rows[i - i1] = row(i);
    }
    return rows;
}

template<typename T>
vector<NVector<T> > NPMatrix<T>::cols(size_t j1, size_t j2) const {

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
    for (size_t i = _i1; i <= _i2; ++i) {
        for (size_t j = i; j <= _j2; ++j)
            upper(i, j) = (*this)(i, j);
    }

    setDefaultBrowseIndices();
    return upper;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::lower() const {

    NPMatrix<T> lower = NPMatrix<T>::zeros(_i2 - _i1 + 1);
    for (size_t i = _i1; i <= _i2; ++i) {
        for (size_t j = _j1; j <= i; ++j)
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
    for (size_t i = 0; i < _a->_n; ++i) {
        l(i, i) = 1;
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
NPMatrix<T> &NPMatrix<T>::setRow(const NVector<T> &u, size_t i1) {
    assert(u.dim() <= _p && isValidRowIndex(i1));

    std::copy(u.begin(), u.end(), this->begin() + _p * i1);
    lupClear();
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::setCol(const NVector<T> &u, size_t j1) {
    assert(u.dim() <= _n && isValidColIndex(j1));

    for (size_t i = 0; i < u.dim(); ++i) {
        (*this)(i, j1) = u(i);
    }
    lupClear();
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::setRows(const vector<NVector<T>> &vectors, size_t i1) {
    size_t size = (vectors.size() + i1 < _n) ? vectors.size() + i1 : _n;

    for (auto i = i1; i < size; ++i) {
        setRow(vectors[i - i1], i);
    }
    lupClear();
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::setCols(const vector<NVector<T>> &vectors, size_t j1) {
    size_t size = (vectors.size() + j1 <= _p) ? vectors.size() + j1 : _p;

    for (auto j = j1; j < size; ++j) {
        setCol(vectors[j - j1], j);
    }
    lupClear();
    return *this;
}


// MANIPULATORS

// TRANSPOSED
template<typename T>
NPMatrix<T> & NPMatrix<T>::trans() {
    NPMatrix<T> temp{_j2 - _j1 + 1, _i2 - _i1 + 1};
    for (auto i = _i1; i <= _i2; ++i) {
        for (auto j = _j1; j <= _j2; ++j) {
            swap(i, j, j, i);
        }
    }
    setDefaultBrowseIndices();
    return *this;
}

template<typename T>
T NPMatrix<T>::trace() const {
    T trace = 0;
    for (size_t i = _i1; i <= _i2; i++) {
        trace += (*this)(i, i);
    }
    setDefaultBrowseIndices();
    return trace;
}


// ALGEBRA


template<typename T>
NPMatrix<T> NPMatrix<T>::shifted(const NPMatrix<T> &m) const {
    NPMatrix<T> shifted = NPMatrix<T>::zeros(_n, m._p + _n);
    for (size_t i = 0; i < _n; i++) {
        for (size_t j = 0; j < _p; j++) {
            shifted(i, j) = (*this)(i, j);
        }

        for (auto j = _p; j < m._p + _p; j++) {
            shifted(i, j) = m(i, j - _p);
        }
    }
    return shifted;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::reduce() {
    size_t r = 0, k, i, j;
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
    return clean();
}

template<typename T>
T NPMatrix<T>::det() const {
    T det = 0;
    if (_a == nullptr) { lupUpdate(); }

    if (_a != nullptr) {
        det = (*_a)(0, 0);
        for (size_t i = 1; i < _a->_n; i++) {
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

// BI-DIMENSIONAL ACCESSORS

template<typename T>
NPMatrix<T> &NPMatrix<T>::operator()(size_t i1, size_t j1, size_t i2, size_t j2) {
    assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));
    assert(i2 >= i1 && j2 >= j1);

    _i1 = i1;
    _j1 = j1;
    _i2 = i2;
    _j2 = j2;

    return *this;
}

// STATIC FUNCTIONS

template<typename T>
NPMatrix<T> NPMatrix<T>::eye(size_t n) {
    NPMatrix<T> eye = NPMatrix<T>::zeros(n);
    for (size_t k = 0; k < eye.n(); ++k) {
        eye(k, k) = 1;
    }
    return eye;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::diag(const vector<T> &data, size_t n) {
    NPMatrix<T> diag = NPMatrix<T>::zeros(n);
    for (size_t k = 0; k < n; ++k) {
        diag(k, k) = data[k];
    }
    return diag;
}

template<typename T>
NPMatrix<T> NPMatrix<T>::ndiag(const vector<NVector<T>> &data) {
    auto n = (long) data.size();
    auto middle = (n - 1) / 2;
    auto dim = data[middle].dim();
    NPMatrix<T> diag = NPMatrix<T>::zeros(dim);

    for (long l = -middle; l <= middle; l++) {
        for (size_t k = 0; k < dim - abs(l); k++) {
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
NPMatrix<T> NPMatrix<T>::nscalar(const vector<T> &scalars, size_t n) {
    auto scalarSize = (long) scalars.size();
    long minSize = n - scalarSize;

    vector<NVector<T> > diags((size_t) (2 * scalarSize - 1));
    size_t size = 1;
    for (size_t l = 0; l < scalarSize; l++) {
        diags[l] = NVector<T>::scalar(scalars[l], size + minSize);
        if (l > 0) {
            diags[l + scalarSize - 1] = NVector<T>::scalar(scalars[scalarSize - l - 1], n - size + 1);
        }
        size++;
    }
    return NPMatrix<T>::ndiag(diags);
}

// PROTECTED METHODS


template<typename T>
NPMatrix<T>::NPMatrix(const NVector<T> &u, size_t n, size_t p, size_t i1, size_t j1, size_t i2, size_t j2):
        NVector<T>(u),
        _n(n), _p(p),
        _i1(i1), _j1(j1), _i2(i2), _j2(j2),
        _a(nullptr), _perm(nullptr) {
    setDefaultBrowseIndices();
}

// MANIPULATORS

template<typename T>
NPMatrix<T> &NPMatrix<T>::swap(const Parts element, size_t k1, size_t k2) {

    NVector<T> temp = (element == Row) ? NPMatrix<T>::row(k1) : col(k1);

    (element == Row) ? setRow(row(k2), k1) : setCol(col(k2), k1);
    (element == Row) ? setRow(temp, k2) : setCol(temp, k2);

    return clean();
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::shift(const Parts element, size_t k, const long iterations) {

    assert(element == Row ? isBetweenI12(k + _i1) : isBetweenJ12(k + _j1));

    NVector<T> vector = (element == Row) ? row(k + _i1) : col(k + _j1);
    (element == Row) ? vector(_j1, _j2).shift(iterations) : vector(_i1, _i2).shift(iterations);
    (element == Row) ? setRow(vector, k + _i1) : setCol(vector, k + _j1);

    return clean();
}

// MAX/MIN

template<typename T>
size_t NPMatrix<T>::maxAbsIndex(const Parts element, size_t k, size_t r) const {
    NVector<T> elem{(element == Row) ? row(k) : col(k)};
    NVector<T> vector;
    vector = elem(r, (element == Row) ? _p - 1 : _n - 1);
    return r + vector.maxAbsIndex();
}

// PRIVATE METHODS

// ALGEBRAICAL OPERATIONS

template<typename T>
NVector<T> &NPMatrix<T>::vectorProduct(NVector<T> &u) const {

    NVector<T> res = NVector<T>::zeros(u.dim());

    assert(matchSizeForProduct(res));

    for (size_t i = _i1; i <= _i2; ++i) {
        res(i - _i1) = row(i)(_j1, _j2) | u;
    }
    u = res;

    setDefaultBrowseIndices();
    return u;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::matrixProduct(const NPMatrix<T> &m) {
    assert(matchSizeForProduct(m));
    assert((_j2 - _j1 == _i2 - _i1) || hasDefaultBrowseIndices());

    NPMatrix<T> res = NPMatrix<T>::zeros(_i2 - _i1 + 1, m._j2 - m._j1 + 1);


    for (size_t i = _i1; i <= _i2; ++i) {
        for (size_t j = m._j1; j <= m._j2; ++j) {
            res(i - _i1, j - m._j1) = row(i)(_j1, _j2) | m.col(j)(m._i1, m._i2);
        }
    }

    copy(res);
    lupClear();
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::pow(long exp) {
    if (exp > 0) {
        rPow(exp);
    } else if (exp < 0) {
        inv();
        rPow(-exp);
    } else {
        *this = NPMatrix<T>::eye(n());
    }
    return clean();
}

template<typename T>
void NPMatrix<T>::rPow(const long exp) {
    if (exp > 1) {
        const NPMatrix<T> this_copy{subMatrix(_i1, _j1, _i2, _j2)};
        matrixProduct(this_copy);
        if (exp % 2 == 0) {
            rPow(exp / 2);
        } else if (exp % 2 == 1) {
            rPow((exp - 1) / 2);
            matrixProduct(this_copy);
        }
    }
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::inv() {
    size_t i, j, k, l;

    if (_a == nullptr) { lupUpdate(); }

    if (_a != nullptr) {
        for (j = 0; j < _a->_n; j++) {
            for (i = 0; i < _a->_n; i++) {
                (*this)(i + _i1, j + _j1) = (((*_perm)[i] == j) ? 1 : 0);
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
    return *this;
}

template<typename T>
NVector<T> &NPMatrix<T>::solve(NVector<T> &u) const {
    size_t i, l, k;

    if (_a == nullptr) { lupUpdate(); }

    if (_i2 - _i1 + 1 == u.dim() && _a != nullptr) {
        for (i = 0; i < _a->_n; i++) {
            u(i) = u((*_perm)[i]);
            for (l = 0; l < i; ++l) {
                u(i) -= (*_a)(i, l) * u(l);
            }
        }
        for (i = 0; i < _a->_n; i++) {
            k = _a->_n - 1 - i;
            for (l = k + 1; l < _a->_n; ++l) {
                u(k) -= (*_a)(k, l) * u(l);
            }
            u(k) /= (*_a)(k, k);
        }
        if (_a->_n != _n) {
            lupClear();
        }
    }
    return u;
}


// LUP MANAGEMENT


template<typename T>
void NPMatrix<T>::lupClear() const  {
    if(_a != nullptr){
        _a.reset(nullptr);
        _perm.reset(nullptr);
    }
}

template<typename T>
void NPMatrix<T>::lupReset() const {
    lupClear();
    _a.reset(new NPMatrix<T>(subMatrix(_i1, _j1, _i2, _j2)));
    _perm.reset(new vector<size_t>(_a->_n + 1, 0));
    for (size_t i = 0; i <= _a->_n; ++i)
        (*_perm)[i] = i; //Unit p permutation, p[i] initialized with i
}

template<typename T>
void NPMatrix<T>::lupCopy(const NPMatrix &m) const {
    if(m._a > nullptr) {
        _a.reset(new NPMatrix<T>(*(m._a)));
        _perm.reset(new vector<size_t>(m._perm->begin(), m._perm->end()));
    } else {
        lupClear();
    }

}

template<typename T>
void NPMatrix<T>::lupUpdate() const {
    //Returns PA such as PA = LU where P is a row p array and A = L * U;
    size_t i, j, k, i_max;

    lupReset();
    if (!_a->isUpper() || !_a->isLower()) {
        for (i = 0; i < _a->_n; ++i) {
            i_max = _a->col(i)(i, _a->_n - 1).maxAbsIndex() + i;
            if (abs((*_a)(i_max, i)) > EPSILON) { //matrix is not degenerate
                if (i_max != i) {
                    j = (*_perm)[i];
                    (*_perm)[i] = (*_perm)[i_max];
                    (*_perm)[i_max] = j;

                    _a->swapRow(i, i_max);

                    (*_perm)[_a->_n]++; //counting pivots starting from a->_n (for determinant)
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
}


// CHARACTERIZATION

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
NPMatrix<T> &NPMatrix<T>::copy(const NPMatrix<T> &m) {
    if (this != &m) {
        if (hasDefaultBrowseIndices() && m.hasDefaultBrowseIndices()) {
            vector<T>::operator=(m);
            _n = m._n;
            _p = m._p;
            lupCopy(m);
        } else if (hasDefaultBrowseIndices()) {
            vector<T>::operator=(m.subMatrix(m._i1, m._j1, m._i2, m._j2));
            _n = m._i2 - m._i1 + 1;
            _p = m._j2 - m._j1 + 1;
            lupClear();
        } else {
            setSubMatrix(m);
            lupClear();
        }
    }
    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
    return *this;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::copy(const vector<vector<T>> &data) {
    for (size_t i = 0; i < _n; ++i) {
        assert(data[i].size() == data[0].size());

        for (size_t j = 0; j < _p; ++j) {
            (*this)(i, j) = data[i][j];
        }
    }
    return clean();
}

// SUB-MATRICES

template<typename T>
NPMatrix<T> NPMatrix<T>::subMatrix(size_t i1, size_t j1, size_t i2, size_t j2) const {
    NPMatrix<T> sub_matrix = NPMatrix<T>::zeros(i2 - i1 + 1, j2 - j1 + 1);
    for (size_t i = 0; i <= i2 - i1; ++i) {
        for (size_t j = 0; j <= j2 - j1; ++j) {
            sub_matrix(i, j) = (*this)(i + i1, j + j1);
        }
    }
    return sub_matrix;
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::setSubMatrix(const NPMatrix<T> &m) {
    return forEach(m, [](T &x, const T &y) { x = y; });
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::forEach(const NPMatrix<T> &m, const function<void(T &, const T &)> &binary_op) {
    assert(hasSameSize(m));

    for (size_t i = 0; i <= _i2 - _i1; ++i) {
        for (size_t j = 0; j <= _j2 - _j1; ++j) {
            binary_op((*this)(i + _i1, j + _j1), m(i + m._i1, j + m._j1));
        }
    }
    return cleanBoth(m);
}

template<typename T>
NPMatrix<T> &NPMatrix<T>::forEach(T s, const function<void(T &, T)> &binary_op) {
    for (size_t i = _i1; i <= _i2; ++i) {
        for (size_t j = _j1; j <= _j2; ++j) {
            binary_op((*this)(i, j), s);
        }
    }
    return clean();
}


template
class NPMatrix<double_t>;

template
class NPMatrix<char>;

template
class NPMatrix<uc_t>;

template
class NPMatrix<int>;

template
class NPMatrix<AESByte>;

template
class NPMatrix<Pixel>;

#pragma clang diagnostic pop