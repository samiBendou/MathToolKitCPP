//
// Created by Sami Dahoux on 22/09/2018.
//

#include <NVector.h>
#include "gtest/gtest.h"

class NVectorFuncOpTest : public ::testing::Test {

protected:
    void SetUp() override {
        _u = {1, 0, 0};
        _v = {0, 1, 0};
        _w = {0, 0, 1};
    }

    vec_t _u;
    vec_t _v;
    vec_t _w;
};


TEST_F(NVectorFuncOpTest, Dim) {
    ASSERT_EQ(_u(0, 1).dim(), 2);
    ASSERT_EQ(_u.dim(), 3);
}

TEST_F(NVectorFuncOpTest, Equality) {
    ASSERT_TRUE(_u(0, 1) == _v(1, 2));
    ASSERT_EQ(_u.dim(), 3);
    ASSERT_TRUE(_u(0, 1) == vec_t({1, 0}));
    ASSERT_EQ(_u.dim(), 3);

    ASSERT_FALSE(_u(0, 1) != _v(1, 2));

    ASSERT_FALSE(_u(0, 1) != vec_t({1, 0}));
}

TEST_F(NVectorFuncOpTest, Serialization) {
    ASSERT_EQ(_u(0, 1).array(), std::vector<double>({1, 0}));
    ASSERT_EQ(_u.dim(), 3);
}

TEST_F(NVectorFuncOpTest, AffectationAccess) {
    ASSERT_EQ(_u(0), 1);
    ASSERT_EQ(_u(1), 0);
    ASSERT_EQ(_u(2), 0);

    _u(0) = 0;
    ASSERT_EQ(_u(0), 0);

    _u(0) = 1;

    ASSERT_EQ(_u(0, 1), vec_t({1, 0}));
    ASSERT_EQ(_u(1, 2), vec_t({0, 0}));

    _v = _u(0, 1);
    ASSERT_EQ(_v, vec_t({1, 0}));

    _v(0, 1) = _w(1, 2);
    ASSERT_EQ(_v, vec_t({0, 1}));

    _u(0, 1) = _v;
    ASSERT_EQ(_u, vec_t({0, 1, 0}));
}


TEST_F(NVectorFuncOpTest, Add) {
    _u(0, 1) = _u(0, 1) + _v(0, 1);
    ASSERT_EQ(_u, vec_t({1, 1, 0}));

    _u(0, 1) += _v(0, 1);
    ASSERT_EQ(_u, vec_t({1, 2, 0}));

    _u(0, 1) = _u(0, 1) + _w(1, 2);
    ASSERT_EQ(_u, vec_t({1, 3, 0}));

    _u(0, 1) += _w(1, 2);
    ASSERT_EQ(_u, vec_t({1, 4, 0}));
}

TEST_F(NVectorFuncOpTest, Sub) {
    _u(0, 1) = _u(0, 1) - _v(0, 1);
    ASSERT_EQ(_u, vec_t({1, -1, 0}));

    _u(0, 1) -= _v(0, 1);
    ASSERT_EQ(_u, vec_t({1, -2, 0}));

    _u(0, 1) = _u(0, 1) - _w(1, 2);
    ASSERT_EQ(_u, vec_t({1, -3, 0}));

    _u(0, 1) -= _w(1, 2);
    ASSERT_EQ(_u, vec_t({1, -4, 0}));

    _u += _w;
    _u(0, 1) = -_v(0, 1);
    ASSERT_EQ(_u, vec_t({0, -1, 1}));
}

TEST_F(NVectorFuncOpTest, Prod) {
    double x = 5;

    _v(0, 1) = _u(0, 1) * x;
    ASSERT_EQ(_v, vec_t({5, 0, 0}));

    _v(0, 1) *= x;
    ASSERT_EQ(_v, vec_t({25, 0, 0}));

    _v(0, 1) = _v(0, 1) / x;
    ASSERT_EQ(_v, vec_t({5, 0, 0}));

    _v(0, 1) /= x;
    ASSERT_EQ(_v, vec_t({1, 0, 0}));
}

TEST_F(NVectorFuncOpTest, EuclideanOperations) {
    ASSERT_EQ(_u(0, 1) | _v(0, 1), 0);
    ASSERT_EQ(_u(0, 1) | _v(1, 2), 1);

    ASSERT_EQ(!_u(1, 2), 0);
    ASSERT_EQ(!_u(0, 1), 1);

    ASSERT_EQ(_u(0, 1) / _v(0, 1), pow(2, 0.5));
    ASSERT_EQ(_u(0, 1) / _v(1, 2), 0);
}

TEST_F(NVectorFuncOpTest, MaxMin) {
    ASSERT_EQ(_u(0, 1).max(), 1);
    ASSERT_EQ(_u(0, 1).min(), 0);

    ASSERT_EQ(_u(1, 2).max(), 0);
    ASSERT_EQ(_u(1, 2).min(), 0);
}

TEST_F(NVectorFuncOpTest, MaxMinIndex) {
    ASSERT_EQ(_u(0, 1).maxIndex(), 0);
    ASSERT_EQ(_u(0, 1).minIndex(), 1);

    ASSERT_EQ(_v(1, 2).maxIndex(), 0);
    ASSERT_EQ(_v(1, 2).minIndex(), 1);
}

TEST_F(NVectorFuncOpTest, Shift) {
    _u(0, 1).shift(1);

    ASSERT_EQ(_u, _v);

    _u(1, 2).shift(1);
    ASSERT_EQ(_u, _w);
}