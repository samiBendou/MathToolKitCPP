//
// Created by Sami Dahoux on 15/10/2018.
//

#ifndef AESTEST_AESBYTE_H
#define AESTEST_AESBYTE_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

typedef unsigned char uc_t;

typedef unsigned int ui_t;

class AESByte {

public:

    friend AESByte abs(const AESByte& b);

    friend AESByte sqrt(const AESByte& b);

    AESByte(char val = 0x00);

    AESByte(int val);

    AESByte(double val);

    uc_t val() const;

    AESByte operator+(const AESByte& b);

    AESByte operator-(const AESByte& b);

    AESByte operator-() const;

    friend AESByte operator*(const AESByte& b1, const AESByte& b2);

    AESByte& operator+=(const AESByte& b);

    AESByte& operator*=(const AESByte& b);

    AESByte&operator -=(const AESByte& b);

    AESByte&operator /=(const AESByte& b);

    friend bool operator==(const AESByte& b1, const AESByte& b2);

    friend bool operator!=(const AESByte& b1, const AESByte& b2);

    friend bool operator>(const AESByte& b1, const AESByte& b2);

    friend bool operator<(const AESByte& b1, const AESByte& b2);

    friend bool operator>=(const AESByte& b1, const AESByte& b2);

    friend bool operator<=(const AESByte& b1, const AESByte& b2);

    friend std::ostream& operator<<(std::ostream& os, const AESByte& b);

private:

    void add(const AESByte& b);

    void prod(const AESByte& b);

    uc_t _val;
};

#endif //AESTEST_AESBYTE_H
