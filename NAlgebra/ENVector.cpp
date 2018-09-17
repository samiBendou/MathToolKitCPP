//
// Created by Sami Dahoux on 03/05/2018.
//

#include "ENVector.h"

using namespace std;

ENVector::ENVector(const unsigned long dim) : NVector(dim) {}

ENVector::ENVector(const NVector &vector) : NVector(vector) {}

ENVector::ENVector(const ENVector &vector) : NVector(vector) {}


// OPERATORS


ENVector operator+(const ENVector &v1, const ENVector &v2) {
    ENVector res{v1};
    res.add(v2);
    return res;
}

ENVector operator-(const ENVector &v1, const ENVector &v2) {
    ENVector res{v1};
    res.sub(v2);
    return res;
}

ENVector operator*(double scalar, const ENVector &vector) {
    ENVector res{vector};
    res.prod(scalar);
    return res;
}

ENVector operator*(const ENVector &vector, double scalar) {
    ENVector res{vector};
    res.prod(scalar);
    return res;
}

ENVector operator/(const ENVector &vector, double scalar) {
    ENVector res{vector};
    res.div(scalar);
    return res;
}


// NORM BASED COMPARISON OPERATORS


bool operator==(const ENVector &vector, double scalar) {
    return scalar == 0 && vector.isNull();
}

bool operator!=(const ENVector &vector, double scalar) {
    return !(vector == scalar);
}

bool operator==(const ENVector &v1, const ENVector &v2) {
    return v1.isEqual(v2);
}

bool operator!=(const ENVector &v1, const ENVector &v2) {
    return !(v1 == v2);
}

bool operator<(const ENVector &v1, const ENVector &v2) {
    return v1.norm() < v2.norm();
}

bool operator>(const ENVector &v1, const ENVector &v2) {
    return v2 < v1;
}

bool operator<=(const ENVector &v1, const ENVector &v2) {
    return !(v2 > v1);
}

bool operator>=(const ENVector &v1, const ENVector &v2) {
    return !(v2 < v1);
}


// SCALAR PRODUCT BASED OPERATIONS


double operator!(const ENVector &vector) {
    return vector.norm();
}

double operator*(const ENVector &u, const ENVector &v) {
    return u.dot(v);
}

double operator/(const ENVector &v1, const ENVector &v2) {
    return v1.distance(v2);
}


// STATIC FUNCTIONS


ENVector ENVector::sum(const vector<ENVector> &vectors) {
    vector<NVector> nVectors(vectors.size());
    for (int k = 0; k < vectors.size(); ++k) {
        nVectors[k] = vectors[k];
    }
    return NVector::sum(nVectors);
}

ENVector ENVector::sumProd(const vector<double>& scalars, const vector<ENVector> &vectors) {
    vector<NVector> nVectors(vectors.size());
    for (int k = 0; k < vectors.size(); ++k) {
        nVectors[k] = vectors[k];
    }
    return NVector::sumProd(scalars, nVectors);
}


// PRIVATE METHODS


bool ENVector::isNull() const {
    return norm() < numeric_limits<double>::epsilon();
}

bool ENVector::isEqual(const ENVector& vector) const {
    return distance(vector) < numeric_limits<double>::epsilon();
}

double ENVector::dot(const ENVector &vector) const {
    double dot = 0.0;
    if(dim() == vector.dim()) {
        for (int k = 0; k < dim(); ++k) {
            dot += vector(k) * (*this)(k);
        }
        return dot;
    }
    else
        return nan("");
}

double ENVector::norm() const {
    return sqrt(dot(*this));
}

double ENVector::distance(const ENVector &vector) const {
    return (*this - vector).norm();
}







