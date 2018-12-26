/**
 * @class          : Pixel
 * @date           : 19/12/2018
 * @author         : samiBendou
 * @description    : Pixel class is a representation of a pixel providing uses of multiple color scale
 *                   and conversion between theses. The class provides an interface with char primitive
 *                   type by converting a char value onto a grey scale pixel and vice versa if needed.
 *
 *                   A pixel can be in several states usefull for representing pixel on image processing
 *                   calculation :
 *                      - format    : either Red, Green, Blue (RGB) or Grey Scale (GScale).
 *                      - limited   : the value of each component can be limited to be between 0 and 255.
 *                                    If the value of a component is set negative the result is 0. Else,
 *                                    the if the value is greater than MAX_LIMIT_CMP than the set value
 *                                    is the original value mod MAX_LIMIT_CMP + 1.
*                    The pixel is stored in memory as a RGB value even if the format is not RGB. Getting and
 *                   setting components generally implies a calculation to translate between RGB and other
 *                   formats.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_PIXEL_H
#define MATHTOOLKIT_PIXEL_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <typedef.h>

#define MAX_LIMIT_CMP 255

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

    void setRed(int red);

    void setGreen(int green);

    void setBlue(int blue);

    void setGrey(int grey);

    void setRGB(int red, int green, int blue);

    void setLimited(bool limited);

    // MANIPULATORS

    void limit();

    void conformFormatTo(const Pixel &p);

    // OPERATORS

    friend Pixel operator+(const Pixel &p1, const Pixel &p2);

    friend Pixel operator-(const Pixel &p1, const Pixel &p2);

    Pixel operator-() const;

    friend Pixel operator*(const Pixel &p1, const Pixel &p2);

    friend Pixel operator/(const Pixel &p1, const Pixel &p2);

    Pixel &operator+=(const Pixel &p);

    Pixel &operator*=(const Pixel &p);

    Pixel &operator-=(const Pixel &p);

    Pixel &operator/=(const Pixel &p);

    friend bool operator==(const Pixel &p, int val);

    friend bool operator==(const Pixel &p1, const Pixel &p2);

    friend bool operator!=(const Pixel &p1, const Pixel &p2);

    friend bool operator>(const Pixel &p1, const Pixel &p2);

    friend bool operator<(const Pixel &p1, const Pixel &p2);

    friend bool operator>=(const Pixel &p1, const Pixel &p2);

    friend bool operator<=(const Pixel &p1, const Pixel &p2);

    friend std::ostream &operator<<(std::ostream &os, const Pixel &p);

private:

    // ALGEBRAICAL OPERATIONS

    void add(const Pixel &p);

    void sub(const Pixel &p);

    void opp();

    void prod(const Pixel &p);

    void div(const Pixel &p);

    bool isEqual(int val) const;

    int limitCmpIfLimited(int cmp) const;

    void setRGBWithoutFormatChange(int red, int green, int blue);

    int _red;
    int _green;
    int _blue;

    Format _format;
    bool _limited;
};


#endif //MATHTOOLKIT_PIXEL_H
