//
// Created by Sami Dahoux on 09/05/2018.
//
#include "tests.h"
#define DIM_TEST 3

using namespace std;

const NVector testVector = NVector::canonical(1, DIM_TEST) + 2 * NVector::canonical(2, DIM_TEST);

//MOCK Objects : Objets générées speciallement pour les tests
bool testNVectorAlgebra() {
    cout << endl << "**** ALGEBRAICAL OPERATIONS ****" << endl << endl;

    NVector vector1 = testVector;
    NVector vector2 = NVector::ones(DIM_TEST);

    cout << "vector1 : " << vector1 << endl;
    cout << "vector2 : " << vector2 << endl;

    cout << "v1 + v2 : " << (vector1 + vector2) << endl;
    cout << "v1 - v2 : " << (vector1 - vector2) << endl;
    cout << "v2 * 10 : " << (vector2 * 10) << endl;
    cout << "v2 / 10 : " << (vector2 / 10) << endl;

    cout << endl<< "**** COMPOUND OPERATIONS ****" << endl << endl;

    vector1 += 2 * vector2;
    cout << "v1 += 2 * v2 : " << vector1 << endl;

    vector1 *= 2;
    cout << "v1 *= 2 : " << vector1 << endl;
    return false;
}

bool testNVectorMaxMin() {
    cout << endl<< "**** MAX/MIN ****" << endl << endl;

    NVector vector = testVector;

    cout << "vector : " << vector << endl;

    cout << "vector.max() : " << vector.max() << " index : " << vector.maxIndex() << endl;
    cout << "vector.min() : " << vector.min() << " index : " << vector.minIndex() << endl;

    cout << "vector.maxAbs() : " << vector.maxAbs() << " index : " << vector.maxAbsIndex() << endl;
    cout << "vector.minAbs() : " << vector.minAbs() << " index : " << vector.minAbsIndex() << endl;
    return false;
}

bool testNVectorSwap() {
    cout << endl<< "**** SWAP ****" << endl << endl;

    NVector vector = testVector;

    cout << "vector : " << vector << endl;
    vector.swap(0, 1);
    cout << "vector.swap(0, 1) : " << vector << endl;
    return false;
}

bool testNVectorShift() {
    cout << endl<< "**** SHIFT ****" << endl << endl;

    NVector vector = testVector;

    cout << "Vector : " << vector << endl;
    vector.shift(-2);
    cout << "vector.shift(-2) : " << vector << endl;
    return false;
}

bool testNVectorSubVectors() {
    cout << endl<< "**** SUB-VECTORS ****" << endl << endl;

    const NVector vector = testVector;
    NVector subVector = vector(0, 1);

    cout << "vector : " << vector << endl;
    cout << "vector(0, 1) : " << subVector << endl;
    subVector(0, 1) = vector(1, 2);
    cout << "subVector(0, 1) = vector(1, 2) : " << subVector << endl;
    vector(0, 1) = subVector;
    cout << "vector(0, 1) = subVector : " << vector << endl;
    vector;
    cout << "vector(0) = 6 : " << vector << endl;
    return false;
}

bool testNVectorFunctionOp() {
    cout << endl<< "**** FUNCTIONS OPERATORS ****" << endl << endl;
    NVector vector = testVector;
    cout << "vector : " << vector << endl;
    cout << "vector(0) : " << vector(0) << endl;
    return false;
}

bool testNVectorCopy() {
    cout << endl << "*** AFFECTATION/COPY ***" << endl << endl;

    NVector vector1 = 2 * NVector::canonical(0, 3) + 3 * NVector::canonical(1, 3);
    NVector vector2 = 1 * NVector::canonical(2, 3);
    NVector vector3 = 6 * NVector::canonical(2, 3);

    cout << "vector 1 : " << vector1 << endl;
    cout << "vector 2 : " << vector2 << endl;
    cout << "vector 3 : " << vector3 << endl << endl;

    vector2 = vector1;
    vector3 = ENVector(vector1);

    cout << "v2 = v1 : " << vector2 << endl;
    cout << "v3 = ENVector(v1) : " << vector3 << endl;
    vector1 *= 2;
    cout << "v1 *= 2 : " << vector1 << endl;
    cout << "vector 2 : " << vector2 << endl;
    cout << "vector 3 : " << vector3 << endl;
    cout << "v1 = v2 : " << ((vector1 == vector2) ? "true" : "false") << endl;
    cout << "v1 = v3 : " << ((vector1 == vector2) ? "true" : "false") << endl;
    cout << "v2 = v3 : " << ((vector2 == vector3) ? "true" : "false") << endl;
    return false;
}

bool testENVector() {
    cout << endl<< "**** EUCLIDEAN VECTORS ****" << endl << endl;

    ENVector vector1 = NVector::scalar(3, DIM_TEST);
    ENVector vector2 = NVector::scalar(2, DIM_TEST);

    cout << "vector1 : " << vector1 << endl;
    cout << "vector2 : " << vector2 << endl;

    cout << "vector1 * vector2 : " << vector1 * vector2 << endl;
    cout << "vector1 / vector2 : " << vector1 / vector2 << endl;

    cout << "!vector1 : " << !vector1 << endl;
    cout << "!vector2 : " << !vector2 << endl;
    return false;
}

