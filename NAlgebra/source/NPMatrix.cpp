//
// Created by Sami Dahoux on 04/05/2018.
//

#include <NPMatrix.h>

using namespace std;

template <typename T>
NPMatrix<T>::NPMatrix(ul_t n, ul_t p) :
        NVector<T>(n * ((p > 0) ? p : n)), _n(n), _p((p > 0) ? p : n), _i1(0), _j1(0), _i2(0), _j2(0) {
    setDefaultBrowseIndices();
}

template <typename T>
NPMatrix<T>::NPMatrix(const vector<vector<double> > &data) :
        NVector<T>((data.size() * data[0].size())), _n(data.size()), _p(data[0].size()),
        _i1(0), _j1(0), _i2(0), _j2(0) {

    for (ul_t i = 0; i < _n; ++i) {

        assert(data[i].size() == data[0].size());

        for (ul_t j = 0; j < _p; ++j) {
            (*this)(i, j) = data[i][j];
        }
    }
    setDefaultBrowseIndices();
}

template <typename T>
NPMatrix<T>::NPMatrix(const NPMatrix<T> &m) : NVector<T>(0),
                                        _n(0), _p(0),
                                        _i1(0), _j1(0),
                                        _i2(0), _j2(0) {
    copy(m);
}

template <typename T>
NPMatrix<T>::NPMatrix(const string &str) : NVector<T>(0), _n(0), _p(0), _i1(0), _j1(0), _i2(0), _j2(0) {
    parse(str);
    setDefaultBrowseIndices();

}

template <typename T>
NPMatrix<T>::NPMatrix(const NVector<T> &u) :
        NVector<T>(u), _n(1), _p(u.dim()), _i1(0), _j1(0), _i2(0), _j2(0) {
    setDefaultBrowseIndices();
}

template <typename T>
NPMatrix<T>::NPMatrix(const NVector<T> &u, ul_t n, ul_t p) :
        NVector<T>(u), _n(n), _p((p > 0) ? p : n), _i1(0), _j1(0), _i2(0), _j2(0) {
    assert(u.dim() == _n * _p);
    setDefaultBrowseIndices();
}

template <typename T>
NPMatrix<T>::NPMatrix(const vector<NVector<T> > &vectors) :
        NVector<T>((vectors.size() * vectors[0].dim())), _n(vectors.size()), _p(vectors[0].dim()),
        _i1(0), _j1(0), _i2(0), _j2(0) {

    for (ul_t i = 0; i < _n; ++i) {

        assert(vectors[i].dim() == vectors[0].dim());

        setRow(vectors[i], i);
    }
    setDefaultBrowseIndices();
}


template <typename T>
string NPMatrix<T>::str() const {
    string str = "\n";
    char buffer[6];
    for (ul_t i = _i1; i <= _i2; ++i) {
        str.append("(");
        for (ul_t j = _j1; j <= _j2; ++j) {
            sprintf(buffer, "%.2e", abs((*this)(i, j)));
            str.append(((*this)(i, j) >= 0 ? "  " : " -"));
            str.append(buffer);
        }
        str.append("  )\n");
    }

    setDefaultBrowseIndices();
    return str;
}


// GETTERS

template <typename T>
bool NPMatrix<T>::isSquare() const {
    return _j2 - _j1 == _i2 - _i1;
}

template <typename T>
ul_t NPMatrix<T>::n() const {
    auto res = _i2 - _i1 + 1;
    setDefaultBrowseIndices();
    return res;
}

template <typename T>
ul_t NPMatrix<T>::p() const {
    auto res = _j2 - _j1 + 1;
    setDefaultBrowseIndices();
    return res;
}

template <typename T>
NVector<T> NPMatrix<T>::row(ul_t i) const {
    assert(isValidRowIndex(i));

    vector<double> data{this->begin() + _p * i, this->begin() + _p * (i + 1)};
    return NVector<T>(data);
}

template <typename T>
NVector<T> NPMatrix<T>::col(ul_t j) const {
    assert(isValidColIndex(j));

    vector<double> data(_n);
    for (ul_t k = 0; k < _n; ++k) {
        data[k] = (*this)(k, j);
    }
    return NVector<T>(data);
}

template <typename T>
vector<NVector<T> > NPMatrix<T>::rows(ul_t i1, ul_t i2) const {

    auto end = i2 == MAX_SIZE ? _n - 1 : i2;

    assert(end >= i1 && isValidRowIndex(i1) && isValidRowIndex(end));

    vector<NVector<T> > rows(end - i1 + 1);
    for (auto i = i1; i <= end; ++i) {
        rows[i - i1] = row(i);
    }
    return rows;
}

