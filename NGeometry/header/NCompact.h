//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NCOMPACT_H
#define MATHTOOLKIT_NCOMPACT_H

#include<iostream>
#include <NVector.h>

class NCompact {
public:
    NCompact(unsigned long dim);

    unsigned long dim() const;

    virtual std::string str() const = 0;

    virtual bool isEmpty() const = 0;

    virtual bool isIn(const vec_t &x) const = 0;

    virtual std::vector<vec_t> uni(const NCompact &set);

    virtual std::vector<vec_t> inter(const NCompact &set);

    virtual int card() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const NCompact &set);

    virtual NCompact *border() const = 0;

    virtual std::vector<vec_t> mesh(const vec_t &h) const = 0;

protected:

    ul_t _dim;
};


#endif //MATHTOOLKIT_NCOMPACT_H
