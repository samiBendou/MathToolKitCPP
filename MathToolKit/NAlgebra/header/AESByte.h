#ifndef MATHTOOLKIT_AESBYTE_H
#define MATHTOOLKIT_AESBYTE_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <typedef.h>

/**
 * @ingroup NAlgebra
 * @{
 * @class   AESByte
 * @copyright Dahoux Sami 2018 All rights reserved.
 * @date    15/10/2018
 * @author  samiBendou
 * @brief   Representation of a byte in AES.
 *
 * @details Byte in AES algorithm can be seen as elements of Gallois's finite field \f$ GF(2^8) \f$.
 *
 *          This class provides algebraical operation on the specific field. and
 *          interfacing with integers primitive types. For more details go to
 *          https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf.
 *
 */

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

/** @} */

#endif //MATHTOOLKIT_AESBYTE_H
