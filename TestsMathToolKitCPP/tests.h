//
// Created by Sami Dahoux on 09/05/2018.
//

#ifndef MATHTOOLKIT_TESTS_H
#define MATHTOOLKIT_TESTS_H

#include <iostream>

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

bool testNConstantField();
bool testSNewtonianField();

bool testODESolver();

#endif //MATHTOOLKIT_TESTS_H
