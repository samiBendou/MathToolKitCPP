//
// Created by Sami Dahoux on 20/09/2018.
//

#include <NVector.h>
#include "gtest/gtest.h"


class NVectorTest : public ::testing::Test {

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

TEST_F(NVectorTest, Dim) {
    ASSERT_EQ(_u.dim(), 3);
}

TEST_F(NVectorTest, Equality) {
    ASSERT_TRUE(_u == _u);
    ASSERT_FALSE(_u == _v);
    ASSERT_FALSE(_u == _w);
    ASSERT_FALSE(_u == 0);

    ASSERT_FALSE(_u != _u);
    ASSERT_TRUE(_u != _v);
    ASSERT_TRUE(_u != _w);
    ASSERT_TRUE(_u != 0);
}


TEST_F(NVectorTest, Construction) {
    _u = vec_t{0, 0, 1};
    ASSERT_EQ(_u, _w);

    _u = vec_t(std::vector<double>{0, 1, 0});
    ASSERT_EQ(_u, _v);

    _u = vec_t(_w);
    ASSERT_EQ(_u, _w);

    _u = vec_t(3);
    ASSERT_EQ(_u.dim(), 3);
}

TEST_F(NVectorTest, Affectation) {
    vec_t expect_u{0, 1, 0};

    _u = _v;
    _v *= 5;
    ASSERT_EQ(_u, expect_u);
    ASSERT_EQ(_v, vec_t({0, 5, 0}));
    ASSERT_EQ(_u, expect_u);

    _u = {0, 0, 1};
    ASSERT_EQ(_u, _w);

    _u = std::vector<double>{0, 1, 0};
    ASSERT_EQ(_u, expect_u);
}

TEST_F(NVectorTest, Serialization) {
    ASSERT_EQ(_u.array(), std::vector<double>({1, 0, 0}));
}

TEST_F(NVectorTest, Add) {
    vec_t copy_u{{1, 0, 0}};

    ASSERT_EQ(_u + _v, vec_t({1, 1, 0}));

    _u += _w;
    ASSERT_EQ(_u, vec_t({1, 0, 1}));

    ASSERT_EQ(_u - _w, copy_u);

    _u -= _w;
    ASSERT_EQ(_u, copy_u);

    ASSERT_EQ(-_u, vec_t({-1, 0, 0}));
}

TEST_F(NVectorTest, Prod) {
    double x = 5;

    vec_t copy_u{{1, 0, 0}}, expect_u{{5, 0, 0}};


    ASSERT_EQ(x * _u, expect_u);

    _u *= x;
    ASSERT_EQ(_u, expect_u);

    ASSERT_EQ(_u / x, copy_u);

    _u /= x;
    ASSERT_EQ(_u, copy_u);
}

TEST_F(NVectorTest, EuclideanOperations) {
    ASSERT_EQ(_u | _v, 0);
    ASSERT_EQ(_u | _w, 0);
    ASSERT_EQ(_u | _u, 1);

    ASSERT_EQ(!_u, 1);

    ASSERT_EQ(_u / _v, pow(2, 0.5));
    ASSERT_EQ(_u / _u, 0);
}

TEST_F(NVectorTest, MaxMin) {
    ASSERT_EQ(_u.max(), 1);
    ASSERT_EQ(_u.min(), 0);

    ASSERT_EQ(_v.max(), 1);
    ASSERT_EQ(_v.min(), 0);

    ASSERT_EQ(_w.max(), 1);
    ASSERT_EQ(_w.min(), 0);
}

TEST_F(NVectorTest, MaxMinIndex) {
    ASSERT_EQ(_u.maxIndex(), 0);
    ASSERT_EQ(_u.minIndex(), 1);

    ASSERT_EQ(_v.maxIndex(), 1);
    ASSERT_EQ(_v.minIndex(), 0);

    ASSERT_EQ(_w.maxIndex(), 2);
    ASSERT_EQ(_w.minIndex(), 0);
}

TEST_F(NVectorTest, MaxMinAbs) {
    ASSERT_EQ((-_u).maxAbs(), 1);
    ASSERT_EQ((-_u).minAbs(), 0);

    ASSERT_EQ((-_v).maxAbs(), 1);
    ASSERT_EQ((-_v).minAbs(), 0);

    ASSERT_EQ((-_w).maxAbs(), 1);
    ASSERT_EQ((-_w).minAbs(), 0);
}

TEST_F(NVectorTest, MaxMinAbsIndex) {
    ASSERT_EQ((-_u).maxAbsIndex(), 0);
    ASSERT_EQ((-_u).minAbsIndex(), 1);

    ASSERT_EQ((-_v).maxAbsIndex(), 1);
    ASSERT_EQ((-_v).minAbsIndex(), 0);

    ASSERT_EQ((-_w).maxAbsIndex(), 2);
    ASSERT_EQ((-_w).minAbsIndex(), 0);
}

TEST_F(NVectorTest, Swap) {
    vec_t copy_u{{1, 0, 0}}, copy_v{{0, 1, 0}};

    _u.swap(0, 1);
    ASSERT_EQ(_u, _v);

    _u.swap(0, 1);
    ASSERT_EQ(_u, copy_u);

    _v.swap(1, 2);
    ASSERT_EQ(_v, _w);

    _v.swap(1, 2);
    ASSERT_EQ(_v, copy_v);
}

TEST_F(NVectorTest, Shift) {
    vec_t copy_u{{1, 0, 0}};

    _u.shift(1);
    ASSERT_EQ(_u, _w);

    _u.shift(-1);
    ASSERT_EQ(_u, copy_u);

    _u.shift(-2);
    ASSERT_EQ(_u, _w);

    _u.shift(2);
    ASSERT_EQ(_u, copy_u);
}

TEST_F(NVectorTest, Fill) {
    _u.fill(9);
    ASSERT_EQ(_u, vec_t({9, 9, 9}));
}

TEST_F(NVectorTest, StaticGenerators) {
    ASSERT_EQ(vec_t::zeros(3), vec_t({0, 0, 0}));
    ASSERT_EQ(vec_t::ones(3), vec_t({1, 1, 1}));
    ASSERT_EQ(vec_t::scalar(5, 3), vec_t({5, 5, 5}));
    ASSERT_EQ(vec_t::canonical(0, 3), vec_t({1, 0, 0}));
}

TEST_F(NVectorTest, StaticFunctions) {
    ASSERT_EQ(vec_t::sum({_u, _v, _w}), vec_t({1, 1, 1}));
    ASSERT_EQ(vec_t::sumProd({1, 2, 3}, {_u, _v, _w}), vec_t({1, 2, 3}));
}


