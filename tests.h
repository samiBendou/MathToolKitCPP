//
// Created by Sami Dahoux on 09/05/2018.
//

#ifndef MATHTOOLKIT_TESTS_H
#define MATHTOOLKIT_TESTS_H

#include <iostream>

#include "ConsoleMenu.h"

#include <NVector.h>
#include <Vector3.h>
#include <NPMatrix.h>
#include <NMatrix.h>
#include <NSegment.h>
#include <NParallelepiped.h>
#include <NDSet.h>
#include <NConstantField.h>
#include <SNewtonianField.h>
#include <NOde.h>


bool testNMatrixAlgebra();
bool testNMatrixLUP();
bool testNMatrixInv();
bool testNMatrixDet();
bool testNMatrixSolve();

bool testNConstantField();
bool testSNewtonianField();

bool testODESolver();

int launchTestODESolver();
int launchTestNParallelepiped();
int launchTestNDSet();
int launchTestNSegment();
int launchTestNField();
int launchTestNMatrix();
int launchTestNPMatrix();
int launchTestNVector();
int launchTest();

#endif //MATHTOOLKIT_TESTS_H
