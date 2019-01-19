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

Pixel &Pixel::setLimited(bool limited) {
    if (limited)
        limit();
    else
        _limited = false;
    return *this;
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

bool Pixel::isEqual(int val) const {
    if (_format == Pixel::RGB && val == 0) {
        return _red == 0 && _green == 0 && _blue == 0;
    } else if (_format == Pixel::GScale) {
        return _red == val;
    } else return false;
}

void Pixel::conformFormatTo(const Pixel &p) {
    if (_format == GScale && p._format == GScale)
        _format = GScale;
    else if (_format == RGB)
        _format = RGB;
}



