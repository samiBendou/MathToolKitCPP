/**
 * @class          : Vector3
 * @date           : 04/05/2018
 * @author         : samiBendou
 * @description    : Class inheriting from NVector<double> representing 3D Euclidean space. Featuring cross product, coordinate
 *                   transforms and rotations. We will use the following 3D systems of coordinates :
 *
 *                   - X, Y, Z       : Cartesian coordinates.
 *
 *                   - RXY, THETA, Z : Cylindrical coordinates.   |RXY     = sqrt(x2 + y2),
 *                                                                |THETA   = atan(y / x)
 *                                                                |Z       = z
 *
 *                   - R, THETA, PHI : Spherical coordinates.     |R       = sqrt(x2 + y2 + z2),
 *                                                                |THETA   = atan(y / x),
 *                                                                |PHI     = atan(RXY / Z)
 *
 *                   The vector is stored in cartesian coordinates.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_VECTOR3_H
#define MATHTOOLKIT_VECTOR3_H

#include "NVector.h"

class Vector3 : public NVector<double> {
public:

    using NVector<double>::operator=;

    Vector3(const NVector<double> &vector);

    Vector3(const Vector3 &vector);

    explicit Vector3(double x = 0, double y = 0, double z = 0);


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

    /**
     *
     * @return v1 ^ v2 where ^ is vector product between v1 and v2 (cross product).
     */
    friend Vector3 operator^(const Vector3 &v1, const Vector3 &v2);

    /**
     *
     * @return v1 % v2 which is the angle between the two vector.
     */
    friend double operator%(const Vector3 &v1, const Vector3 &v2);
    // Returns angle between v1 & v2

    static Vector3 zeros();

    static Vector3 ones();

    static Vector3 scalar(double scalar);

    static Vector3 canonical(ul_t k);


protected:
    void cross(const Vector3 &vector);

    double angle(const Vector3 &vector) const;

    double pCos(const Vector3 &vector) const;

    double pSin(const Vector3 &vector) const;

    double pTan(const Vector3 &vector) const;
};


#endif //MATHTOOLKIT_VECTOR3_H
