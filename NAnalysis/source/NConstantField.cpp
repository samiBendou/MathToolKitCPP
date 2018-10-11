//
// Created by Sami Dahoux on 07/05/2018.
//

#include "../header/NConstantField.h"

NConstantField::NConstantField(NCompact *domain, const NVector<double> &cst) : NPField(domain, cst.dim()), _cst(cst) {

}

NVector<double> NConstantField::g(const NVector<double> &x) {
    return _cst;
}


