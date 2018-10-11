//
// Created by Sami Dahoux on 08/10/2018.
//

#include <gtest/gtest.h>
#include <NPMatrix.h>

#define SMALL_N_TEST 1000

using namespace std;

class NPMatrixBenchTest : public ::testing::Test {

protected:
    void SetUp() override {
        _a = NPMatrix<double>::ones(SMALL_N_TEST);
        _b = 2 * NPMatrix<double>::ones(SMALL_N_TEST);
    }

    clock_t _t0;
    clock_t _t1;
    double _elapsed_time;

    NPMatrix<double> _a;
    NPMatrix<double> _b;
};

TEST_F(NPMatrixBenchTest, Serialization) {
    _t0 = clock();
    _a.str();
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "SERIALIZATION ELAPSED TIME (sec) : " << _elapsed_time << endl;

    _t0 = clock(); // or gettimeofday or whatever
    _a = _b.str();
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "DESERIALIZATION ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, MatrixProd) {
    _t0 = clock();
    _a *_b;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "* (MATRIX) ELAPSED TIME (sec) : " << _elapsed_time << endl;
}

TEST_F(NPMatrixBenchTest, VectorProd) {
    NVector<double> u = NVector<double>::scalar(2, SMALL_N_TEST);

    _t0 = clock();
    _a * u;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "* (VECTOR) ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}