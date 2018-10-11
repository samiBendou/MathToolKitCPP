//
// Created by Sami Dahoux on 05/05/2018.
//

#include <NMatrix.h>


NMatrix::NMatrix(ul_t n) : NPMatrix<double>(n, n), _a(nullptr), _perm(nullptr)
{
}


NMatrix::NMatrix(const std::string &str) : NPMatrix<double>(str), _a(nullptr), _perm(nullptr) {
    assert(isSquare());
}


NMatrix::NMatrix(const NPMatrix<double> &matrix) : NPMatrix<double>(matrix), _a(nullptr), _perm(nullptr) {
    assert(isSquare());
}

NMatrix::NMatrix(const NMatrix &matrix) : NPMatrix<double>(matrix), _a(nullptr), _perm(nullptr) {
    //Hard copy constructor
    if(matrix._a != nullptr && matrix._perm != nullptr) {
        _a = new NMatrix(*(matrix._a));
        _perm = new std::vector<ul_t>(matrix._n);
        std::copy(matrix._perm, matrix._perm + matrix._n, _perm);
    }
}

NMatrix::~NMatrix() {
    lupClear();
}

// CHARACTERIZATION

bool NMatrix::isUpper() const {
    for(ul_t i = _i1; i <= _i2; ++i) {
        for(ul_t j = i + 1; j <= _j2; ++j) {
            if(abs((*this)(i, j)) > std::numeric_limits<double>::epsilon()) {
                setDefaultBrowseIndices();
                return false;
            }
        }
    }

    setDefaultBrowseIndices();

    return true;
}

bool NMatrix::isLower() const {
    for(ul_t i = _i1; i <= _i2; ++i) {
        for(ul_t j = i + 1; j <= _j2; ++j) {
            if(abs((*this)(i, j)) > std::numeric_limits<double>::epsilon()) {
                setDefaultBrowseIndices();
                return false;
            }
        }
    }

    setDefaultBrowseIndices();

    return true;
}

bool NMatrix::isDiagonal() const {
    for(ul_t i = _i1; i <= _i2; i++) {
        for(ul_t j = _j1; j <= _j2; j++) {
            if(i != j && abs((*this)(i, j)) > std::numeric_limits<double>::epsilon()) {
                setDefaultBrowseIndices();
                return false;
            }
        }
    }

    setDefaultBrowseIndices();

    return true;
}


// GETTERS


NMatrix NMatrix::upper() const {

    NMatrix upper = NPMatrix<double>::zeros(_i2 - _i1 + 1);
    for(ul_t i = _i1; i <= _i2; ++i) {
        for(ul_t j = i; j <= _j2; ++j)
            upper(i, j) = (*this)(i, j);
    }

    setDefaultBrowseIndices();
    return upper;
}

NMatrix NMatrix::lower() const {

    NMatrix lower = NPMatrix<double>::zeros(_i2 - _i1 + 1);
    for(ul_t i = _i1; i <= _i2; ++i) {
        for(ul_t j = _j1; j <= i; ++j)
            lower(i, j) = (*this)(i, j);
    }

    setDefaultBrowseIndices();
    return lower;
}

NMatrix NMatrix::lupL() {
    if(_a == nullptr) { lupUpdate(); }

    assert(_a != nullptr);

    NMatrix l = _a->lower();
    for(ul_t i = 0; i < _a->_n; ++i) {
        l(i, i) = 1.0;
    }

    if(_a->_n != _n) {
        lupClear();
        setDefaultBrowseIndices();
    }
    return l;
}

NMatrix NMatrix::lupU() {
    if(_a == nullptr) { lupUpdate(); }

    assert(_a != nullptr);

    NMatrix u = _a->upper();

    if(_a->_n != _n) {
        lupClear();
        setDefaultBrowseIndices();
    }
    return u;
}


// OPERATIONS


double NMatrix::trace() const {
    double trace = 0.0;
    for(ul_t i = _i1; i <= _i2; i++) {
        trace += (*this)(i, i);
    }
    setDefaultBrowseIndices();
    return trace;
}

