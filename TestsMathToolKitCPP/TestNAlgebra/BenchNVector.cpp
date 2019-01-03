//
// Created by Sami Dahoux on 08/10/2018.
//

#include <NVector.h>
#include "gtest/gtest.h"

#define NVECTOR_SMALL_DIM_TEST 1000000
#define NVECTOR_ITERATIONS_TEST 1000

using namespace std;

class NVectorBenchTest : public ::testing::Test {

protected:
    void SetUp() override {
        _u = vec_t::scalar(3, NVECTOR_SMALL_DIM_TEST);
        _v = vec_t::scalar(6, NVECTOR_SMALL_DIM_TEST);
        _s = 8;
        _elapsed_time = 0.0;
    }

    void iterateTest(const std::function<void(vec_t &, const vec_t &)> &test, std::string op = "") {
        for (int k = 0; k < NVECTOR_ITERATIONS_TEST; ++k) {
            _t0 = clock();
            test(_u, _v);
            _t1 = clock();
            _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / NVECTOR_ITERATIONS_TEST;
        }
        cout << op << " AVG ELAPSED TIME : " << _elapsed_time << "s" << endl;
    }

    void iterateTest(const std::function<void(vec_t &, double)> &test, std::string op = "") {
        for (int k = 0; k < NVECTOR_ITERATIONS_TEST; ++k) {
            _t0 = clock();
            test(_u, _s);
            _t1 = clock();
            _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / NVECTOR_ITERATIONS_TEST;
        }
        cout << op << " AVG ELAPSED TIME : " << _elapsed_time << "s" << endl;
    }

    clock_t _t0;
    clock_t _t1;
    double _elapsed_time;

    vec_t _u;
    vec_t _v;
    double _s;
};

TEST_F(NVectorBenchTest, Add) {
    iterateTest([](vec_t &u, const vec_t &v) { u += v; }, "+");
}

TEST_F(NVectorBenchTest, Sub) {
    iterateTest([](vec_t &u, const vec_t &v) { u -= v; }, "-");
}

TEST_F(NVectorBenchTest, Prod) {
    iterateTest([](vec_t &u, double s) { u /= s; }, "*");
}

TEST_F(NVectorBenchTest, Div) {
    iterateTest([](vec_t &u, double s) { u /= s; }, "/");
}

TEST_F(NVectorBenchTest, DotProduct) {
    iterateTest([](vec_t &u, const vec_t &v) { u | v; }, "|");
}