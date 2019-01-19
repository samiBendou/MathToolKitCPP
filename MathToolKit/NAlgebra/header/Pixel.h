#ifndef MATHTOOLKIT_PIXEL_H
#define MATHTOOLKIT_PIXEL_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <typedef.h>

#define MAX_LIMIT_CMP (255)

/**
 * @ingroup NAlgebra
 * @{
 * @class   Pixel
 * @copyright Dahoux Sami 2018 All rights reserved.
 * @date    19/12/2018
 * @author  samiBendou
 * @brief   Representation of a pixel.
 *
 * @details Providing multiple color scale and conversion between theses.
 *
 *          The class provides an interface with char primitive
 *          type by converting a char value onto a grey scale pixel and vice versa if needed.
 *
 *          A pixel can be in several states theses can be used for image processing computation :
 *
 *             - `format`    : either Red, Green, Blue (RGB) or Grey Scale (GScale).
 *             - `limited`   : the value of each component can be limited to be between 0 and 255.
 *                             If the value of a component is set negative the result is 0. Else,
 *                             the if the value is greater than MAX_LIMIT_CMP than the set value
 *                             is the original value mod `MAX_LIMIT_CMP + 1`.
 *
 *          The pixel is stored in memory as a RGB value even if the format is not RGB. Getting and
 *          setting components generally implies a constant time calculation to translate between RGB
 *          and other formats.
 *
 */

class Pixel {

public:

    enum Format {
        GScale, RGB
    };

    friend Pixel abs(const Pixel &p);

    friend Pixel sqrt(const Pixel &p);

    // CONSTRUCTOR

    explicit Pixel(Format format = GScale, bool limited = false);

    Pixel(int grey, bool limited = false);

    Pixel(int red, int green, int blue, bool limited = false);

    // GETTERS

    inline int red() const { return _red;}

    inline int green() const { return _green;}

    inline int blue() const { return _blue;}

    inline int grey() const { return (_red + _green + _blue) / 3;}

    inline bool limited() const { return _limited;}

    inline Format format() const { return _format;}

    // SETTERS

    inline Pixel &setRed(int red) { return setRGB(red, _green, _blue);}

    inline Pixel &setGreen(int green) {return setRGB(_red, green, _blue);}


    inline Pixel &setBlue(int blue) {return setRGB(_red, _green, blue);}

    inline Pixel &setGrey(int grey) {
        _format = GScale;
        return setRGBWithoutFormatChange(grey, grey, grey);
    }

    Pixel &setRGB(int red, int green, int blue) {
        _format = RGB;
        return setRGBWithoutFormatChange(red, green, blue);
    }

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
        return p1.grey() > p2.grey();
    }

    inline friend bool operator<(const Pixel &p1, const Pixel &p2) {
        return p1.grey() < p2.grey();
    }

    inline friend bool operator>=(const Pixel &p1, const Pixel &p2) {
        return p1.grey() >= p2.grey();
    }

    inline friend bool operator<=(const Pixel &p1, const Pixel &p2) {
        return p1.grey() <= p2.grey();
    }

    friend std::ostream &operator<<(std::ostream &os, const Pixel &p);

private:

    // ALGEBRAICAL OPERATIONS
    inline Pixel &add(const Pixel &p) {
        conformFormatTo(p);
        return setRGBWithoutFormatChange(_red + p._red, _green + p._green, _blue + p._blue);
    }

    inline Pixel &sub(const Pixel &p) {
        conformFormatTo(p);
        return setRGBWithoutFormatChange(_red - p._red, _green - p._green, _blue - p._blue);
    }

    inline Pixel &opp() {return setRGBWithoutFormatChange(-_red, -_green, -_blue);}

    inline Pixel &prod(const Pixel &p) {
        conformFormatTo(p);
        return setRGBWithoutFormatChange(_red * p._red, _green * p._green, _blue * p._blue);
    }

    inline Pixel &div(const Pixel &p) {
        conformFormatTo(p);
        return setRGBWithoutFormatChange(_red / p._red, _green / p._green, _blue / p._blue);
    }

    bool isEqual(int val) const;

    inline int limitCmpIfLimited(int cmp) const {return _limited ? std::min(abs(cmp), MAX_LIMIT_CMP) : cmp;}

    inline Pixel &setRGBWithoutFormatChange(int red, int green, int blue){
        _red = limitCmpIfLimited(red);
        _blue = limitCmpIfLimited(green);
        _green = limitCmpIfLimited(blue);
        return *this;
    }

    // MANIPULATORS

    inline Pixel& limit() {
        _limited = true;
        return setRGBWithoutFormatChange(_red, _green, _blue);
    }

    void conformFormatTo(const Pixel &p);

    int _red;
    int _green;
    int _blue;

    Format _format;
    bool _limited;
};

/** @} */

#endif //MATHTOOLKIT_PIXEL_H
