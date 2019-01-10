#ifndef MATHTOOLKIT_VECTOR3_H
#define MATHTOOLKIT_VECTOR3_H

#include <NVector.h>

/**
 * @ingroup NAlgebra
 * @{
 * @class   Vector3
 * @copyright Dahoux Sami 2018 All rights reserved.
 * @date    04/05/2018
 * @author  samiBendou
 * @brief   Class representing 3D Euclidean space.
 *
 * @details Featuring cross product, coordinate transforms and rotations.
 * We will use the following 3D systems of coordinates :
 *
 *            - \f$ \vec{u} = (x, y, z) \f$ Cartesian coordinates.
 *
 *            - \f$ \vec{u} = (r_{xy}, \theta, z) \f$ Cylindrical coordinates. We have the following transformations :
 *
 *            \f[
 *              \begin{align*}
 *                  & r_{xy}    & = & \sqrt{x^2 + y^2} \\
 *                  & \theta    & = & atan(y / x) \\
 *                  & z         & = & z \\
 *              \end{align*}
 *            \f]
 *
 *            - \f$ \vec{u} = (r, \theta, \phi) \f$ Spherical coordinates. We have the following transformations :
 *
 *            \f[
 *            \begin{align*}
 *                  & r         & = & \sqrt{x^2 + y^2 + z^2} \\
 *                  & \theta    & = & atan(y / x) \\
 *                  & \phi      & = & atan(r_{xy} / z) \\
 *            \end{align*}
 *            \f]
 *
 *            The u is stored in cartesian coordinates. Getting and
 *            setting components generally implies a constant time calculation to translate between cartesian
 *            and other formats.
 *
 *            The `Vector3` class doesn't support function operator `NVector::operator()()`.
 *
 */

class Vector3 : public NVector<double_t> {
public:

    using NVector::operator=;

    using NVector::NVector;

    explicit Vector3(double_t x = 0, double_t y = 0, double_t z = 0) : NVector(3) { setXYZ(x, y, z); }

    //3D COORDINATES GETTERS

    inline double_t x() const { return (*this)[0]; }

    inline double_t y() const { return (*this)[1]; }

    inline double_t z() const { return (*this)[2]; }

    inline double_t r() const { return !(*this); };

    inline double_t theta() const { return atan2((double)y(), (double)x()); }

    inline double_t phi() const { return atan2((double)!rXY(), (double)z()); }

    inline Vector3 rXY() const { return Vector3(x(), y(), 0); }

    //3D COORDINATES SETTERS

    inline void setX(double_t scalar) { (*this)[0] = scalar; }

    inline void setY(double_t scalar) { (*this)[1] = scalar; }

    inline void setZ(double_t scalar) { (*this)[2] = scalar; }

    inline void setR(double_t scalar) { setRThetaPhi(scalar, theta(), phi()); }

    inline void setTheta(double_t scalar) { setRThetaPhi(r(), scalar, phi()); }

    inline void setPhi(double_t scalar) { setRThetaPhi(r(), theta(), scalar); }

    inline void setXYZ(double_t x, double_t y, double_t z) {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    };

    inline void setRThetaZ(double_t r, double_t theta, double_t z) {
        setXYZ(r * cos((double) theta),
               r * sin((double) theta),
               z);
    };

    inline void setRThetaPhi(double_t r, double_t theta, double_t phi) {
        setXYZ(r * sin((double) phi) * cos((double) theta),
               r * sin((double) phi) * sin((double) theta),
               r * cos((double) phi));
    }

    inline friend Vector3 operator+(Vector3 u, const Vector3 &v) {
        u += v;
        return u;
    }

    inline friend Vector3 operator-(Vector3 u, const Vector3 &v) {
        u -= v;
        return u;
    }

    inline friend Vector3 operator-(Vector3 u) {
        u.opp();
        return u;
    }

    inline friend Vector3 operator*(double_t s, Vector3 u) {
        u *= s;
        return u;
    }

    inline friend Vector3 operator*(const Vector3 &u, double_t s) {
        return s * u;
    }

    inline friend Vector3 operator/(Vector3 u, double_t s) {
        u /= s;
        return u;
    }

    inline friend double_t operator|(const Vector3 &u, const Vector3 &v) { return u.dotProduct(v); }

    inline friend double_t operator!(const Vector3 &u) { return u.norm(); }

    inline friend double_t operator/(const Vector3 &u, const Vector3 &v) { return u.distance(v); }

    /**
     * @brief Vector product between two us
     * @details usual u product given by :
     *
     * \f[
     * \begin{align*}
     *      & u_y v_z - u_z v_y \\
     *      & u_z v_x - u_x v_z \\
     *      & u_x v_y - u_y v_x \\
     * \end{align*}
     * \f]
     *
     * @return value of \f$ \vec{u} \times \vec{v} \f$.
     */
    inline friend Vector3 operator^(Vector3 u, const Vector3 &v) {
        u ^= v;
        return u;
    }

    /**
     * @brief Angle between two us.
     * @return value of the angle.
     */
    inline friend double_t operator%(const Vector3 &u, const Vector3 &v) {return u.angle(v);}


    inline Vector3& operator ^=(const Vector3 &u) {return cross(u);}

    inline static Vector3 zeros() {return Vector3(NVector::zeros(3));}

    inline static Vector3 ones() {return Vector3(NVector::ones(3));}

    inline static Vector3 scalar(double_t scalar) {return Vector3(NVector::scalar(scalar, 3));}

    inline static Vector3 cano(size_t k) {return Vector3(NVector::cano(k, 3));}


protected:
    Vector3& cross(const Vector3 &u) {
        setXYZ(y() * u.z() - z() * u.y(),
               z() * u.x() - x() * u.z(),
               x() * u.y() - y() * u.x());
        return *this;
    }

    inline double_t angle(const Vector3 &u) const {return atan((double) pTan(u));}

    inline double_t pCos(const Vector3 &u) const {return ((*this != 0 && u != 0) ? ((*this) | u) / (!(*this) * !u) : 1);};

    inline double_t pSin(const Vector3 &u) const {return ((*this != 0 && u != 0) ? !((*this) ^ u) / (!(*this) * !u) : 0);};

    inline double_t pTan(const Vector3 &u) const {return pSin(u) / pCos(u);};
};

/** @} */


#endif //MATHTOOLKIT_VECTOR3_H
