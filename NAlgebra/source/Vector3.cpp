//
// Created by Sami Dahoux on 04/05/2018.
//

#include "../header/Vector3.h"

Vector3::Vector3(const NVector &vector) : NVector(vector) {

}

Vector3::Vector3(const Vector3 &vector) = default;

Vector3::Vector3(double x, double y, double z) : NVector(3) {
    setXYZ(x, y, z);
}

double Vector3::x() const {
    return (*this)[0];
}

double Vector3::y() const {
    return (*this)[1];
}

double Vector3::z() const {
    return (*this)[2];
}

double Vector3::r() const {
    return !(*this);
}

double Vector3::theta() const {
    return atan2(y(), x());
}

double Vector3::phi() const {
    return atan2(!rXY(), z());
}

Vector3 Vector3::rXY() const {
    return Vector3(x(), y(), 0.0);
}

void Vector3::setX(double scalar) {
    (*this)[0] = scalar;
}

void Vector3::setY(double scalar) {
    (*this)[1] = scalar;
}

void Vector3::setZ(double scalar) {
    (*this)[2] = scalar;
}

void Vector3::setR(double scalar) {
    setRThetaPhi(scalar, theta(), phi());
}

void Vector3::setTheta(double scalar) {
    setRThetaPhi(r(), scalar, phi());
}

void Vector3::setPhi(double scalar) {
    setRThetaPhi(r(), theta(), scalar);
}

void Vector3::setXYZ(double x, double y, double z) {
    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

void Vector3::setRThetaZ(double r, double theta, double z) {
    setXYZ(r * cos(theta), r * sin(theta), z);
}

void Vector3::setRThetaPhi(double r, double theta, double phi) {
    setXYZ(r * sin(phi) * cos(theta), r * sin(phi) * sin(theta), r * cos(phi));
}


Vector3 operator^(const Vector3 &v1, const Vector3 &v2) {
    Vector3 res{v1};
    res.cross(v2);
    return res;
}

double operator%(const Vector3 &v1, const Vector3 &v2) {
    return v1.angle(v2);
}


Vector3 Vector3::zeros() {
    return Vector3(NVector::zeros(3));
}

Vector3 Vector3::ones() {
    return Vector3(NVector::ones(3));
}

Vector3 Vector3::scalar(double scalar) {
    return Vector3(NVector::scalar(scalar, 3));
}

Vector3 Vector3::canonical(ul_t k) {
    return Vector3(NVector::canonical(k, 3));
}

void Vector3::cross(const Vector3 &vector) {
    double xCross = y() * vector.z() - z() * vector.y();
    double yCross = z() * vector.x() - x() * vector.z();
    double zCross = x() * vector.y() - y() * vector.x();
    setXYZ(xCross, yCross, zCross);
}

double Vector3::angle(const Vector3 &vector) const {
    return atan(pTan(vector));
}

double Vector3::pCos(const Vector3 &vector) const {
    if (*this != 0 && vector != 0)
        return ((*this) | vector) / (!(*this) * !vector);
    else return 1.0;
}

double Vector3::pSin(const Vector3 &vector) const {
    if (*this != 0 && vector != 0)
        return !((*this) ^ vector) / (!(*this) * !vector);
    else return 0.0;
}

double Vector3::pTan(const Vector3 &vector) const {
    return pSin(vector) / pCos(vector);
}




