//
// Created by Sami Dahoux on 20/09/2018.
//

#include <NVector.h>
#include "gtest/gtest.h"


class NVectorTest : public ::testing::Test {

protected:
    void SetUp() override {
        _u = "(1 0 0)";
        _v = "(0 1 0)";
        _w = "(0 0 1)";
    }
    void TearDown() override {
        _u = "(1 0 0)";
        _v = "(0 1 0)";
        _w = "(0 0 1)";
    }

    NVector _u;
    NVector _v;
    NVector _w;
};

TEST_F(NVectorTest, Dim) {
    ASSERT_EQ(_u.dim(), 3);
}

TEST_F(NVectorTest, Construction) {
    _u = NVector(std::vector<double>{0, 1, 0});
    ASSERT_EQ(_u, _v);

    _u = NVector(_w);
    ASSERT_EQ(_u, _w);

    _u = NVector("(0 1 0)");
    ASSERT_EQ(_u, _v);

    _u = NVector(3);
    ASSERT_EQ(_u, NVector("(0 0 0)"));
}

TEST_F(NVectorTest, Affectation) {
    _u = _v;
    _v *= 5;
    ASSERT_EQ(_u, NVector("(0 1 0)"));
}

TEST_F(NVectorTest, Serialization) {
    std::vector<double> expect{1, 0, 0};

    ASSERT_EQ(_u, NVector("(1 0 0)"));
    ASSERT_NE(_u, NVector("(1, 0, 0)"));

    ASSERT_EQ(_u.str(), "(  1.00e+00  0.00e+00  0.00e+00  )");

    ASSERT_EQ(_u.array(), expect);
}

TEST_F(NVectorTest, Equality) {
    ASSERT_FALSE(_u == _v);
    ASSERT_FALSE(_u == _w);
    ASSERT_TRUE(_u == NVector("(1 0 0)"));
    ASSERT_FALSE(_u == 0);
    ASSERT_TRUE(NVector("(0 0 0)") == 0);

    ASSERT_TRUE(_u != _v);
    ASSERT_TRUE(_u != _w);
    ASSERT_FALSE(_u != NVector("(1 0 0)"));
    ASSERT_TRUE(_u != 0);
    ASSERT_FALSE(NVector("(0 0 0)") != 0);
}


TEST_F(NVectorTest, Add) {
    ASSERT_EQ(_u + _v, NVector("(1 1 0)"));

    _u += _w;
    ASSERT_EQ(_u, NVector("(1 0 1)"));

    ASSERT_EQ(_u - _w, NVector("(1 0 0)"));

    _u -= _w;
    ASSERT_EQ(_u, NVector("(1 0 0)"));

    ASSERT_EQ(-_u, NVector("(-1 0 0)"));
}

TEST_F(NVectorTest, Prod) {
    double x = 5;

    ASSERT_EQ(x * _u, NVector("(5 0 0)"));

    _u *= x;
    ASSERT_EQ(_u, NVector("(5 0 0)"));

    ASSERT_EQ(_u / x, NVector("(1 0 0)"));

    _u /= x;
    ASSERT_EQ(_u,  NVector("(1 0 0)"));
}

TEST_F(NVectorTest, EuclideanOperations) {
    ASSERT_EQ(_u * _v, 0);
    ASSERT_EQ(_u * _w, 0);
    ASSERT_EQ(_u * _u, 1);

    ASSERT_EQ(!_u, 1);
    ASSERT_EQ(_u/_v, pow(2, 0.5));
    ASSERT_EQ(_u/_u, 0);
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
}

TEST_F(NVectorTest, MaxMinAbsIndex) {
    ASSERT_EQ((-_u).maxAbsIndex(), 0);
    ASSERT_EQ((-_u).minAbsIndex(), 1);
}

TEST_F(NVectorTest, Swap) {
    _u.swap(0, 1);
    ASSERT_EQ(_u, _v);

    _u.swap(0, 1);
    ASSERT_EQ(_u, NVector("(1 0 0)"));

    _v.swap(1, 2);
    ASSERT_EQ(_v, _w);

    _v.swap(1, 2);
    ASSERT_EQ(_v, NVector("(0 1 0)"));
}

TEST_F(NVectorTest, Shift) {
    _u.shift(1);
    ASSERT_EQ(_u, _w);

    _u.shift(-1);
    ASSERT_EQ(_u, NVector("(1 0 0)"));

    _u.shift(-2);
    ASSERT_EQ(_u, _w);

    _u.shift(2);
    ASSERT_EQ(_u, NVector("(1 0 0)"));
}

TEST_F(NVectorTest, StaticGenerators) {
    ASSERT_EQ(NVector::zeros(3), NVector("(0 0 0)"));
    ASSERT_EQ(NVector::ones(3), NVector("(1 1 1)"));
    ASSERT_EQ(NVector::scalar(5, 3), NVector("(5 5 5)"));
    ASSERT_EQ(NVector::canonical(0, 3), NVector("(1 0 0)"));
}


