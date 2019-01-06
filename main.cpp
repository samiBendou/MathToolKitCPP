// Use this file to perform quick tests.

#include <iostream>

#include <NVector.h>
#include <Vector3.h>
#include <NPMatrix.h>
#include <NSegment.h>
#include <NParallelepiped.h>
#include <NDSet.h>
#include <NConstantField.h>
#include <SNewtonianField.h>
#include <NOde.h>

using namespace std;

int main() {

    Vector3 u{0, 2, 3}, v{2, 2, 2};
    (u + v).x();
}
