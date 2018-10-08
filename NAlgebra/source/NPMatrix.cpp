//
// Created by Sami Dahoux on 04/05/2018.
//

#include <NPMatrix.h>

#include "../header/NPMatrix.h"

using namespace std;

NPMatrix::NPMatrix(unsigned long n, unsigned long p) :
        NVector(n * ((p > 0) ? p : n)), _n(n), _p((p > 0) ? p : n), _i1(0), _j1(0), _i2(0), _j2(0) {
    setDefaultBrowseIndices();
}

NPMatrix::NPMatrix(const vector<vector<double> > &data) :
        NVector((data.size() * data[0].size())), _n(data.size()), _p(data[0].size()),
        _i1(0), _j1(0), _i2(0), _j2(0) {

    for (unsigned long i = 0; i < _n; ++i) {

        assert(data[i].size() == data[0].size());

        for (unsigned long j = 0; j < _p; ++j) {
            (*this)(i, j) = data[i][j];
        }
    }
    setDefaultBrowseIndices();
}

NPMatrix::NPMatrix(const NPMatrix &m) : NVector(0),
                                        _n(0), _p(0),
                                        _i1(0), _j1(0),
                                        _i2(0), _j2(0) {
    copy(m);
}

NPMatrix::NPMatrix(const string &str) : NVector(0), _n(0), _p(0), _i1(0), _j1(0), _i2(0), _j2(0) {
    parse(str);
    setDefaultBrowseIndices();

}

NPMatrix::NPMatrix(const NVector &u) :
        NVector(u), _n(1), _p(u.dim()), _i1(0), _j1(0), _i2(0), _j2(0) {
    setDefaultBrowseIndices();
}

NPMatrix::NPMatrix(const NVector &u, unsigned long n, unsigned long p) :
        NVector(u), _n(n), _p((p > 0) ? p : n), _i1(0), _j1(0), _i2(0), _j2(0) {
    assert(u.dim() == _n * _p);
    setDefaultBrowseIndices();
}

NPMatrix::NPMatrix(const vector<NVector> &vectors) :
        NVector((vectors.size() * vectors[0].dim())), _n(vectors.size()), _p(vectors[0].dim()),
        _i1(0), _j1(0), _i2(0), _j2(0) {

    for (unsigned long i = 0; i < _n; ++i) {

        assert(vectors[i].dim() == vectors[0].dim());

        setRow(vectors[i], i);
    }
    setDefaultBrowseIndices();
}


string NPMatrix::str() const {
    string str = "\n";
    char buffer[6];
    for (unsigned long i = 0; i < _n; ++i) {
        str.append("|");
        for (unsigned long j = 0; j < _p; ++j) {
            sprintf(buffer, "%.2e", abs((*this)(i, j)));
            str.append(((*this)(i, j) >= 0 ? "  " : " -"));
            str.append(buffer);
        }
        str.append("  |\n");
    }

    return str;
}


// GETTERS

bool NPMatrix::isSquare() const {
    return _j2 - _j1 == _i2 - _i1;
}

unsigned long NPMatrix::n() const {
    auto res = _i2 - _i1 + 1;
    setDefaultBrowseIndices();
    return res;
}

unsigned long NPMatrix::p() const {
    auto res = _j2 - _j1 + 1;
    setDefaultBrowseIndices();
    return res;
}

NVector NPMatrix::row(unsigned long i) const {
    assert(isValidRowIndex(i));

    vector<double> data{this->begin() + _p * i, this->begin() + _p * (i + 1)};
    return NVector(data);
}

NVector NPMatrix::col(unsigned long j) const {
    assert(isValidColIndex(j));

    vector<double> data(_n);
    for (unsigned long k = 0; k < _n; ++k) {
        data[k] = (*this)(k, j);
    }
    return NVector(data);
}