template <typename T>
vector<NVector<T> > NPMatrix<T>::cols(ul_t j1, ul_t j2) const {

    auto end = j2 == MAX_SIZE ? _p - 1 : j2;

    assert(end >= j1 && isValidColIndex(j1) && isValidColIndex(end));

    vector<NVector<T> > cols(end - j1 + 1);
    for (auto j = j1; j <= end; ++j) {
        cols[j - j1] = col(j);
    }
    return cols;
}


// ROWS/COLS/SUB SETTERS


template <typename T>
void NPMatrix<T>::setRow(const NVector<T> &u, ul_t i1) {
    assert(u.dim() <= _p && isValidRowIndex(i1));

    std::copy(u.begin(), u.end(), this->begin() + _p * i1);
}

template <typename T>
void NPMatrix<T>::setCol(const NVector<T> &u, ul_t j1) {
    assert(u.dim() <= _n && isValidColIndex(j1));

    for (ul_t i = 0; i < u.dim(); ++i) {
        (*this)(i, j1) = u(i);
    }
}

template <typename T>
void NPMatrix<T>::setRows(const vector<NVector<T> > &vectors, ul_t i1) {
    ul_t size = (vectors.size() + i1 < _n) ? vectors.size() + i1 : _n;

    for (auto i = i1; i < size; ++i) {
        setRow(vectors[i - i1], i);
    }
}

template <typename T>
void NPMatrix<T>::setCols(const vector<NVector<T> > &vectors, ul_t j1) {
    ul_t size = (vectors.size() + j1 <= _p) ? vectors.size() + j1 : _p;

    for (auto j = j1; j < size; ++j) {
        setCol(vectors[j - j1], j);
    }
}


// MANIPULATORS

// SWAPS


template <typename T>
void NPMatrix<T>::swap(ul_t i1, ul_t j1, ul_t i2, ul_t j2) {
    assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));

    NVector<T>::swap(getVectorIndex(i1, j1), getVectorIndex(i2, j2));
}

template <typename T>
void NPMatrix<T>::swapRow(ul_t i1, ul_t i2) {
    swap(Row, i1, i2);
}

template <typename T>
void NPMatrix<T>::swapCol(ul_t j1, ul_t j2) {
    swap(Col, j1, j2);
}


// SHIFTS


template <typename T>
void NPMatrix<T>::shiftRow(ul_t i, const long iterations) {
    shift(Row, i, iterations);
}

template <typename T>
void NPMatrix<T>::shiftCol(ul_t j, const long iterations) {
    shift(Col, j, iterations);
}

// TRANSPOSED


template <typename T>
NPMatrix<T> NPMatrix<T>::transposed() {
    NPMatrix<T> temp{_j2 - _j1 + 1, _i2 - _i1 + 1};

    for (auto i = _i1; i <= _i2; ++i) {
        for (auto j = _j1; j <= _j2; ++j) {
            temp(j - _j1, i - _i1) = (*this)(i, j);
        }
    }
    setDefaultBrowseIndices();
    return temp;
}

// ALGEBRA


template <typename T>
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

