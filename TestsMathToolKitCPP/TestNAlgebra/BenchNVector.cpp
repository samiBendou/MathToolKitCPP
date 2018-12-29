//
// Created by Sami Dahoux on 08/10/2018.
//

#include <NVector.h>
#include "gtest/gtest.h"

#define SMALL_DIM_TEST 1000000
#define ITERATIONS 100

using namespace std;

class NVectorBenchTest : public ::testing::Test {

protected:
    void SetUp() override {
        _u = vec_t::scalar(3, SMALL_DIM_TEST);
        _v = vec_t::scalar(6, SMALL_DIM_TEST);
        _elapsed_time = 0.0;
    }

    clock_t _t0;
    clock_t _t1;
    double _elapsed_time;

    vec_t _u;
    vec_t _v;
};

TEST_F(NVectorBenchTest, Add) {

    for (int k = 0; k < ITERATIONS; ++k) {
        _t0 = clock();
        _u += _v;
        _t1 = clock();
        _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / ITERATIONS;
    }

    cout << endl << "+ AVG. ELAPSED TIME (sec) : " << _elapsed_time << endl;
}

TEST_F(NVectorBenchTest, Sub) {

    for (int k = 0; k < ITERATIONS; ++k) {
        _t0 = clock(); // or gettimeofday or whatever
        _u -= _v;
        _t1 = clock();
        _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / ITERATIONS;
    }

    cout << endl << "- AVG. ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NVectorBenchTest, Prod) {
    _t0 = clock();
    _u *= 5.0;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "* ELAPSED TIME (sec) : " << _elapsed_time << endl;

    _t0 = clock();
    _u /= 5.0;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "/ ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NVectorBenchTest, DotProduct) {
    _t0 = clock();
    _u | _v;
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "| ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}

TEST_F(NVectorBenchTest, Max) {
    _t0 = clock();
    _u.max();
    _t1 = clock();
    _elapsed_time = (_t1 - _t0) / (double) CLOCKS_PER_SEC;

    cout << endl << "max() ELAPSED TIME (sec) : " << _elapsed_time << endl << endl;
}