//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_NCOMPACT_H
#define MATHTOOLKIT_NCOMPACT_H


#include "NSet.h"

class NCompact : public NSet {
public:
    NCompact(int dim);

    virtual NCompact* border() const = 0;

    virtual std::vector<ENVector> mesh(const ENVector& h) const  = 0;
};


#endif //MATHTOOLKIT_NCOMPACT_H
