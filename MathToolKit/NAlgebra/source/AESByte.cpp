//
// Created by Sami Dahoux on 15/10/2018.
//

#include <AESByte.h>

#include "AESByte.h"

AESByte &AESByte::prod(const AESByte &b) {
    AESByte copy_this{*this}, copy_b{b}, res, temp;

    while (copy_this != 0x00) {
        if ((copy_this._val & 0x01) != 0x00) {
            res += copy_b;
        }

        temp._val = static_cast<uc_t>(copy_b._val & 0x80);
        copy_b._val = copy_b._val << 1;
        if (temp != 0x00) {
            copy_b = copy_b + 0x1b;
        }
        copy_this = copy_this._val >> 1;
    }
    *this = res;
    return *this;
}

AESByte &AESByte::div(const AESByte &b) {
    // TODO : Implement real div computing algorithm on GF(2⁸)
    return *this;
}

std::ostream &operator<<(std::ostream &os, const AESByte &b) {
    char buffer[5];
    sprintf(buffer, "0x%02x", (ui_t) b._val);
    os << buffer;
    return os;
}

AESByte sqrt(const AESByte &b) {
    // TODO : Implement real sqrt computing algorithm on GF(2⁸)
    return {(char) sqrt(b._val)};
}