double NMatrix::det() {
    double det = 0.0;
    if(_a == nullptr) { lupUpdate(); }

    if(_a != nullptr) {
        det = (*_a)(0, 0);
        for(ul_t i = 1; i < _a->_n; i++) {
            det *= (*_a)(i, i);
        }
        det = (((*_perm)[_a->_n - 1] - (_a->_n - 1)) % 2 == 0) ? det : -det;

        if(_a->_n != _n) {
            lupClear();
        }
    }
    return det;
}


NMatrix NMatrix::operator+(const NMatrix &m) const {
    return NPMatrix<double>::operator+(m);
}

NMatrix NMatrix::operator-(const NMatrix &m) const {
    return NPMatrix<double>::operator-(m);
}

NMatrix NMatrix::operator-() const {
    return NPMatrix<double>::operator-();
}

NMatrix operator*(double s, const NMatrix &m) {
    NMatrix res{m};
    res *= s;
    return res;
}

NMatrix operator*(const NMatrix &m, double s) {
    return s * m;
}

NMatrix NMatrix::operator*(const NMatrix &m) const {
    return NPMatrix<double>::operator*(m);
}

NMatrix NMatrix::operator/(double s) const {
    return NPMatrix<double>::operator/(s);
}


// OPERATORS


NMatrix operator^(const NPMatrix<double> &m, long exp) {
    NMatrix res{m};
    res ^= exp;
    return res;
}

NVector<double> operator%(NMatrix &matrix, const NVector<double> &vector) {
    NVector<double> b{vector};
    matrix.solve(b);
    matrix.setDefaultBrowseIndices();
    return b;
}

NVector<double> &NMatrix::operator^=(const long exp) {
    pow(exp);
    setDefaultBrowseIndices();
    return *this;
}

double &NMatrix::operator()(ul_t i, ul_t j) {
    return NPMatrix<double>::operator()(i, j);
}

double NMatrix::operator()(ul_t i, ul_t j) const {
    return NPMatrix<double>::operator()(i, j);
}

NMatrix NMatrix::operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) const {
    assert(_i2 - _i1 == _j2 - _j1);
    return NPMatrix<double>::operator()(i1, j1, i2, j2);
}

NMatrix &NMatrix::operator()(ul_t i1, ul_t j1, ul_t i2, ul_t j2) {
    assert(_i2 - _i1 == _j2 - _j1);
    NPMatrix<double>::operator()(i1, j1, i2, j2);
    return *this;
}

// STATIC FUNCTIONS


NMatrix NMatrix::eye(ul_t n) {
    NMatrix eye = NPMatrix<double>::zeros(n);
    for (ul_t k = 0; k < eye.n(); ++k) {
        eye(k, k) = 1.0;
    }
    return eye;
}

NMatrix NMatrix::diag(const std::vector<double> &data, ul_t n) {
    NMatrix diag = NPMatrix<double>::zeros(n);
    for (ul_t k = 0; k < n; ++k) {
        diag(k, k) = data[k];
    }
    return diag;
}

NMatrix NMatrix::scalar(double s, ul_t n) {
    return s * NMatrix::eye(n);
}

//Returns a n-diagonal matrix filled with arr bi-dimensional array : arr[l] is the values of coefficients of the l-th
//diagonal from the left. arr[middle] is the values of coefficients on the diagonal.
NMatrix NMatrix::ndiag(const std::vector<NVector<double>> &data) {
    const auto n = (long) data.size();
    const auto middle = (n - 1) / 2;
    const auto dim = data[middle].dim();
    NPMatrix<double> diag = NPMatrix<double>::zeros(dim);

    for(long l = -middle; l <= middle; l++) {
        for(ul_t k = 0; k < dim - abs(l); k++) {
            if(l < 0) {
                diag(k - l, k) = data[l + middle](k);
            }
            else {
                diag(k , k + l) = data[l + middle](k);
            }
        }
    }
    return diag;
}