bool testVector3() {
    cout << endl << "*** 3D VECTORS ***" << endl << endl;

    cout << endl << "*** CANONICAL BASE ***" << endl << endl;
    auto* b = new Vector3[3];

    for (unsigned int k = 0; k < 3; ++k) {
        b[k] = Vector3::canonical(k);
        cout << "b" << k << " : " << b[k] << endl;
        cout << "r : " << b[k].r() << endl;
        cout << "theta : " << b[k].theta() << endl;
        cout << "phi : " << b[k].phi() << endl;
    }

    cout << "b0 ^ b1 : " << (b[0] ^ b[1]) << endl;
    cout << "b1 ^ b2 : " << (b[1] ^ b[2]) << endl;
    cout << "b2 ^ b0 : " << (b[2] ^ b[0]) << endl;

    cout << "b0 % b1 : " << b[0] % b[1] << endl;
    cout << "b1 % b2 : " << b[1] % b[2] << endl;
    cout << "b2 % b0 : " << b[2] % b[0] << endl;
    return false;
}


bool testNPMatrixAlgebra() {
    cout << endl << "*** ALGEBRAICAL OPERATIONS ***" << endl << endl;

    NMatrix matrix1 = NMatrix::diag(vector<double>{1, 2, 1}, DIM_TEST);
    NMatrix matrix2 = NPMatrix::ones(DIM_TEST);
    ENVector vector = NVector::scalar(2, DIM_TEST);

    cout << "matrix1 : " << matrix1 << endl;
    cout << "matrix2 : " << matrix2 << endl;
    cout << "vector : " << vector << endl;

    cout << "!m1 : " << (!matrix1) << endl;
    cout << "m1 * m2 : " << (matrix1 * matrix2) << endl;
    cout << "m1 * v : " << (matrix1 * vector) << endl;

    cout << "v * !v : " << (NPMatrix(vector) * !NPMatrix(vector)) << endl;
    cout << "!v * v : " << (!NPMatrix(vector) * NPMatrix(vector)) << endl;
    return false;
}

bool testNPMatrixMaxMin() {
    cout << endl<< "**** MAX/MIN ****" << endl << endl;

    NPMatrix matrix = NMatrix::eye(3);

    cout << "matrix : " << matrix << endl;
    cout << endl << "**** MAX INDEX ROW ****" << endl;
    cout << "matrix.maxAbsIndexRow(0, 0) : " << matrix.maxAbsIndexRow(0) << endl;
    cout << "matrix.maxAbsIndexRow(1, 0) : " << matrix.maxAbsIndexRow(1) << endl;
    cout << "matrix.maxAbsIndexRow(2, 0) : " << matrix.maxAbsIndexRow(2) << endl;

    cout << endl << "**** MAX INDEX COL ****" << endl;
    cout << "matrix.maxAbsIndexCol(0, 0) : " << matrix.maxAbsIndexCol(0) << endl;
    cout << "matrix.maxAbsIndexCol(1, 0) : " << matrix.maxAbsIndexCol(1) << endl;
    cout << "matrix.maxAbsIndexCol(2, 0) : " << matrix.maxAbsIndexCol(2) << endl;

    return false;
}

bool testNPMatrixSwap() {
    cout << endl<< "**** SWAP ****" << endl << endl;

    NMatrix matrix = NMatrix::diag(vector<double>{1, 2, 1}, DIM_TEST);

    cout << "matrix : " << matrix << endl;
    
    matrix.swap(1,1,2,2);
    cout << "matrix.swap(1,1,2,2) : " << matrix << endl;
    matrix.swapCol(0, 1);
    cout << "matrix.swapCol(0, 1) : " << matrix << endl;
    matrix.swapRow(0, 1);
    cout << "matrix.swapRow(0, 1) : " << matrix << endl;
    return false;
}

bool testNPMatrixShift() {
    cout << endl<< "**** SHIFT ****" << endl << endl;
    NMatrix matrix = NMatrix::diag(vector<double>{1, 2, 1}, DIM_TEST);
    cout << "matrix : " << matrix << endl;
    matrix.shiftRow(1, 1);
    cout << "matrix shift row.shiftRow(1, 1) : " << matrix << endl;
    matrix.shiftCol(0, 1);
    cout << "matrix shift col.shiftCol(0, 1) : " << matrix << endl;

    return false;
}

bool testNPMatrixSubs() {
    cout << endl<< "**** SUBS ****" << endl << endl;
    NPMatrix matrix = NMatrix::diag(vector<double>{1, 2, 1}, DIM_TEST);

    cout << "matrix : " << matrix << endl;

    cout << endl<< "**** COL/ROW ****" << endl << endl;
    cout << "matrix.row(0) : " << matrix.row(0) << endl;
    cout << "matrix.col(0) : " << matrix.col(0) << endl;

    cout << endl<< "**** ROWS ****" << endl << endl;
    vector<ENVector> rows = matrix.rows();
    vector<ENVector> cols = matrix.cols();

    for (int i = 0; i < DIM_TEST; ++i) {
        cout << "rows["<< i << "] : " << rows[i] << endl;
    }

    cout << endl<< "**** COLS ****" << endl << endl;
    for (int j = 0; j < DIM_TEST; ++j) {
        cout << "cols["<< j << "] : " << cols[j] << endl;
    }

    cout << endl<< "**** SUB MATRIX ****" << endl << endl;
    cout << "matrix.subMatrix(0,0,1,1) : " << matrix.subMatrix(0,0,1,1) << endl;

    return false;
}

bool testNPMatrixFunctionOp() {
    cout << endl<< "**** FUNCTIONS OPERATORS ****" << endl << endl;

    NMatrix matrix = NMatrix::diag(vector<double>{1, 2, 1}, DIM_TEST);

    cout << "matrix : " << matrix << endl;
    cout << "matrix(0, 0)" << matrix(0, 0) << endl;
    cout << "matrix(1, 1)" << matrix(1, 1) << endl;
    cout << "matrix(2, 2)" << matrix(2, 2) << endl;
    return false;
}

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






