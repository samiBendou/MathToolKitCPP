//
// Created by Sami Dahoux on 08/10/2018.
//


#include <gtest/gtest.h>
#include <NMatrix.h>

#define SMALL_N_TEST 100
#define SMALL_EXP_TEST 5

using namespace std;

class NMatrixBenchTest : public ::testing::Test {

protected:
    void SetUp() override {
        _a = NMatrix::nscalar({-1, 2, -1}, SMALL_N_TEST);
    }

    clock_t _t0;
    clock_t _t1;
    double _elapsed_time;

    NMatrix _a;
};

TEST_F(NMatrixBenchTest, Pow) {
    _t0 = clock();
    _a ^= SMALL_EXP_TEST;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "^ ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NMatrixBenchTest, Inv) {
    _t0 = clock();
    _a ^= -1;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "inv() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NMatrixBenchTest, Det) {
    NVector<double> u = NVector<double>::scalar(2, SMALL_N_TEST);

    _t0 = clock();
    _a.det();
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "det() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NMatrixBenchTest, Solve) {
    NVector<double> u = NVector<double>::scalar(2, SMALL_N_TEST);

    _t0 = clock();
    _a % u;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "solve() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

