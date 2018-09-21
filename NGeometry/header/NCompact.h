//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NCOMPACT_H
#define MATHTOOLKIT_NCOMPACT_H


#include "NSet.h"

class NCompact : public NSet {
public:
    NCompact(unsigned long dim);

    virtual NCompact* border() const = 0;

    virtual std::vector<NVector> mesh(const NVector& h) const  = 0;
};


#endif //MATHTOOLKIT_NCOMPACT_H
