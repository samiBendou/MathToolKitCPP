//
// Created by Sami Dahoux on 04/05/2018.
//
//@license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
//@class          : Vector3
//@description    : Module inheriting from ENVector representing 3D Euclidean space. Featuring cross product, coordinate
//                  transforms and rotations.
//
//                  - X, Y, Z       : Cartesian coordinates.
//
//                  - R, THETA, Z   : Cylindrical coordinates.   |R       = RXY = sqrt(x2 + y2),
//                                                               |THETA   = atan(y / x)
//                                                               |Z       = z
//
//                  - R, THETA, PHI : Spherical coordinates.     |R       = sqrt(x2 + y2 + z2),
//                                                               |THETA   = atan(y / x),
//                                                               |PHI     = atan(RXY / Z)

#ifndef MATHTOOLKIT_VECTOR3_H
#define MATHTOOLKIT_VECTOR3_H

#include "ENVector.h"

class Vector3 : public ENVector {
public:

    Vector3(const ENVector& vector);

    Vector3(const Vector3& vector);

    Vector3(double x = 0, double y = 0, double z = 0);


    //3D COORDINATES GETTERS


    double x() const;

    double y() const;

    double z() const;

    double r() const;

    double theta() const;

    double phi() const;

    Vector3 rXY() const;


    //3D COORDINATES SETTERS


    void setX(double scalar);

    void setY(double scalar);

    void setZ(double scalar);

    void setR(double scalar);

    void setTheta(double scalar);

    void setPhi(double scalar);

    void setXYZ(double x, double y, double z);

    void setRThetaZ(double r, double theta, double z);

    void setRThetaPhi(double r, double theta, double phi);

    friend Vector3 operator^(const Vector3& v1, const Vector3& v2);
    // Returns vector product between v1 and v2 (cross product)

    friend double operator%(const Vector3& v1, const Vector3& v2);
    // Returns angle between v1 & v2

    static Vector3 zeros();

    static Vector3 ones();

    static Vector3 scalar(double scalar);

    static Vector3 canonical(unsigned int k);


protected:
    void cross(const Vector3 &vector);

    double angle(const Vector3 &vector) const;

    double pCos(const Vector3 &vector) const;

    double pSin(const Vector3 &vector) const;

    double pTan(const Vector3 &vector) const;
};


#endif //MATHTOOLKIT_VECTOR3_H