template <typename T>
void NPMatrix<T>::reduce() {
    const double epsilon = numeric_limits<double>::epsilon();

    ul_t r = 0, k, i, j;
    NVector<T> spin;
    for (j = 0; j < floor(_p / 2); ++j) {

        k = maxAbsIndexCol(j, r);
        if (abs((*this)(k, j)) > epsilon) {
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
}

// OPERATORS

// ALGEBRAICAL OPERATORS

template <typename T>
NPMatrix<T> NPMatrix<T>::operator+(const NPMatrix<T> &matrix) const {
    NPMatrix<T> res{*this};
    res += matrix;
    return res;
}

template <typename T>
NPMatrix<T> NPMatrix<T>::operator-(const NPMatrix<T> &matrix) const {
    NPMatrix<T> res{*this};
    res -= matrix;
    return res;
}

template <typename T>
NPMatrix<T> NPMatrix<T>::operator*(const NPMatrix<T> &m) const {
    NPMatrix<T> res{*this};
    NPMatrix<T> sub_m{this != &m ? m : res};
    res *= sub_m;
    return res;
}

template <typename T>
NVector<T> NPMatrix<T>::operator*(const NVector<T> &v) const {
    NVector<T> res{v};
    vectorProduct(res);
    return res;
}

template <typename T>
NPMatrix<T> NPMatrix<T>::operator/(double s) const {
    NPMatrix<T> res{*this};
    res /= s;
    return res;
}

template <typename T>
NPMatrix<T> NPMatrix<T>::operator-() const {
    NPMatrix<T> res = this->subMatrix(_i1, _j1, _i2, _j2);
    res.opp();
    setDefaultBrowseIndices();
    return res;
}

// COMPOUND OPERATORS

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator+=(const NPMatrix<T> &m1) {
    assert(hasSameSize(m1));

    NPMatrix<T> sub_this{this->subMatrix(_i1, _j1, _i2, _j2)};
    sub_this.NVector<T>::operator+=(m1(m1._i1, m1._j1, m1._i2, m1._j2));
    (*this)(_i1, _j1, _i2, _j2) = sub_this;

    setDefaultBrowseIndices();
    m1.setDefaultBrowseIndices();

    return *this;
}

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator-=(const NPMatrix<T> &m) {
    return *this += (-m);
}

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator*=(const NPMatrix<T> &m) {
    matrixProduct(m);

    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
    return *this;
}

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator*=(double s) {
    NPMatrix<T> sub_this{this->subMatrix(_i1, _j1, _i2, _j2)};
    sub_this.NVector<T>::operator*=(s);
    (*this)(_i1, _j1, _i2, _j2) = sub_this;
    setDefaultBrowseIndices();

    return *this;
}

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator/=(double s) {
    return operator*=(1 / s);
}


// BI-DIMENSIONAL ACCESSORS

template <typename T>
double &NPMatrix<T>::operator()(ul_t i, ul_t j) {
    assert(isValidIndex(i, j));
    return (*this)[getVectorIndex(i, j)];

}

template <typename T>
double NPMatrix<T>::operator()(ul_t i, ul_t j) const {
    assert(isValidIndex(i, j));
    return (*this).at(getVectorIndex(i, j));
}

template <typename T>
NPMatrix<T> NPMatrix<T>::operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const {
    return subMatrix(i1, j1, i2, j2);
}

template <typename T>
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

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator=(const NPMatrix<T> &m) {
    copy(m);
    return *this;
}

template <typename T>
NPMatrix<T> &NPMatrix<T>::operator=(const string &str) {
    parse(str);
    return *this;
}

// STATIC FUNCTIONS

template <typename T>
NPMatrix<T> NPMatrix<T>::zeros(ul_t n, ul_t p) {
    p = (p > 0) ? p : n;
    return NPMatrix<T>(NVector<T>::zeros(n * p), n, p);
}

template <typename T>
NPMatrix<T> NPMatrix<T>::ones(ul_t n, ul_t p) {
    p = (p > 0) ? p : n;
    return NPMatrix<T>(NVector<T>::ones(n * p), n, p);
}

template <typename T>
NPMatrix<T> NPMatrix<T>::canonical(ul_t i, ul_t j, ul_t n, ul_t p) {
    p = (p > 0) ? p : n;
    return NPMatrix<T>(NVector<T>::canonical(p * i + j, n * p), n, p);
}

// PROTECTED METHODS

// MANIPULATORS

template <typename T>
void NPMatrix<T>::swap(const ElementEnum element, ul_t k1, ul_t k2) {

    NVector<T> temp = (element == Row) ? NPMatrix<T>::row(k1) : col(k1);

    (element == Row) ? setRow(row(k2), k1) : setCol(col(k2), k1);
    (element == Row) ? setRow(temp, k2) : setCol(temp, k2);

    setDefaultBrowseIndices();
}

template <typename T>
void NPMatrix<T>::shift(const ElementEnum element, ul_t k, const long iterations) {

    assert(element == Row ? isBetweenI12(k + _i1) : isBetweenJ12(k + _j1));

    NVector<T> vector = (element == Row) ? row(k + _i1) : col(k + _j1);
    (element == Row) ? vector(_j1, _j2).shift(iterations) : vector(_i1, _i2).shift(iterations);
    (element == Row) ? setRow(vector, k + _i1) : setCol(vector, k + _j1);

    setDefaultBrowseIndices();
}

// MAX/MIN

template <typename T>
ul_t NPMatrix<T>::maxAbsIndex(const ElementEnum element, ul_t k, ul_t r) const {
    NVector<T> elem{(element == Row) ? row(k) : col(k)};
    NVector<T> vector;
    vector = elem(r, (element == Row) ? _p - 1 : _n - 1);
    return r + vector.maxAbsIndex();
}

template <typename T>
ul_t NPMatrix<T>::maxAbsIndexRow(ul_t i, ul_t r) const {
    return maxAbsIndex(Row, i, r);
}

template <typename T>
ul_t NPMatrix<T>::maxAbsIndexCol(ul_t j, ul_t r) const {
    return maxAbsIndex(Col, j, r);
}

// ALGEBRAICAL OPERATIONS

template <typename T>
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

template <typename T>
void NPMatrix<T>::matrixProduct(const NPMatrix<T> &m) {
    assert(isCompatible(m));
    assert(isSquare() || hasDefaultBrowseIndices());

    vector<NVector<T> > vector_rows = rows();
    vector<NVector<T> > vector_cols = m.cols();

    NPMatrix<T> res = NPMatrix<T>::zeros(_i2 - _i1 + 1, m._j2 - m._j1  + 1);
    for (ul_t i = _i1; i <= _i2; ++i) {
        for (ul_t j = m._j1; j <= m._j2; ++j) {
            res(i - _i1, j - m._j1) = vector_rows[i](_j1, _j2) | vector_cols[j](m._i1, m._i2);
        }
    }
    this->copy(res);
}

// PRIVATE METHODS

// CHARACTERIZATION

template <typename T>
bool NPMatrix<T>::isValidRowIndex(ul_t i) const {
    return i < _n;
}

template <typename T>
bool NPMatrix<T>::isValidColIndex(ul_t j) const {
    return j < _p;
}

template <typename T>
bool NPMatrix<T>::isValidIndex(ul_t i, ul_t j) const {
    return isValidRowIndex(i) && isValidColIndex(j);
}

template <typename T>
bool NPMatrix<T>::isBetweenI12(ul_t i) const {
    return i >= _i1 && i <= _i2;
}

template <typename T>
bool NPMatrix<T>::isBetweenJ12(ul_t j) const {
    return j >= _j1 && j <= _j2;
}

template <typename T>
bool NPMatrix<T>::isCompatible(const NVector<T> &u) const {
    return u.dim() - 1 == _j2 - _j1;
}

template <typename T>
bool NPMatrix<T>::isCompatible(const NPMatrix<T> &m) const {
    return m._i2 - m._i1 == _j2 - _j1;
}

template <typename T>
bool NPMatrix<T>::hasSameSize(const NPMatrix<T> &m) const {
    return m._i2 - m._i1 == _i2 - _i1 && m._j2 - m._j1 == _j2 - _j1;
}

template <typename T>
bool NPMatrix<T>::hasDefaultBrowseIndices() const {
    return _i1 == 0 &&
           _j1 == 0 &&
           (_i2 == _n - 1 || _i2 == 0) &&
           (_j2 == _p - 1 || _j2 == 0) &&
           NVector<T>::hasDefaultBrowseIndices();
}

template <typename T>
void NPMatrix<T>::setDefaultBrowseIndices() const {
    _i1 = 0;
    _j1 = 0;
    _i2 = _n - 1;
    _j2 = _p - 1;
    NVector<T>::setDefaultBrowseIndices();
}

// SERIALIZATION

template <typename T>
void NPMatrix<T>::copy(const NPMatrix<T> &m) {
    if (this != &m) {
        if (hasDefaultBrowseIndices() && m.hasDefaultBrowseIndices()) {
            this->std::vector<double>::operator=(m);
            _n = m._n;
            _p = m._p;
        } else if (hasDefaultBrowseIndices()) {
            this->std::vector<double>::operator=(m.subMatrix(m._i1, m._j1, m._i2, m._j2));
            _n = m._i2 - m._i1 + 1;
            _p = m._j2 - m._j1 + 1;
        } else {
            setSubMatrix(m);
        }
        setDefaultBrowseIndices();
        m.setDefaultBrowseIndices();
    }
}

template <typename T>
void NPMatrix<T>::parse(const string &str) {

    string copy_str{str};
    std::vector<NVector<T> > rows;

    ul_t pos_par;
    while((pos_par = copy_str.find(')')) != string::npos) {
        rows.push_back(NVector<T>(copy_str.substr(0, pos_par)));
        copy_str.erase(copy_str.begin(), copy_str.begin() + pos_par + 1);
    }

    this->copy(NPMatrix<T>(rows));
}

template <typename T>
ul_t NPMatrix<T>::getVectorIndex(ul_t i, ul_t j) const {
    return _p * i + j;
}

template <typename T>
ul_t NPMatrix<T>::getRowFromVectorIndex(ul_t k) const {
    assert(k < _n * _p);
    return k / _p;
}

template <typename T>
ul_t NPMatrix<T>::getColFromVectorIndex(ul_t k) const {
    assert(k < _n * _p);
    return k % _p;
}


// SUB-MATRICES

template <typename T>
NPMatrix<T> NPMatrix<T>::subMatrix(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const {
    NPMatrix<T> sub_matrix = NPMatrix<T>::zeros(i2 - i1 + 1, j2 - j1 + 1);


    for (ul_t i = 0; i <= i2 - i1; ++i) {
        for (ul_t j = 0; j <= j2 - j1; ++j) {
            sub_matrix(i, j) = (*this)(i + i1, j + j1);
        }
    }
    return sub_matrix;
}

template <typename T>
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

template class NPMatrix<double>;




























