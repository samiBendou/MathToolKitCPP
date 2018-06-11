#include <iostream>

#include "tests.h"
#include "ConsoleMenu.h"

using namespace std;

int launchTestODESolver() {
    testODESolver();
}

int launchTestNParallelepiped() {
    return 0;
}

int launchTestNDSet() {
    return 0;
}

int launchTestNSegment() {
    return 0;
}

int launchTestNField() {
    ConsoleMenu menu{vector<string>{"N Dimensional Constant field",
                                    "R3 Newtonian Field",
                                    "Return"},
                     "VECTOR FIELDS"};

    switch(menu.launch()) {
        case 1:
            return testNConstantField();
        case 2:
            return testSNewtonianField();
        default:
            return 0;
    }
}

int launchTestNMatrix() {

    ConsoleMenu menu{vector<string>{"Algebraical Operations",
                                    "LU Decomposition",
                                    "Inversion",
                                    "Determinant",
                                    "Linear Solving",
                                    "Return"},
                     "SQUARE MATRIX"};

    switch(menu.launch()) {
        case 1:
            return testNMatrixAlgebra();
        case 2:
            return testNMatrixLUP();

        case 3:
            return testNMatrixInv();

        case 4:
            return testNMatrixDet();

        case 5:
            return testNMatrixSolve();
        default:
            return 0;

    }
}

int launchTestNPMatrix() {

    ConsoleMenu menu{vector<string>{"Algebraical Operations",
                                    "Max/Min",
                                    "Swap",
                                    "Shift",
                                    "Setters / Getters / Function Operators",
                                    "Return"},
                     "MATRIX"};

    switch(menu.launch()) {
        case 1:
            return testNPMatrixAlgebra();

        case 2:
            return testNPMatrixMaxMin();

        case 3:
            return testNPMatrixSwap();

        case 4:
            return testNPMatrixShift();

        case 5:
            return testNPMatrixSubs() && testNPMatrixFunctionOp();
        default:
            return 0;

    }
}

int launchTestNVector() {
    ConsoleMenu menu{vector<string>{"Algebraical Operations",
                                    "Max/Min",
                                    "Swap",
                                    "Shift",
                                    "Sub Vectors / Function Operators",
                                    "Affectation / Copy",
                                    "Euclidean Vectors",
                                    "3D Vectors",
                                    "Return"},
                                    "VECTORS"};

        switch(menu.launch()) {
            case 1:
                return testNVectorAlgebra();
                
            case 2:
                return testNVectorMaxMin();
                
            case 3:
                return testNVectorSwap();
                
            case 4:
                return testNVectorShift();
                
            case 5:
                return testNVectorSubVectors() && testNVectorFunctionOp();
                
            case 6:
                return testNVectorCopy();
                
            case 7:
                return testENVector();

            case 8:
                return testVector3();

            default:
                return 0;
                
        }
}

int launchTest() {
    ConsoleMenu menu{vector<string>{ "Vector",
                                     "Matrix",
                                     "Square Matrix",
                                     "Vector Fields",
                                     "Segments",
                                     "Discrete Set",
                                     "Parallelepiped",
                                     "ODE Solver",
                                     "Quit"},
                     "MathToolKit 0.1 TEST PROGRAM"};

    switch (menu.launch()) {
        case 1:
            return launchTestNVector();

        case 2:
            return launchTestNPMatrix();

        case 3:
            return launchTestNMatrix();

        case 4:
            return launchTestNField();

        case 5:
            return launchTestNSegment();

        case 6:
            return launchTestNDSet();

        case 7:
            return launchTestNParallelepiped();

        case 8:
            return launchTestODESolver();

        default:
            return 0;
    }
}

int main() {
    return launchTest();
}

