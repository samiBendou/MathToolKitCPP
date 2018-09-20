#include <iostream>

#include <NVector.h>
#include <ENVector.h>
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
    NPMatrix matrix{{"|1 0 0|",
                     "|0 1 0|",
                     "|0 0 1|"}};
    return 0;
}
