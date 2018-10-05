//
// Created by Sami Dahoux on 09/05/2018.
//
#include "tests.h"
#define DIM_TEST 3

using namespace std;

const NVector testVector = NVector::canonical(1, DIM_TEST) + 2 * NVector::canonical(2, DIM_TEST);


bool testNMatrixAlgebra() {
    cout << endl << "*** ALGEBRAICAL OPERATIONS ***" << endl << endl;
    
    NMatrix matrix = NMatrix::diag(vector<double>{1, 2, 1}, DIM_TEST);

    cout << "matrix : " << matrix << endl;
    cout << "matrix ^ 2 : " << (matrix ^ 2) << endl;
    return false;
}

bool testNMatrixLUP() {
    cout << endl << "**** LUP ****" << endl;

    NMatrix matrix = NMatrix::nScalar({-1, 2}, 3);
    NMatrix matrixLupL = matrix.lupL();
    NMatrix matrixLupU = matrix.lupU();

    cout << "matrix : " << matrix << endl;
    cout << "matrix.lupL() : " << matrixLupL << endl;
    cout << "matrix.lupU() : " << matrixLupU << endl;
    cout << "matrix.lupL() * matrix.lupP() = " << (matrixLupL * matrixLupU) << endl;

    return false;
}

bool testNMatrixInv() {
    cout << endl << "**** INV ****" << endl;

    NMatrix matrix = NMatrix::nScalar({-1, 2}, 3);
    cout << "matrix : " << matrix << endl;
    cout << "matrix ^ -1 : " << (matrix ^ -1) << endl;
    cout << "matrix ^ -1 * matrix : " << (matrix ^ -1) * matrix << endl;
    return false;
}

bool testNMatrixDet() {
    cout << endl << "**** DET ****" << endl;

    NMatrix matrix1 = NMatrix::nScalar({-1, 2}, 3);
    NMatrix matrix2 = NMatrix::nScalar({-3, 2}, 3);

    cout << "matrix1 : " << matrix1 << endl;
    cout << "matrix2 : " << matrix2 << endl;
    cout << "matrix1.det() : " << matrix1.det() << endl;
    cout << "matrix2.det() : " << matrix2.det() << endl;
    cout << "(matrix1 ^ -1).det() : " << (matrix1 ^-1).det() << endl;
    cout << "(matrix1 * matrix2).det() : " << (matrix1 * matrix2).det() << endl;
    return false;
}

bool testNMatrixSolve() {
    cout << endl << "**** SOLVE ****" << endl;

    NMatrix matrix = NMatrix::nScalar({-1, 2}, 3);
    ENVector vector = ENVector::ones(3);

    cout << "matrix : " << matrix << endl;
    cout << "vector : " << vector << endl;
    cout << "matrix % vector : " << (matrix % vector) << endl;
    cout << "matrix * (matrix % vector)) : " << (matrix * (matrix % vector)) << endl;
    return false;
}

bool testNConstantField() {
    cout << endl<< "**** CONSTANT FIELD ****" << endl << endl;
    NMatrix base = NMatrix::scalar(5, 3);
    vector<ENVector> baseCols = base.cols();
    ENVector pos = NVector::zeros(3);
    ENVector dx = NVector::scalar(1.0 / 3.0, 3);
    NParallelepiped para{base, pos};
    cout << "para : " << para << endl;
    NConstantField field{&para, Vector3(0, 0, 9.81)};
    field.h = dx;
    cout << "field.meshMatrix() : " << field.meshMatrix() << endl;

    return false;
}

bool testSNewtonianField() {
    cout << endl<< "**** NEWTONIAN FIELD ****" << endl << endl;
    const double sunMass = 1.9891e+30, earthSunDistance = 1.47098074e+11; //earthSpd = 3.0287e+4;

    NMatrix base = NMatrix::scalar(1 * earthSunDistance, 3);
    vector<ENVector> baseCols = base.cols();
    ENVector pos = NVector::zeros(3);
    ENVector dx = NVector::scalar(1.0 / 3, 3);
    NParallelepiped para{base, pos};

    cout << "para : " << para << endl;

    cout << "Earth-Sun system simulation" << endl;

    std::vector<double> mass{sunMass};
    std::vector<Vector3> r{Vector3(0, 0, 0), Vector3(earthSunDistance, 0, 0)};
    SNewtonianField field{&para, -6.67408e-11, mass, r};
    field.h = dx;
    cout << "field.meshMatrix() : " << field.meshMatrix() << endl;
    cout << "field(earth) : " << field(Vector3(earthSunDistance, 0, 0)) << endl;
    return false;
}

bool testODESolver() {
    /*
    cout << endl<< "**** ODE SOLVER ****" << endl << endl;
    NConstantField f{Vector3(0, 0, 9.81)};
    std::vector<ENVector> solution = NOde::euler(ENVector::zeros(6), f);
    for (int k = 0; k <solution.size(); ++k) {
        cout << "solution " << k << " : " << solution[k] << endl;
    }
    NPMatrix matSol{solution};
    cout << matSol << endl;
*/
    return false;
}

// LAUNCH TESTS

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