NMatrix NMatrix::nscalar(const std::vector<double> &scalars, const ul_t n) {
    const auto scalarSize = (long) scalars.size();
    const long minSize = n - scalarSize;

    std::vector< NVector<double> > diags((ul_t) (2 * scalarSize - 1));
    ul_t size = 1;
    for(ul_t l = 0; l < scalarSize; l++) {
        diags[l] = NVector<double>::scalar(scalars[l], size + minSize);
        if(l > 0) {
            diags[l + scalarSize - 1] = NVector<double>::scalar(scalars[scalarSize - l - 1], n - size + 1);
        }
        size++;
    }
    return NMatrix::ndiag(diags);
}


// PRIVATE ALGEBRAICAL OPERATIONS


void NMatrix::add(const NVector<double> &vector) {
    NVector<double>::add(vector);
    lupClear();
}

void NMatrix::sub(const NVector<double> &vector) {
    NVector<double>::sub(vector);
    lupClear();
}

void NMatrix::opp() {
    NVector<double>::opp();
    lupClear();
}

void NMatrix::prod(double scalar) {
    NVector<double>::prod(scalar);
    lupClear();
}

void NMatrix::div(double scalar) {
    NVector<double>::div(scalar);
    lupClear();
}

void NMatrix::matrixProduct(const NPMatrix<double> &m) {
    NPMatrix<double>::matrixProduct(m);
    lupClear();
}


void NMatrix::pow(const long n) {
    if(n > 0) {
        rPow(n);
    }
    else if(n < 0) {
        inv();
        rPow(-n);
    }
    else {
        *this = NMatrix::eye(_i2 - _i1 + 1);
    }
    lupClear();
}

void NMatrix::rPow(const long n) {
    if(n > 1) {
        const NMatrix copy{this->subMatrix(_i1, _j1, _i2, _j2)};
        (*this)(_i1, _j1, _i2, _j2).matrixProduct(copy);
        if(n % 2 == 0) {
            rPow(n / 2);
        }
        else if(n % 2 == 1) {
            rPow((n - 1) / 2);
            (*this)(_i1, _j1, _i2, _j2).matrixProduct(copy);
        }
    }
}

void NMatrix::inv() {
    ul_t i, j, k, l;

    if(_a == nullptr) { lupUpdate(); }

    if(_a != nullptr) {
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
        if(_a->_n != _n) {
            lupClear();
        }
    }
}

void NMatrix::solve(NVector<double>& vector) {
    ul_t i, l, k;

    if(_a == nullptr) { lupUpdate(); }

    if(_i2 - _i1 + 1 == vector.dim() && _a != nullptr) {
        for(i = 0; i < _a->_n; i++) {
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
        if(_a->_n != _n) {
            lupClear();
        }
    }
}

// LUP MANAGEMENT

void NMatrix::lupUpdate() {
    //Returns PA such as PA = LU where P is a row p array and A = L * U;
    ul_t i, j, k, iMax;

    lupClear();

    _a = new NMatrix(this->subMatrix(_i1, _j1, _i2, _j2));
    auto* p = new std::vector<ul_t>();

    for (i = 0; i <= _a->_n; ++i)
        p->push_back(i); //Unit p permutation, p[i] initialized with i

    if(!_a->isUpper() || !_a->isLower()) {
        for (i = 0; i < _a->_n; ++i) {
            iMax = _a->maxAbsIndexCol(i, i);
            if (abs((*_a)(iMax, i)) > std::numeric_limits<double>::epsilon()) { //matrix is not degenerate
                if (iMax != i) {
                    j = (*p)[i];
                    (*p)[i] = (*p)[iMax];
                    (*p)[iMax] = j;

                    _a->swapRow(i, iMax);

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

void NMatrix::lupClear() {
    if(_a != nullptr) {
        delete _a;
        delete _perm;
        _a = nullptr;
        _perm = nullptr;
    }
}

void NMatrix::copy(const NPMatrix<double> &m) {
    NPMatrix<double>::copy(m);
    lupClear();
}














