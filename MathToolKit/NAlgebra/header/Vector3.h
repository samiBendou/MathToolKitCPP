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
 *            The vector is stored in cartesian coordinates. Getting and
 *            setting components generally implies a constant time calculation to translate between cartesian
 *            and other formats.
 *
 *            The `Vector3` class doesn't support function operator `NVector::operator()()`.
 *
 */

class Vector3 : public NVector<double> {
public:

    using NVector::operator=;

    using NVector::NVector;

    explicit Vector3(double x = 0, double y = 0, double z = 0) : NVector(3) { setXYZ(x, y, z); }

    //3D COORDINATES GETTERS

    inline double x() const { return (*this)[0]; }

    inline double y() const { return (*this)[1]; }

    inline double z() const { return (*this)[2]; }

    inline double r() const { return !(*this); };

    inline double theta() const { return atan2(y(), x()); }

    inline double phi() const { return atan2(!rXY(), z()); }

    inline Vector3 rXY() const { return Vector3(x(), y(), 0.0); }

    //3D COORDINATES SETTERS

    inline void setX(double scalar) { (*this)[0] = scalar; }

    inline void setY(double scalar) { (*this)[1] = scalar; }

    inline void setZ(double scalar) { (*this)[2] = scalar; }

    inline void setR(double scalar) { setRThetaPhi(scalar, theta(), phi()); }

    inline void setTheta(double scalar) { setRThetaPhi(r(), scalar, phi()); }

    inline void setPhi(double scalar) { setRThetaPhi(r(), theta(), scalar); }

    inline void setXYZ(double x, double y, double z) {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    };

    inline void setRThetaZ(double r, double theta, double z) {
        setXYZ(r * cos(theta),
               r * sin(theta),
               z);
    };

    inline void setRThetaPhi(double r, double theta, double phi) {
        setXYZ(r * sin(phi) * cos(theta),
               r * sin(phi) * sin(theta),
               r * cos(phi));
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

    inline friend Vector3 operator*(double s, Vector3 u) {
        u *= s;
        return u;
    }

    inline friend Vector3 operator*(const Vector3 &u, double s) {
        return s * u;
    }

    inline friend Vector3 operator/(Vector3 u, double s) {
        u /= s;
        return u;
    }

    inline friend double operator|(const Vector3 &u, const Vector3 &v) { return u.dotProduct(v); }

    inline friend double operator!(const Vector3 &u) { return u.norm(); }

    inline friend double operator/(const Vector3 &u, const Vector3 &v) { return u.distance(v); }


    /**
     * @brief Vector product between two vectors
     * @details usual vector product given by :
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
     * @brief Angle between two vectors.
     * @return value of the angle.
     */
    inline friend double operator%(const Vector3 &u, const Vector3 &v) {return u.angle(v);}


    inline Vector3& operator ^=(const Vector3 &u) {return cross(u);}

    inline static Vector3 zeros() {return Vector3(NVector::zeros(3));}

    inline static Vector3 ones() {return Vector3(NVector::ones(3));}

    inline static Vector3 scalar(double scalar) {return Vector3(NVector::scalar(scalar, 3));}

    inline static Vector3 canonical(ul_t k) {return Vector3(NVector::canonical(k, 3));}


protected:
    Vector3& cross(const Vector3 &u) {
        setXYZ(y() * u.z() - z() * u.y(),
               z() * u.x() - x() * u.z(),
               x() * u.y() - y() * u.x());
        return *this;
    }

    double angle(const Vector3 &vector) const {return atan(pTan(vector));}

    double pCos(const Vector3 &vector) const {return ((*this != 0 && vector != 0) ? ((*this) | vector) / (!(*this) * !vector) : 1.0);};

    double pSin(const Vector3 &vector) const {return ((*this != 0 && vector != 0) ? !((*this) ^ vector) / (!(*this) * !vector) : 0.0);};

    double pTan(const Vector3 &vector) const {return pSin(vector) / pCos(vector);};
};

/** @} */


#endif //MATHTOOLKIT_VECTOR3_H
