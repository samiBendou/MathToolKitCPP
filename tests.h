//
// Created by Sami Dahoux on 09/05/2018.
//

#ifndef MATHTOOLKIT_TESTS_H
#define MATHTOOLKIT_TESTS_H

#include <iostream>
#include "NAlgebra/header/NVector.h"
#include "NAlgebra/header/ENVector.h"
#include "NAlgebra/header/Vector3.h"
#include "NAlgebra/header/NPMatrix.h"
#include "NAlgebra/header/NMatrix.h"
#include "NGeometry/header/NSegment.h"
#include "NGeometry/header/NParallelepiped.h"
#include "NGeometry/header/NDSet.h"
#include "NAnalysis/header/NConstantField.h"
#include "NAnalysis/header/NOde.h"
#include "NAnalysis/header/SNewtonianField.h"

bool testNVectorAlgebra();
bool testNVectorMaxMin();
bool testNVectorSwap();
bool testNVectorShift();
bool testNVectorSubVectors();
bool testNVectorFunctionOp();
bool testNVectorCopy();
bool testENVector();
bool testVector3();

bool testNPMatrixAlgebra();
bool testNPMatrixMaxMin();
bool testNPMatrixSwap();
bool testNPMatrixShift();
bool testNPMatrixSubs();
bool testNPMatrixFunctionOp();

bool testNMatrixAlgebra();
bool testNMatrixLUP();
bool testNMatrixInv();
bool testNMatrixDet();
bool testNMatrixSolve();

bool testNConstantField();
bool testSNewtonianField();

bool testODESolver();

#endif //MATHTOOLKIT_TESTS_H
