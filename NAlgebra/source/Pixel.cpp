//
// Created by Bendou on 19/12/2018.
//

#include <Pixel.h>

Pixel::Pixel(Pixel::Format format, bool limited) : _red(0), _green(0), _blue(0),
                                                   _format(format), _limited(limited) {

}


Pixel::Pixel(int grey, bool limited) : _red(grey), _green(grey), _blue(grey),
                                       _format(GScale), _limited(limited) {

}

Pixel::Pixel(int red, int green, int blue, bool limited) : _red(red), _green(green), _blue(blue),
                                                           _format(RGB), _limited(limited) {

}

int Pixel::red() const {
    return _red;
}

int Pixel::green() const {
    return _green;
}

int Pixel::blue() const {
    return _blue;
}

int Pixel::grey() const {
    return (_red + _green + _blue) / 3;
}

bool Pixel::limited() const {
    return _limited;
}

Pixel::Format Pixel::format() const {
    return _format;
}

void Pixel::setRed(int red) {
    _red = limitCmpIfLimited(red);
    _format = RGB;
}

void Pixel::setGreen(int green) {
    _green = limitCmpIfLimited(green);
    _format = RGB;
}

void Pixel::setBlue(int blue) {
    _blue = limitCmpIfLimited(blue);
    _format = RGB;
}

void Pixel::setGrey(int grey) {
    setRGBWithoutFormatChange(grey, grey, grey);
    _format = GScale;
}

void Pixel::setRGB(int red, int green, int blue) {
    setRGBWithoutFormatChange(red, green, blue);
    _format = RGB;
}

void Pixel::setLimited(bool limited) {
    if (limited)
        limit();
    else
        _limited = false;
}

void Pixel::limit() {
    _limited = true;
    setRGBWithoutFormatChange(_red, _green, _blue);
}

void Pixel::conformFormatTo(const Pixel &p) {
    if (_format == GScale && p._format == GScale)
        _format = GScale;
    else if (_format == RGB)
        _format = RGB;
}

Pixel operator+(const Pixel &p1, const Pixel &p2) {
    Pixel res{p1};
    res += p2;
    return res;
}


Pixel operator-(const Pixel &p1, const Pixel &p2) {
    Pixel res{p1};
    res -= p2;
    return res;
}

Pixel Pixel::operator-() const {
    Pixel res{*this};
    res.opp();
    return res;
}

Pixel operator*(const Pixel &p1, const Pixel &p2) {
    Pixel res{p1};
    res.prod(p2);
    return res;
}

Pixel operator/(const Pixel &p1, const Pixel &p2) {
    Pixel res{p1};
    res.div(p2);
    return res;
}

Pixel &Pixel::operator+=(const Pixel &p) {
    add(p);
    return *this;
}

Pixel &Pixel::operator*=(const Pixel &p) {
    prod(p);
    return *this;
}

Pixel &Pixel::operator-=(const Pixel &p) {
    sub(p);
    return *this;
}

Pixel &Pixel::operator/=(const Pixel &p) {
    div(p);
    return *this;
}

bool operator==(const Pixel &p, int val) {
    return p.isEqual(val);
}


bool operator==(const Pixel &p1, const Pixel &p2) {
    return (p1 - p2) == 0;
}

bool operator!=(const Pixel &p1, const Pixel &p2) {
    return !(p1 == p2);
}


bool operator<=(const Pixel &p1, const Pixel &p2) {
    return p1.grey() <= p2.grey();
}

bool operator<(const Pixel &p1, const Pixel &p2) {
    return p1.grey() < p2.grey();
}

bool operator>(const Pixel &p1, const Pixel &p2) {
    return p1.grey() > p2.grey();
}

bool operator>=(const Pixel &p1, const Pixel &p2) {
    return p1.grey() >= p2.grey();
}

std::ostream &operator<<(std::ostream &os, const Pixel &p) {
    switch (p._format) {
        case Pixel::RGB :
            os << "RGB : (" << p._red << ", " << p._green << ", " << p._blue << ")";
            break;
        default :
            os << p._red;
            break;
    }
    return os;
}


Pixel abs(const Pixel &p) {
    Pixel p_limited = p;
    p_limited.limit();
    return p_limited;
}

Pixel sqrt(const Pixel &p) {
    Pixel p_sqrt = p;
    p_sqrt.setRGBWithoutFormatChange((int) floor(sqrt(p._red)), (int) floor(sqrt(p._green)),
                                     (int) floor(sqrt(p._blue)));
    return p_sqrt;
}

void Pixel::add(const Pixel &p) {
    setRGBWithoutFormatChange(_red + p._red, _green + p._green, _blue + p._blue);
    conformFormatTo(p);
}

void Pixel::sub(const Pixel &p) {
    setRGBWithoutFormatChange(_red - p._red, _green - p._green, _blue - p._blue);
    conformFormatTo(p);
}

void Pixel::opp() {
    setRGBWithoutFormatChange(-_red, -_green, -_blue);
}

void Pixel::prod(const Pixel &p) {
    setRGBWithoutFormatChange(_red * p._red, _green * p._green, _blue * p._blue);
    conformFormatTo(p);
}

void Pixel::div(const Pixel &p) {
    setRGBWithoutFormatChange(_red / p._red, _green / p._green, _blue / p._blue);
    conformFormatTo(p);
}

bool Pixel::isEqual(int val) const {
    if (val == 0) {
        return _red == 0 && _green == 0 && _blue == 0;
    } else if (_format == Pixel::GScale) {
        return _red == val;
    } else return false;
}

int Pixel::limitCmpIfLimited(int cmp) const {
    if (_limited)
        return cmp > 0 ? cmp % (MAX_LIMIT_CMP + 1) : 0;
    else return cmp;
}

void Pixel::setRGBWithoutFormatChange(int red, int green, int blue) {
    _red = limitCmpIfLimited(red);
    _blue = limitCmpIfLimited(green);
    _green = limitCmpIfLimited(blue);
}



