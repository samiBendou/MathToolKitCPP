//
// Created by Sami Dahoux on 07/05/2018.
//

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


using namespace std;
int mainBis() {
/*
    cout << endl<< "**** MathToolKit TEST PROGRAM ****" << endl << endl;

    cout << endl<< "**** VECTORS ****" << endl << endl;





    cout << "Vector1 : " << vector1 << endl;
    cout << "Vector2 : " << vector2 << endl;

    cout << endl<< "**** COMPOUND OPERATIONS ****" << endl << endl;

    vector1 += 2 * vector2;
    cout << "v1 += 2 * v2 : " << vector1 << endl;

    vector1 *= 2;
    cout << "v1 *= 2 : " << vector1 << endl;

    cout << endl<< "**** MAX/MIN ****" << endl << endl;

    NVector vector3 = NVector::canonical(0, 3);
    cout << "Vector3 : " << vector3 << endl;

    cout << "Max of Vector3 : " << vector3.max() << " index : " << vector3.maxIndex() << endl;
    cout << "Min of Vector3 : " << vector3.min() << " index : " << vector3.minIndex() << endl;

    cout << "MaxAbs of Vector3 : " << vector3.maxAbs() << " index : " << vector3.maxAbsIndex() << endl;
    cout << "MinAbs of Vector3 : " << vector3.minAbs() << " index : " << vector3.minAbsIndex() << endl;

    cout << endl<< "**** SWAP ****" << endl << endl;
    vector3.swap(0, 1);
    cout << "Vector 3 swap(0, 1) : " << vector3 << endl;

    cout << endl<< "**** SHIFT ****" << endl << endl;
    vector3.shift(-2);
    cout << "Vector 3 shift(-2) : " << vector3 << endl;

    cout << endl<< "**** SUB-VECTORS ****" << endl << endl;
    NVector vector4 = vector3(0, 1);
    cout << "Vector 4 : " << vector4 << endl;

    vector4(0, 3) = vector1(0, 1);
    cout << "Vector 4 : " << vector4 << endl;

    cout << endl<< "**** ARRAY-SUBSCRIPT OPERATOR ****" << endl << endl;
    cout << "vector4(0) : " << vector4(0) << endl;

    cout << endl<< "**** EUCLIDEAN VECTORS ****" << endl << endl;

    ENVector eVector1 = vector1;
    cout << "eVector 1 : " << eVector1 << endl;
    cout << "eV1 * v3 : " << eVector1 * vector3 << endl;
    eVector1 += vector3 / 10;
    cout << "eVector 1 : " << eVector1 << endl;
    cout << "norm : " << !eVector1 << endl;

    cout << endl << "*** AFFECTATION/COPY ***" << endl << endl;

    ENVector aVector1 = 2 * NVector::canonical(0, 3) + 3 * NVector::canonical(1, 3);
    ENVector aVector2 = 1 * NVector::canonical(2, 3);
    ENVector aVector3 = 6 * NVector::canonical(2, 3);

    cout << "aVector 1 : " << aVector1 << endl;
    cout << "aVector 2 : " << aVector2 << endl;
    cout << "aVector 3 : " << aVector3 << endl << endl;

    aVector2 = aVector1;
    aVector3 = ENVector(aVector2);
    aVector1 *= 2;
    cout << "aVector 1 : " << aVector1 << endl;
    cout << "aVector 2 : " << aVector2 << endl;
    cout << "aVector 3 : " << aVector3 << endl;
    cout << "a1 = a2 : " << ((aVector1 == aVector2) ? "true" : "false") << endl;
    cout << "a2 = a3 : " << ((aVector2 == aVector3) ? "true" : "false") << endl;

    cout << endl << "*** 3D VECTORS ***" << endl << endl;

    cout << endl << "*** CANONICAL BASE ***" << endl << endl;
    auto* b = new Vector3[3];

    for (int k = 0; k < 3; ++k) {
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

    cout << endl << "*** NPMatrix ***" << endl << endl;

    NPMatrix matrix1 = NPMatrix::zeros(3);
    NPMatrix matrix2 = NPMatrix::ones(3);

    cout << "Matrix1 : " << matrix1 << endl;
    cout << "Matrix2 : " << matrix2 << endl;


    cout << endl<< "**** ALGEBRAICAL OPERATIONS ****" << endl << endl;

    cout << "Sum : " << (matrix1 + matrix2) << endl;
    cout << "Subtraction : " << (matrix1 - matrix2) << endl;
    cout << "Multiply by 10 : " << (matrix2 * 10) << endl;
    cout << "Divide by 10 : " << (matrix2 / 10) << endl;

    cout << "Matrix1 : " << matrix1 << endl;
    cout << "Matrix2 : " << matrix2 << endl;

    cout << endl<< "**** COMPOUND OPERATIONS ****" << endl << endl;

    matrix1 += 2 * matrix2;
    cout << "v1 += 2 * v2 : " << matrix1 << endl;

    matrix1 *= 2.0;
    cout << "v1 *= 2 : " << matrix1 << endl;

    cout << endl<< "**** MATRIX OPERATIONS ****" << endl << endl;

    vector<double> dataDiag3{1, 2, 1};
    NMatrix matrix3 = NMatrix::diag(dataDiag3, 3);

    cout << "Matrix3 : " << matrix3 << endl;
    cout << "!Matrix3 : " << (!matrix3) << endl;

    cout << endl<< "**** COL/ROW ****" << endl << endl;
    cout << "MatrixRow0 : " << matrix3.row(0) << endl;
    cout << "MatrixCol0 : " << matrix3.col(0) << endl;

    cout << endl<< "**** ROWS ****" << endl << endl;
    vector<ENVector> rows3 = matrix3.rows();
    vector<ENVector> cols3 = matrix3.cols();

    for (int i = 0; i < 3; ++i) {
        cout << "MatrixRow"<< i << " : " << rows3[i] << endl;
    }

    cout << endl<< "**** COLS ****" << endl << endl;

    for (int j = 0; j < 3; ++j) {
        cout << "MatrixCol"<< j << " : " << cols3[j] << endl;
    }

    cout << endl<< "**** SUB MATRIX ****" << endl << endl;
    NMatrix sMatrix1 = matrix3.subMatrix(0,0,2,2);
    cout << "sMatrix1 : " << sMatrix1 << endl;

    cout << endl<< "**** MATRIX PRODUCT ****" << endl << endl;
    vector<double> dataDiag4{1, 5, 1};
    NMatrix matrix4 = NMatrix::diag(dataDiag4, 3);

    ENVector vector5 = NVector::ones(3);

    cout << "Matrix4 : " << matrix4 << endl;
    cout << "Vector5 : " << vector5 << endl;

    cout << "m4 * v5 : " << (matrix4 * vector5) << endl;
    cout << "m4 * m4 : " << (matrix4 * matrix4) << endl;

    cout << "v3 * !v3 : " << (NPMatrix{vector3} * !NPMatrix(vector3)) << endl;
    cout << "!v3 * v3 : " << (!NPMatrix{vector3} * NPMatrix(vector3)) << endl;

    NMatrix matrix5 = NPMatrix::canonical(0, 0, 2) + 2 * NPMatrix::canonical(1, 0, 2);

    matrix4.setSubMatrix(matrix5, 1, 1);
    cout << "Matrix4 : " << matrix4 << endl;

    cout << endl<< "**** SWAP ****" << endl << endl;
    matrix4.swap(1,1,2,2);
    cout << "Matrix4 : " << matrix4 << endl;
    matrix4.swapCol(0, 1);
    cout << "Matrix4 : " << matrix4 << endl;
    matrix4.swapRow(0, 1);
    cout << "Matrix4 : " << matrix4 << endl;

    cout << endl<< "**** SHIFT ****" << endl << endl;
    cout << "Matrix4 : " << matrix4 << endl;
    matrix4.shiftRow(1, 1);
    cout << "Matrix4 shift row : " << matrix4 << endl;
    matrix4.shiftCol(0, 1);
    cout << "Matrix4 shift col : " << matrix4 << endl;


    cout << endl << "**** MAX INDEX ROW ****" << endl;
    cout << "Matrix4.maxAbsIndexRow(0, 0) : " << matrix4.maxAbsIndexRow(0) << endl;
    cout << "Matrix4.maxAbsIndexRow(1, 0) : " << matrix4.maxAbsIndexRow(1) << endl;
    cout << "Matrix4.maxAbsIndexRow(2, 0) : " << matrix4.maxAbsIndexRow(2) << endl;

    cout << endl << "**** MAX INDEX COL ****" << endl;
    cout << "Matrix4.maxAbsIndexCol(0, 0) : " << matrix4.maxAbsIndexCol(0) << endl;
    cout << "Matrix4.maxAbsIndexCol(1, 0) : " << matrix4.maxAbsIndexCol(1) << endl;
    cout << "Matrix4.maxAbsIndexCol(2, 0) : " << matrix4.maxAbsIndexCol(2) << endl;


    cout << endl << "**** POW ****" << endl;
    NMatrix matrix6 = NMatrix::diag(dataDiag3, 3);

    const NMatrix eye3 = NMatrix::eye(3);

    cout << "Matrix6 : " << matrix6 << endl;
    matrix6 ^= 2;
    cout << "Square of Matrix6 : " << matrix6 << endl;
    cout << "Det Matrix6 : " << matrix6.det() << endl;
    matrix6 ^= -1;
    cout << "Inverse of Matrix6 : " << matrix6 << endl;
    cout << "Det Matrix6 : " << matrix6.det() << endl;

    cout << endl << "**** LUP ****" << endl;
    vector<double> matrix7Data{-1, 2};
    NMatrix matrix7 = NMatrix::nScalar(matrix7Data, 3);

    NMatrix lupL7 = matrix7.lupL();
    NMatrix lupU7 = matrix7.lupU();

    cout << "Matrix7 : " << matrix7 << endl;

    cout << "Matrix7.luL() : " << lupL7 << endl;
    cout << "Matrix7.luU() : " << lupU7 << endl;
    cout << "LU = " << (lupL7 * lupU7) << endl;

    cout << endl << "**** INV ****" << endl;
    NMatrix matrix7Inv = NMatrix(matrix7);
    matrix7Inv ^= -1;
    cout << "Matrix7.inv() : " << matrix7Inv << endl;
    cout << "Matrix7-1 * Matrix7 : " << (matrix7Inv * matrix7) << endl;

    cout << "Matrix7 : " << matrix7 << endl;
    cout << "Matrix7-1 : " << matrix7Inv << endl;

    cout << endl << "**** DET ****" << endl;

    double det7 = matrix7.det();
    double det7Inv = matrix7Inv.det();

    cout << "Det Matrix7 : " << det7 << endl;
    cout << "Det Matrix7Inv : " << det7Inv << endl;
    cout << "Matrix7-1.det * Matrix7.det : " << det7 * det7Inv << endl;

    cout << "Matrix7 : " << matrix7 << endl;
    cout << "Matrix7-1 : " << matrix7Inv << endl;

    cout << endl << "**** SOLVE ****" << endl;
    ENVector bVector = ENVector::ones(3);
    cout << "b : " << bVector << endl;
    cout << "Matrix7 * X = b : X = " << (matrix7 % bVector) << endl;
    cout << "Matrix7 * X = " << (matrix7 * (matrix7 % bVector)) << endl;

    cout << "Matrix7 : " << matrix7 << endl;
    cout << "Matrix7-1 : " << matrix7Inv << endl;

    cout << endl << "*****************************************" << endl;

    cout << endl << "**** NSegment TESTS ****" << endl;

    ENVector a1 = NVector::zeros(3);
    ENVector b1 = NVector::scalar(10.0, 3);
    const double h = 1;
    NSegment seg1{-b1, b1};
    vector< ENVector > mesh = seg1.mesh(h);
    cout << "a, b : " << seg1.str() << endl;
    for(int k = 0; k < mesh.size(); k++) {
        cout << "mesh[" << k << "] : " << mesh[k] << endl;
    }
    cout << "a1 is in seg1 : " << seg1.isIn(a1) << endl;
    cout << "-1 * b1 is in seg1 : " << seg1.isIn(-1 * b1) << endl;
    cout << endl << "**** NParallelepiped TESTS ****" << endl;
    NMatrix base = NMatrix::scalar(5, 2);
    vector<ENVector> baseCols = base.cols();
    ENVector pos = NVector::zeros(2);
    ENVector dx = NVector::scalar(h / 3, 2);
    NParallelepiped para{base, pos};

    cout << para << endl;


    vector< ENVector > paraMesh = para.mesh(dx);
    for(int k = 0; k < paraMesh.size(); k++) {
        cout << "paraMesh[" << k << "] : " << paraMesh[k] << endl;
    }

    cout << "pos is in para : " << para.isIn(pos + 0.9 * baseCols[0]) << endl;

    cout << endl << "**** NDSet TESTS ****" << endl;

    NDSet set1 = NDSet(baseCols);
    cout << "set1 : " << set1 << endl;
    vector< ENVector > set1Mesh = set1.mesh();
    for(int k = 0; k < set1.card(); k++) {
        cout << "set1Mesh[" << k << "] : " << set1Mesh[k] << endl;
    }

    cout << endl<< "**** FUNCTIONS ****" << endl << endl;
    NConstantField gField{Vector3(0, 0, 9.81)};
    std::vector<ENVector> solution = NOde::euler(ENVector::zeros(6), gField);
    for (int k = 0; k <solution.size(); ++k) {
        cout << "solution " << k << " : " << solution[k] << endl;
    }
    NPMatrix matSol{solution};
    cout << matSol << endl;

    cout << endl<< "**** NEWTONIAN FIELD ****" << endl << endl;
    std::vector<double> mass{1.9891e+30, 5.9736e+24};
    std::vector<Vector3> r{Vector3(0, 0, 0), Vector3(0, 0, 1.47098074e+11)};
    ENVector u0 = ENVector::zeros(6);
    u0(0) = 1.47098074e+11;
    u0(4) = 3.0287e+4;
    SNewtonianField gNewtonian{-6.67408e-11, &mass, &r};
    std::vector<ENVector> solutionNewtonian = NOde::euler(u0, gNewtonian);
    for (int k = 0; k <solutionNewtonian.size(); ++k) {
        cout << "solution " << k << " : " << solutionNewtonian[k] << endl;
    }
    */
    return 0;

}