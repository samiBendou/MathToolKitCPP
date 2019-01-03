//
// Created by Sami Dahoux on 08/10/2018.
//

#include <gtest/gtest.h>
#include <NPMatrix.h>

#define NPMATRIX_SMALL_DIM_TEST 1000
#define NPMATRIX_ITERATIONS_TEST 100
#define NPMATRIX_SMALL_EXP_TEST 5

using namespace std;

class NPMatrixBenchTest : public ::testing::Test {

protected:
    void SetUp() override {
        _u = vec_t::scalar(3, NPMATRIX_SMALL_DIM_TEST);
        _a = mat_t::nscalar({-1, 2, -1}, NPMATRIX_SMALL_DIM_TEST);
        _b = 2 * mat_t::ones(NPMATRIX_SMALL_DIM_TEST);
        _s = 8;
    }

    void iterateTest(const std::function<void(mat_t &, const mat_t &)> &test, std::string op = "") {
        for (int k = 0; k < NPMATRIX_ITERATIONS_TEST; ++k) {
            _t0 = clock();
            test(_a, _b);
            _t1 = clock();
            _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / NPMATRIX_ITERATIONS_TEST;
        }
        cout << op << " AVG ELAPSED TIME : " << _elapsed_time << "s" << endl;
    }

    void iterateTest(const std::function<void(mat_t &, double)> &test, std::string op = "") {
        for (int k = 0; k < NPMATRIX_ITERATIONS_TEST; ++k) {
            _t0 = clock();
            test(_a, _s);
            _t1 = clock();
            _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / NPMATRIX_ITERATIONS_TEST;
        }
        cout << op << " AVG ELAPSED TIME : " << _elapsed_time << "s" << endl;
    }

    void iterateTest(const std::function<void(vec_t &, const mat_t &)> &test, std::string op = "") {
        for (int k = 0; k < NPMATRIX_ITERATIONS_TEST; ++k) {
            _t0 = clock();
            test(_u, _a);
            _t1 = clock();
            _elapsed_time += ((_t1 - _t0) / (double) CLOCKS_PER_SEC) / NPMATRIX_ITERATIONS_TEST;
        }
        cout << op << " AVG ELAPSED TIME : " << _elapsed_time << "s" << endl;
    }

    clock_t _t0{};
    clock_t _t1{};
    double _elapsed_time{};

    mat_t _a;
    mat_t _b;
    vec_t _u;
    double _s;
};

TEST_F(NPMatrixBenchTest, Add) {
    iterateTest([](mat_t &a, const mat_t &b) { a += b; }, "+");
}

TEST_F(NPMatrixBenchTest, Prod) {
    iterateTest([](mat_t &a, double s) { a *= s; }, "* (SCALAR)");
}

TEST_F(NPMatrixBenchTest, VectorProd) {
    iterateTest([](vec_t &u, const mat_t &a) { u *= a; }, "* (VECTOR)");
}

TEST_F(NPMatrixBenchTest, MatrixProd) {
    iterateTest([](mat_t &a, const mat_t &b) { a *= b; }, "* (MATRIX)");
}

TEST_F(NPMatrixBenchTest, DotProduct) {
    iterateTest([](mat_t &a, const mat_t &b) { a | b; }, "|");
}

TEST_F(NPMatrixBenchTest, Pow) {
    iterateTest([](mat_t &a, double s) { a ^= NPMATRIX_SMALL_EXP_TEST; }, "*");
}

TEST_F(NPMatrixBenchTest, Inv) {
    iterateTest([](mat_t &a, double s) { a ^= -1; }, "INVERSION");
}

TEST_F(NPMatrixBenchTest, Det) {
    iterateTest([](mat_t &a, double s) { a.det(); }, "DETERMINANT");
}

TEST_F(NPMatrixBenchTest, Solve) {
    iterateTest([](vec_t &u, const mat_t &a) { u %= a; }, "% (SOLVE)");
}