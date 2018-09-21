//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_SET_H
#define MATHTOOLKIT_SET_H

#include "../../NAlgebra/header/NVector.h"

class NSet {
public:
    explicit NSet(unsigned long dim);

    ~NSet();

    unsigned long dim() const;

    virtual std::string str() const = 0;

    virtual bool isEmpty() const = 0;

    virtual bool isIn(const NVector& x) const = 0;

    virtual void uni(const NSet* set) = 0;

    virtual void inter(const NSet* set) = 0;

    virtual int card() const = 0;

    friend std::ostream & operator<<(std::ostream& os, const NSet& set);
protected:
    unsigned long _dim;
};


#endif //MATHTOOLKIT_SET_H
