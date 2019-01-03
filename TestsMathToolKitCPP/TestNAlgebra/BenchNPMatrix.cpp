//
// Created by Sami Dahoux on 08/10/2018.
//

#include <gtest/gtest.h>
#include <NPMatrix.h>

#define SMALL_N_TEST 1000
#define SMALL_EXP_TEST 5

using namespace std;

class NPMatrixBenchTest : public ::testing::Test {

protected:
    void SetUp() override {
        _a = mat_t::nscalar({-1, 2, -1}, SMALL_N_TEST);
        _b = 2 * mat_t::ones(SMALL_N_TEST);
    }

    clock_t _t0{};
    clock_t _t1{};
    double _elapsed_time{};

    mat_t _a;
    mat_t _b;
};

TEST_F(NPMatrixBenchTest, Add) {
    _t0 = clock();
    _a += _b;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "+ ELAPSED TIME (sec) : " << _elapsed_time << endl;

    _t0 = clock(); // or gettimeofday or whatever
    _a -= _b;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "- ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, Prod) {
    _t0 = clock();
    _a *= 5.0;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "* ELAPSED TIME (sec) : " << _elapsed_time << endl;

    _t0 = clock();
    _a /= 5.0;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "/ ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, DotProduct) {
    _t0 = clock();
    _a | _b;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "| ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, Max) {
    _t0 = clock();
    _a.max();
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "max() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, MatrixProd) {
    _t0 = clock();
    _a *= _b;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "* (MATRIX) ELAPSED TIME (sec) : " << _elapsed_time << endl;
}

TEST_F(NPMatrixBenchTest, VectorProd) {
    vec_t u = vec_t::scalar(2, SMALL_N_TEST);

    _t0 = clock();
    u *= _a;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "* (VECTOR) ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, Pow) {
    _t0 = clock();
    _a ^= SMALL_EXP_TEST;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "^ ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, Inv) {
    _t0 = clock();
    _a ^= -1;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "inv() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, Det) {
    vec_t u = vec_t::scalar(2, SMALL_N_TEST);

    _t0 = clock();
    _a.det();
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "det() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NPMatrixBenchTest, Solve) {
    vec_t u = vec_t::scalar(2, SMALL_N_TEST);

    _t0 = clock();
    _a % u;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "solve() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}