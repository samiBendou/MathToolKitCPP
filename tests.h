//
// Created by Sami Dahoux on 09/05/2018.
//

#ifndef MATHTOOLKIT_TESTS_H
#define MATHTOOLKIT_TESTS_H

#include <iostream>
#include "NAlgebra/NVector.h"
#include "NAlgebra/ENVector.h"
#include "NAlgebra/Vector3.h"
#include "NAlgebra/NPMatrix.h"
#include "NAlgebra/NMatrix.h"
#include "NGeometry/NSegment.h"
#include "NGeometry/NParallelepiped.h"
#include "NGeometry/NDSet.h"
#include "NAnalysis/NConstantField.h"
#include "NAnalysis/NOde.h"
#include "NAnalysis/SNewtonianField.h"

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
