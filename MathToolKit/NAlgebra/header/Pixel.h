#ifndef MATHTOOLKIT_PIXEL_H
#define MATHTOOLKIT_PIXEL_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <typedef.h>

#define MAX_LIMIT_CMP 255

/**
* @ingroup NAlgebra
* @{
*
* @class   Pixel
* @date    19/12/2018
* @author  samiBendou
* @brief   Pixel class is a representation of a pixel providing support of multiple color scale
*          and conversion between theses.
*
* @details The class provides an interface with char primitive
*          type by converting a char value onto a grey scale pixel and vice versa if needed.
*
*          A pixel can be in several states theses can be used for image processing computation :
*             - format    : either Red, Green, Blue (RGB) or Grey Scale (GScale).
*             - limited   : the value of each component can be limited to be between 0 and 255.
*                           If the value of a component is set negative the result is 0. Else,
*                           the if the value is greater than MAX_LIMIT_CMP than the set value
*                           is the original value mod `MAX_LIMIT_CMP + 1`.
*          The pixel is stored in memory as a RGB value even if the format is not RGB. Getting and
*          setting components generally implies a constant time calculation to translate between RGB
*          and other formats.
*
*/

class Pixel {

public:

    enum Format {
        GScale = 1, RGB = 3
    };

    friend Pixel abs(const Pixel &p);

    friend Pixel sqrt(const Pixel &p);

    // CONSTRUCTOR

    explicit Pixel(Format format = GScale, bool limited = false);

    Pixel(int grey, bool limited = false);

    Pixel(int red, int green, int blue, bool limited = false);

    // GETTERS

    int red() const;

    int green() const;

    int blue() const;

    int grey() const;

    bool limited() const;

    Format format() const;

    // SETTERS

    Pixel &setRed(int red);

    Pixel &setGreen(int green);

    Pixel &setBlue(int blue);

    Pixel &setGrey(int grey);

    Pixel &setRGB(int red, int green, int blue);

    Pixel &setLimited(bool limited);

    // OPERATORS

    inline friend Pixel operator+(Pixel p1, const Pixel &p2) {
        p1 += p2;
        return p1;
    }

    inline friend Pixel operator-(Pixel p1, const Pixel &p2) {
        p1 -= p2;
        return p1;
    }

    inline friend Pixel operator-(Pixel p) {
        p.opp();
        return p;
    }

    inline friend Pixel operator*(Pixel p1, const Pixel &p2) {
        p1 *= p2;
        return p1;
    }

    inline friend Pixel operator/(Pixel p1, const Pixel &p2) {
        p1 /= p2;
        return p1;
    }

    inline Pixel &operator+=(const Pixel &p) {
        return add(p);
    }

    inline Pixel &operator*=(const Pixel &p) {
        return prod(p);
    }

    inline Pixel &operator-=(const Pixel &p) {
        return sub(p);
    }

    inline Pixel &operator/=(const Pixel &p) {
        return div(p);
    }

    inline friend bool operator==(const Pixel &p, int val) {
        return p.isEqual(val);
    }

    inline friend bool operator==(const Pixel &p1, const Pixel &p2) {
        return (p1 - p2) == 0;
    }

    inline friend bool operator!=(const Pixel &p1, const Pixel &p2) {
        return !(p1 == p2);
    }

    inline friend bool operator>(const Pixel &p1, const Pixel &p2) {
        return p1.grey() <= p2.grey();
    }

    inline friend bool operator<(const Pixel &p1, const Pixel &p2) {
        return p1.grey() < p2.grey();
    }

    inline friend bool operator>=(const Pixel &p1, const Pixel &p2) {
        return p1.grey() > p2.grey();
    }

    inline friend bool operator<=(const Pixel &p1, const Pixel &p2) {
        return p1.grey() >= p2.grey();
    }

    friend std::ostream &operator<<(std::ostream &os, const Pixel &p);

private:

    // ALGEBRAICAL OPERATIONS

    Pixel &add(const Pixel &p);

    Pixel &sub(const Pixel &p);

    Pixel &opp();

    Pixel &prod(const Pixel &p);

    Pixel &div(const Pixel &p);

    bool isEqual(int val) const;

    int limitCmpIfLimited(int cmp) const;

    Pixel &setRGBWithoutFormatChange(int red, int green, int blue);

    // MANIPULATORS

    void limit();

    void conformFormatTo(const Pixel &p);

    int _red;
    int _green;
    int _blue;

    Format _format;
    bool _limited;
};

/** @} */

#endif //MATHTOOLKIT_PIXEL_H