vector<NVector> NPMatrix::rows(unsigned long i1, unsigned long i2) const {

    auto end = i2 == MAX_SIZE ? _n - 1 : i2;

    assert(end >= i1 && isValidRowIndex(i1) && isValidRowIndex(end));

    vector<NVector> rows(end - i1 + 1);
    for (auto i = i1; i <= end; ++i) {
        rows[i - i1] = row(i);
    }
    return rows;
}

vector<NVector> NPMatrix::cols(unsigned long j1, unsigned long j2) const {

    auto end = j2 == MAX_SIZE ? _p - 1 : j2;

    assert(end >= j1 && isValidColIndex(j1) && isValidColIndex(end));

    vector<NVector> cols(end - j1 + 1);
    for (auto j = j1; j <= end; ++j) {
        cols[j - j1] = col(j);
    }
    return cols;
}


// ROWS/COLS/SUB SETTERS


void NPMatrix::setRow(const NVector &u, unsigned long i1) {
    assert(u.dim() <= _p && isValidRowIndex(i1));

    std::copy(u.begin(), u.end(), this->begin() + _p * i1);
}

void NPMatrix::setCol(const NVector &u, unsigned long j1) {
    assert(u.dim() <= _n && isValidColIndex(j1));

    for (unsigned long i = 0; i < u.dim(); ++i) {
        (*this)(i, j1) = u(i);
    }
}

void NPMatrix::setRows(const vector<NVector> &vectors, unsigned long i1) {
    unsigned long size = (vectors.size() + i1 < _n) ? vectors.size() + i1 : _n;

    for (auto i = i1; i < size; ++i) {
        setRow(vectors[i - i1], i);
    }
}

void NPMatrix::setCols(const vector<NVector> &vectors, unsigned long j1) {
    unsigned long size = (vectors.size() + j1 <= _p) ? vectors.size() + j1 : _p;

    for (auto j = j1; j < size; ++j) {
        setCol(vectors[j - j1], j);
    }
}


// MANIPULATORS

// SWAPS


void NPMatrix::swap(unsigned long i1, unsigned long j1, unsigned long i2, unsigned long j2) {
    assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));

    NVector::swap(getVectorIndex(i1, j1), getVectorIndex(i2, j2));
}

void NPMatrix::swapRow(unsigned long i1, unsigned long i2) {
    swap(Row, i1, i2);
}

void NPMatrix::swapCol(unsigned long j1, unsigned long j2) {
    swap(Col, j1, j2);
}


// SHIFTS


void NPMatrix::shiftRow(unsigned long i, const long iterations) {
    shift(Row, i, iterations);
}

void NPMatrix::shiftCol(unsigned long j, const long iterations) {
    shift(Col, j, iterations);
}

// TRANSPOSED

NPMatrix NPMatrix::transposed() {
    NPMatrix temp{_j2 - _j1 + 1, _i2 - _i1 + 1};

    for (auto i = _i1; i <= _i2; ++i) {
        for (auto j = _j1; j <= _j2; ++j) {
            temp(j - _j1, i - _i1) = (*this)(i, j);
        }
    }
    setDefaultBrowseIndices();
    return temp;
}

// ALGEBRA

NPMatrix NPMatrix::shifted(const NPMatrix &m) const {
    NPMatrix shifted = NPMatrix::zeros(_n, m._p + _n);
    for (unsigned long i = 0; i < _n; i++) {
        for (unsigned long j = 0; j < _p; j++) {
            shifted(i, j) = (*this)(i, j);
        }

        for (auto j = _p; j < m._p + _p; j++) {
            shifted(i, j) = m(i, j - _p);
        }
    }
    return shifted;
}


