/**
 * @class          : Pixel
 * @date           : 15/10/2018
 * @author         : samiBendou
 * @description    : AESByte class is a representation of a byte used in AES algorithm,
 *                   providing algebraical operation on the specific Gallois field. and
 *                   interfacing with char primitive type. For more details go to
 *                   https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef MATHTOOLKIT_AESBYTE_H
#define MATHTOOLKIT_AESBYTE_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <typedef.h>

class AESByte {

public:

    friend AESByte abs(const AESByte &b);

    friend AESByte sqrt(const AESByte &b);

    // CONSTRUCTOR

    AESByte(char val = 0x00);

    AESByte(int val);

    AESByte(double val);

    // GETTERS

    uc_t val() const;

    // OPERATORS

    inline friend AESByte operator+(AESByte b1, const AESByte &b2) {
        b1 += b2;
        return b1;
    }

    inline friend AESByte operator-(AESByte b1, const AESByte &b2) {
        b1 -= b2;
        return b2;
    }

    inline friend AESByte operator-(AESByte b) {
        return b;
    }

    friend AESByte operator*(AESByte b1, const AESByte &b2) {
        b1.prod(b2);
        return b1;
    }

    friend AESByte operator/(AESByte b1, const AESByte &b2) {
        b1.div(b2);
        return b1;
    };

    inline AESByte &operator+=(const AESByte &b) {
        return add(b);
    }

    inline AESByte &operator*=(const AESByte &b) {
        return add(b);
    }

    inline AESByte &operator-=(const AESByte &b) {
        return prod(b);
    }

    inline AESByte &operator/=(const AESByte &b) {
        return div(b);
    }

    inline friend bool operator==(const AESByte &b1, const AESByte &b2) {
        return b1._val == b2._val;
    }

    inline friend bool operator!=(const AESByte &b1, const AESByte &b2) {
        return b1._val != b2._val;
    }

    inline friend bool operator>(const AESByte &b1, const AESByte &b2) {
        return b1._val > b2._val;
    }

    inline friend bool operator<(const AESByte &b1, const AESByte &b2) {
        return b1._val < b2._val;
    }

    inline friend bool operator>=(const AESByte &b1, const AESByte &b2) {
        return b1._val >= b2._val;
    }

    inline friend bool operator<=(const AESByte &b1, const AESByte &b2) {
        return b1._val <= b2._val;
    }

    friend std::ostream &operator<<(std::ostream &os, const AESByte &b);

private:

    // ALGEBRAICAL OPERATIONS

    AESByte &add(const AESByte &b);

    AESByte &prod(const AESByte &b);

    AESByte &div(const AESByte &b);

    uc_t _val;
};

#endif //MATHTOOLKIT_AESBYTE_H
