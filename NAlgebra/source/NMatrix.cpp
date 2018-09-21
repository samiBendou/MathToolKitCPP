//
// Created by Sami Dahoux on 05/05/2018.
//

#include "../header/NMatrix.h"

NMatrix::NMatrix(const NPMatrix &matrix) : NPMatrix(matrix), _a(nullptr), _permutation(nullptr) {

}

NMatrix::NMatrix(const NMatrix &matrix) : NPMatrix(matrix), _a(nullptr), _permutation(nullptr){
    //Hard copy constructor
    if(matrix._a != nullptr && matrix._permutation != nullptr) {
        _a = new NMatrix(*(matrix._a));
        _permutation = new unsigned long[matrix._n];
        std::copy(matrix._permutation, matrix._permutation + matrix._n, _permutation);
    }
}

// CHARACTERIZATION

bool NMatrix::isUpper() const {
    for(unsigned long i = 0; i < _n; i++) {
        for(unsigned long j = 0; j < i; j++) {
            if(abs((*this)(i, j)) > std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}

bool NMatrix::isLower() const {
    for(unsigned long i = 0; i < _n; i++) {
        for(unsigned long j = i + 1; j < _n; j++) {
            if(abs((*this)(i, j)) > std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}

bool NMatrix::isDiagonal() const {
    for(unsigned long i = 0; i < _n; i++) {
        for(unsigned long j =0; j < _n; j++) {
            if(i != j && abs((*this)(i, j)) > std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}


// GETTERS


NMatrix NMatrix::upper() const {
    NMatrix upper = NPMatrix::zeros(_n);
    for(unsigned long i = 0; i < _n; i++) {
        for(unsigned long j = i; j < _n; j++)
            upper(i, j) = (*this)(i, j);
    }
    return upper;
}

NMatrix NMatrix::lower() const {
    NMatrix lower = NPMatrix::zeros(_n);
    for(unsigned long i = 0; i < _n; i++) {
        for(unsigned long j = 0; j <= i; j++)
            lower(i, j) = (*this)(i, j);
    }
    return lower;
}

NMatrix NMatrix::lupL() {
    if(_a == nullptr) { lupUpdate(); }
    NMatrix l = _a->lower();
    for(unsigned long i = 0; i < _n; i++) {
        l(i, i) = 1.0;
    }
    return l;
}

NMatrix NMatrix::lupU() {
    if(_a == nullptr) { lupUpdate(); }
    return _a->upper();
}


// OPERATIONS


double NMatrix::trace() const {
    double trace = 0.0;
    for(unsigned long i = 0; i < _n; i++) {
        trace += (*this)(i, i);
    }
    return trace;
}

double NMatrix::det() {
    double det = 0.0;
    if(_a == nullptr) { lupUpdate(); }

    if(_a != nullptr) {
        det = (*_a)(0, 0);
        for(unsigned long i = 1; i < _n; i++) {
            det *= (*_a)(i, i);
        }
        det = ((_permutation[_n - 1] - (_n - 1)) % 2 == 0) ? det : -det;
    }
    return det;
}

void NMatrix::matrixProduct(const NPMatrix &matrix) {
    NPMatrix::matrixProduct(matrix);
    lupClear();
}


// OPERATORS


NMatrix operator^(const NPMatrix &m, long exp) {
    NMatrix res{m};
    res.pow(exp);
    return res;
}

NVector operator%(NMatrix &matrix, const NVector &vector) {
    NVector b{vector};
    matrix.solve(b);
    return b;
}

NVector &NMatrix::operator^=(const long exp) {
    pow(exp);
    return *this;
}


// STATIC FUNCTIONS


NMatrix NMatrix::eye(unsigned long n) {
    NMatrix eye = NPMatrix::zeros(n);
    for (unsigned long k = 0; k < eye.n(); ++k) {
        eye(k, k) = 1.0;
    }
    return eye;
}

NMatrix NMatrix::diag(const std::vector<double> &data, unsigned long n) {
    NMatrix diag = NPMatrix::zeros(n);
    for (unsigned long k = 0; k < n; ++k) {
        diag(k, k) = data[k];
    }
    return diag;
}

NMatrix NMatrix::scalar(double s, unsigned long n) {
    return s * NMatrix::eye(n);
}

//Returns a n-diagonal matrix filled with arr bi-dimensional array : arr[l] is the values of coefficients of the l-th
//diagonal from the left. arr[middle] is the values of coefficients on the diagonal.
NMatrix NMatrix::nDiag(const std::vector< NVector > & data) {
    const auto n = (long) data.size();
    const auto middle = (n - 1) / 2;
    const auto dim = data[middle].dim();
    NPMatrix diag = NPMatrix::zeros(dim);

    for(long l = -middle; l <= middle; l++) {
        for(unsigned long k = 0; k < dim - abs(l); k++) {
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

NMatrix NMatrix::nScalar(const std::vector<double> & scalars, const unsigned long n) {
    const auto scalarSize = (long) scalars.size();
    const long minSize = n - scalarSize;

    std::vector< NVector > diags((unsigned long) (2 * scalarSize - 1));
    unsigned long size = 1;
    for(unsigned long l = 0; l < scalarSize; l++) {
        diags[l] = NVector::scalar(scalars[l], size + minSize);
        if(l > 0) {
            diags[l + scalarSize - 1] = NVector::scalar(scalars[scalarSize - l - 1], n - size + 1);
        }
        size++;
    }
    return NMatrix::nDiag(diags);
}


// PRIVATE ALGEBRAICAL OPERATIONS


void NMatrix::add(const NVector &vector) {
    NVector::add(vector);
    lupClear();
}

void NMatrix::sub(const NVector &vector) {
    NVector::sub(vector);
    lupClear();
}

void NMatrix::opp() {
    NVector::opp();
    lupClear();
}

void NMatrix::prod(double scalar) {
    NVector::prod(scalar);
    lupClear();
}

void NMatrix::div(double scalar) {
    NVector::div(scalar);
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
        *this = NPMatrix::zeros(_n);
    }
    lupClear();
}

void NMatrix::rPow(const long n) {
    if(n > 1) {
        const NMatrix copy = NMatrix(*this);
        *this *= *this;
        if(n % 2 == 0) {
            rPow(n / 2);
        }
        else if(n % 2 == 1) {
            rPow((n - 1) / 2);
            *this *= copy;
        }
    }
}

void NMatrix::inv() {
    unsigned long i, j, k, l;

    if(_a == nullptr) { lupUpdate(); }

    assert(abs(det()) > std::numeric_limits<double>::epsilon());

    if(det() != 0.0) {
        for (j = 0; j < _n; j++) {
            for (i = 0; i < _n; i++) {
                (*this)(i, j) = ((_permutation[i] == j) ? 1.0 : 0.0);
                for (l = 0; l < i; ++l) {
                    (*this)(i, j) -= (*_a)(i, l) * (*this)(l, j);
                }

            }
            for (i = 0; i < _n; i++) {
                k = _n - 1 - i;
                for (l = k + 1; l < _n; l++) {
                    (*this)(k, j) -= (*_a)(k, l) * (*this)(l, j);
                }
                (*this)(k, j) /= (*_a)(k, k);
            }
        }
        lupClear();
    }
}

void NMatrix::solve(NVector& vector) {
    unsigned long i, l, k;
    if(_a == nullptr) { lupUpdate(); }

    if(_n == vector.dim() && det() != 0.0) {
        for(i = 0; i < _n; i++) {
            vector(i) = vector(_permutation[i]);
            for (l = 0; l < i; ++l) {
                vector(i) -= (*_a)(i, l) * vector(l);
            }
        }
        for (i = 0; i < _n; i++) {
            k = _n - 1 - i;
            for (l = k + 1; l < _n; ++l) {
                vector(k) -= (*_a)(k, l) * vector(l);
            }
            vector(k) /= (*_a)(k, k);
        }
    }
}

// LUP MANAGEMENT

void NMatrix::lupUpdate() {
    //Returns PA such as PA = LU where P is a row p array and A = L + U;
    unsigned long i, j, k, iMax;

    lupClear();
    _a = new NMatrix(*this);
    auto* p = new unsigned long[_n + 1];

    for (i = 0; i <= _n; i++)
        p[i] = i; //Unit p permutation, p[i] initialized with i
    if(!this->isUpper() || !this->isLower()) {
        for (i = 0; i < _n; i++) {
            iMax = _a->maxAbsIndexCol(i, i);
            if (abs((*_a)(iMax, i)) > std::numeric_limits<double>::epsilon()) { //matrix is not degenerate
                if (iMax != i) {
                    i = p[i];
                    p[i] = p[iMax];
                    _a->swapRow(i, iMax);
                    //counting pivots starting from _n (for determinant)
                    p[_n]++;
                }
            }
            for (j = i + 1; j < _n; j++) {
                if(abs((*_a)(i, i)) < std::numeric_limits<double>::epsilon()) {
                    lupClear();
                    return;
                }
                (*_a)(j, i) /= (*_a)(i, i);
                for (k = i + 1; k < _n; k++) {
                    (*_a)(j, k) -= (*_a)(j, i) * (*_a)(i, k);
                }
            }
        }
    }
    _permutation = p;
}

void NMatrix::lupClear() {
    if(_a != nullptr) {
        delete _a;
        delete[] _permutation;
        _a = nullptr;
        _permutation = nullptr;
    }
}

NMatrix operator+(const NMatrix &m1, const NMatrix &m2) {
    NMatrix res{m1};
    if(m1._n == m2._n && m1._p == m2._p)
        res.add(m2);
    return res;
}

NMatrix operator-(const NMatrix &m1, const NMatrix &m2) {
    NMatrix res{m1};
    if(m1._n == m2._n && m1._p == m2._p)
        res.sub(m2);
    return res;
}

NMatrix operator*(double scalar, const NMatrix &matrix) {
    NMatrix res{matrix};
    res.prod(scalar);
    return res;
}

NMatrix operator*(const NMatrix &matrix, double scalar) {
    NMatrix res{matrix};
    res.prod(scalar);
    return res;
}


NMatrix operator*(const NMatrix &m1, const NMatrix &m2) {
    NMatrix res{m1};
    res.matrixProduct(m2);
    return res;
}

NMatrix operator/(const NMatrix &matrix, double scalar) {
    NMatrix res{matrix};
    res.div(scalar);
    return res;
}

NMatrix operator-(const NMatrix &matrix) {
    NMatrix res{matrix};
    res.opp();
    return res;
}

NMatrix operator!(const NMatrix &matrix) {
    NMatrix res{matrix};
    res.transpose();
    return res;
}







