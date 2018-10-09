// Use this file to perform quick tests.

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

using namespace std;

int main() {

    NVector vector{"(0 0 1)"};

    cout << vector << endl;

    return 0;
}
