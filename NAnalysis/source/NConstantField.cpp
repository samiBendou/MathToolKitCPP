//
// Created by Sami Dahoux on 07/05/2018.
//

#include "../header/NConstantField.h"

NConstantField::NConstantField(NCompact* domain, const NVector& cst) : NPField(domain, cst.dim()), _cst(cst) {

}

NVector NConstantField::g(const NVector &x) {
    return _cst;
}