void NPMatrix::reduce() {
    const double epsilon = numeric_limits<double>::epsilon();

    unsigned long r = 0, k, i, j;
    NVector spin;
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

NPMatrix NPMatrix::operator+(const NPMatrix &matrix) const {
    NPMatrix res{*this};
    res += matrix;
    return res;
}


NPMatrix NPMatrix::operator-(const NPMatrix &matrix) const {
    NPMatrix res{*this};
    res -= matrix;
    return res;
}

NPMatrix operator*(double s, const NPMatrix &m) {
    NPMatrix res{m};
    res *= s;
    return res;
}


NPMatrix operator*(const NPMatrix &m, double s) {
    return s * m;
}


NPMatrix NPMatrix::operator*(const NPMatrix &m) const {
    NPMatrix res{*this};
    NPMatrix sub_m{this != &m ? m : res};
    res *= sub_m;
    return res;
}

NVector NPMatrix::operator*(const NVector &v) const {
    NVector res{v};
    vectorProduct(res);
    return res;
}

NPMatrix NPMatrix::operator/(double s) const {
    NPMatrix res{*this};
    res /= s;
    return res;
}

NPMatrix NPMatrix::operator-() const {
    NPMatrix res = this->subMatrix(_i1, _j1, _i2, _j2);
    res.opp();
    setDefaultBrowseIndices();
    return res;
}

// SCALAR PRODUCT BASED OPERATIONS

double operator|(const NPMatrix &m1, const NPMatrix &m2) {
    NVector sub_m1 = m1(m1._i1, m1._j1, m1._i2, m1._j2);
    NVector sub_m2 = m2(m2._i1, m2._j1, m2._i2, m2._j2);
    auto res = sub_m1 | sub_m2;

    m1.setDefaultBrowseIndices();
    m2.setDefaultBrowseIndices();
    return res;
}

double operator!(const NPMatrix &m) {
    return sqrt(m | m);
}

double operator/(const NPMatrix &m1, const NPMatrix &m2) {
    return !(m1 - m2);
}

// COMPOUND OPERATORS

NPMatrix &NPMatrix::operator+=(const NPMatrix &m1) {
    assert(hasSameSize(m1));

    NPMatrix sub_this{this->subMatrix(_i1, _j1, _i2, _j2)};
    sub_this.NVector::operator+=(m1(m1._i1, m1._j1, m1._i2, m1._j2));
    (*this)(_i1, _j1, _i2, _j2) = sub_this;

    setDefaultBrowseIndices();
    m1.setDefaultBrowseIndices();

    return *this;
}

NPMatrix &NPMatrix::operator-=(const NPMatrix &m) {
    return *this += (-m);
}


NPMatrix &NPMatrix::operator*=(const NPMatrix &m) {
    matrixProduct(m);

    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
    return *this;
}


NPMatrix &NPMatrix::operator*=(double s) {
    NPMatrix sub_this{this->subMatrix(_i1, _j1, _i2, _j2)};
    sub_this.NVector::operator*=(s);
    (*this)(_i1, _j1, _i2, _j2) = sub_this;
    setDefaultBrowseIndices();

    return *this;
}

NPMatrix &NPMatrix::operator/=(double s) {
    return operator*=(1 / s);
}


// BI-DIMENSIONAL ACCESSORS


double &NPMatrix::operator()(unsigned long i, unsigned long j) {
    assert(isValidIndex(i, j));
    return (*this)[getVectorIndex(i, j)];

}

double NPMatrix::operator()(unsigned long i, unsigned long j) const {
    assert(isValidIndex(i, j));
    return (*this).at(getVectorIndex(i, j));
}

NPMatrix NPMatrix::operator()(unsigned long i1, unsigned long j1, unsigned long i2, unsigned long j2) const {
    return subMatrix(i1, j1, i2, j2);
}

NPMatrix &NPMatrix::operator()(unsigned long i1, unsigned long j1, unsigned long i2, unsigned long j2) {
    assert(isValidIndex(i1, j1) && isValidIndex(i2, j2));
    assert(i2 >= i1 && j2 >= j1);

    _i1 = i1;
    _j1 = j1;
    _i2 = i2;
    _j2 = j2;

    return *this;
}

// AFFECTATION

NPMatrix &NPMatrix::operator=(const NPMatrix &m) {
    copy(m);
    return *this;
}

NPMatrix &NPMatrix::operator=(const string &str) {
    parse(str);
    return *this;
}

// COMPARAISON OPERATORS

bool operator==(const NPMatrix &m1, const NPMatrix &m2) {
    bool res = m1(m1._i1, m1._j1, m1._i2, m1._j2).isEqual(m2(m2._i1, m2._j1, m2._i2, m2._j2));

    m1.setDefaultBrowseIndices();
    m2.setDefaultBrowseIndices();
    return res;
}

bool operator!=(const NPMatrix &m1, const NPMatrix &m2) {
    return !(m1 == m2);
}


// STATIC FUNCTIONS


NPMatrix NPMatrix::zeros(unsigned long n, unsigned long p) {
    p = (p > 0) ? p : n;
    return NPMatrix(NVector::zeros(n * p), n, p);
}

NPMatrix NPMatrix::ones(unsigned long n, unsigned long p) {
    p = (p > 0) ? p : n;
    return NPMatrix(NVector::ones(n * p), n, p);
}

NPMatrix NPMatrix::canonical(unsigned long i, unsigned long j, unsigned long n, unsigned long p) {
    p = (p > 0) ? p : n;
    return NPMatrix(NVector::canonical(p * i + j, n * p), n, p);
}

// PROTECTED METHODS

// MANIPULATORS


void NPMatrix::swap(const ElementEnum element, unsigned long k1, unsigned long k2) {

    NVector temp = (element == Row) ? NPMatrix::row(k1) : col(k1);

    (element == Row) ? setRow(row(k2), k1) : setCol(col(k2), k1);
    (element == Row) ? setRow(temp, k2) : setCol(temp, k2);

    setDefaultBrowseIndices();
}

void NPMatrix::shift(const ElementEnum element, unsigned long k, const long iterations) {

    assert(element == Row ? isBetweenI12(k + _i1) : isBetweenJ12(k + _j1));

    NVector vector = (element == Row) ? row(k + _i1) : col(k + _j1);
    (element == Row) ? vector(_j1, _j2).shift(iterations) : vector(_i1, _i2).shift(iterations);
    (element == Row) ? setRow(vector, k + _i1) : setCol(vector, k + _j1);

    setDefaultBrowseIndices();
}

// MAX/MIN

unsigned long NPMatrix::maxAbsIndex(const ElementEnum element, unsigned long k, unsigned long r) const {
    NVector elem{(element == Row) ? row(k) : col(k)};
    NVector vector;
    vector = elem(r, (element == Row) ? _p - 1 : _n - 1);
    return r + vector.maxAbsIndex();
}

unsigned long NPMatrix::maxAbsIndexRow(unsigned long i, unsigned long r) const {
    return maxAbsIndex(Row, i, r);
}

unsigned long NPMatrix::maxAbsIndexCol(unsigned long j, unsigned long r) const {
    return maxAbsIndex(Col, j, r);
}

// ALGEBRAICAL OPERATIONS


void NPMatrix::vectorProduct(NVector &u) const {

    NVector res = NVector::zeros(u.dim());
    std::vector<NVector> vector_rows = rows(_i1, _i2);

    assert(isCompatible(res));

    for (unsigned long i = _i1; i <= _i2; ++i) {
        res(i - _i1) = vector_rows[i](_j1, _j2) | u;
    }
    u = res;

    setDefaultBrowseIndices();
}

void NPMatrix::matrixProduct(const NPMatrix &m) {
    assert(isCompatible(m));
    assert(isSquare() || hasDefaultBrowseIndices());

    vector<NVector> vector_rows = rows();
    vector<NVector> vector_cols = m.cols();

    NPMatrix res = NPMatrix::zeros(_i2 - _i1 + 1, m._j2 - m._j1  + 1);
    for (unsigned long i = _i1; i <= _i2; ++i) {
        for (unsigned long j = m._j1; j <= m._j2; ++j) {
            res(i - _i1, j - m._j1) = vector_rows[i](_j1, _j2) | vector_cols[j](m._i1, m._i2);
        }
    }
    this->copy(res);
}

// PRIVATE METHODS

// CHARACTERIZATION

bool NPMatrix::isValidRowIndex(unsigned long i) const {
    return i < _n;
}

bool NPMatrix::isValidColIndex(unsigned long j) const {
    return j < _p;
}

bool NPMatrix::isValidIndex(unsigned long i, unsigned long j) const {
    return isValidRowIndex(i) && isValidColIndex(j);
}

bool NPMatrix::isBetweenI12(unsigned long i) const {
    return i >= _i1 && i <= _i2;
}

bool NPMatrix::isBetweenJ12(unsigned long j) const {
    return j >= _j1 && j <= _j2;
}

bool NPMatrix::isCompatible(const NVector &u) const {
    return u.dim() - 1 == _j2 - _j1;
}

bool NPMatrix::isCompatible(const NPMatrix &m) const {
    return m._i2 - m._i1 == _j2 - _j1;
}

bool NPMatrix::hasSameSize(const NPMatrix &m) const {
    return m._i2 - m._i1 == _i2 - _i1 && m._j2 - m._j1 == _j2 - _j1;
}

bool NPMatrix::hasDefaultBrowseIndices() const {
    return _i1 == 0 &&
           _j1 == 0 &&
           (_i2 == _n - 1 || _i2 == 0) &&
           (_j2 == _p - 1 || _j2 == 0) &&
           NVector::hasDefaultBrowseIndices();
}

void NPMatrix::setDefaultBrowseIndices() const {
    _i1 = 0;
    _j1 = 0;
    _i2 = _n - 1;
    _j2 = _p - 1;
    NVector::setDefaultBrowseIndices();
}

// SERIALIZATION

void NPMatrix::copy(const NPMatrix &m) {
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

void NPMatrix::parse(const string &str) {

    string copy_str{str};
    std::vector<NVector> rows;

    unsigned long pos_par;
    while((pos_par = copy_str.find(')')) != string::npos) {
        rows.push_back(NVector(copy_str.substr(0, pos_par)));
        copy_str.erase(copy_str.begin(), copy_str.begin() + pos_par + 1);
    }

    this->copy(NPMatrix(rows));
}


unsigned long NPMatrix::getVectorIndex(unsigned long i, unsigned long j) const {
    return _p * i + j;
}

unsigned long NPMatrix::getRowFromVectorIndex(unsigned long k) const {
    assert(k < _n * _p);
    return k / _p;
}

unsigned long NPMatrix::getColFromVectorIndex(unsigned long k) const {
    assert(k < _n * _p);
    return k % _p;
}


// SUB-MATRICES

NPMatrix NPMatrix::subMatrix(unsigned long i1, unsigned long j1, unsigned long i2, unsigned long j2) const {
    NPMatrix sub_matrix = NPMatrix::zeros(i2 - i1 + 1, j2 - j1 + 1);


    for (unsigned long i = 0; i <= i2 - i1; ++i) {
        for (unsigned long j = 0; j <= j2 - j1; ++j) {
            sub_matrix(i, j) = (*this)(i + i1, j + j1);
        }
    }
    return sub_matrix;
}

void NPMatrix::setSubMatrix(const NPMatrix &m) {
    assert(hasSameSize(m));

    for (unsigned long i = 0; i <= _i2 - _i1; ++i) {
        for (unsigned long j = 0; j <= _j2 - _j1; ++j) {
            (*this)(i + _i1, j + _j1) = m(i + m._i1, j + m._j1);
        }
    }
    setDefaultBrowseIndices();
    m.setDefaultBrowseIndices();
}
































