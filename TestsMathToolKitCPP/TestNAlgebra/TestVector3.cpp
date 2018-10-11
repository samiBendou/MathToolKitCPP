//
// Created by Sami Dahoux on 22/09/2018.
//

#include <Vector3.h>
#include "gtest/gtest.h"

class Vector3Test : public ::testing::Test {

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

    Vector3 _u;
    Vector3 _v;
    Vector3 _w;
};

TEST_F(Vector3Test, Getters) {
    ASSERT_EQ(_u.r(), 1);
    ASSERT_TRUE(_u.rXY() == "(1 0 0)");
    ASSERT_EQ(_u.theta(), 0);
    ASSERT_EQ(_u.phi(), M_PI_2);

    ASSERT_EQ(_v.r(), 1);
    ASSERT_TRUE(_v.rXY() == "(0 1 0)");
    ASSERT_EQ(_v.theta(), M_PI_2);
    ASSERT_EQ(_v.phi(), M_PI_2);

    ASSERT_EQ(_w.r(), 1);
    ASSERT_TRUE(_w.rXY() == 0);
    ASSERT_EQ(_w.theta(), 0);
    ASSERT_EQ(_w.phi(), 0);
}

TEST_F(Vector3Test, Setters) {
    _u.setR(2);
    ASSERT_TRUE(_u == "(2 0 0)");

    _u.setTheta(M_PI_2);
    ASSERT_TRUE(_u == "(0 2 0)");

    _u.setPhi(0);
    ASSERT_TRUE(_u == "(0 0 2)");
}

TEST_F(Vector3Test, VectorProduct) {
    ASSERT_EQ(_u ^ _v, _w);
    ASSERT_EQ(_v ^ _w, _u);
    ASSERT_EQ(_w ^ _u, _v);
}

TEST_F(Vector3Test, Angle) {
    ASSERT_EQ(_u % _v, M_PI_2);
    ASSERT_EQ(_v % _w, M_PI_2);
    ASSERT_EQ(_w % _u, M_PI_2);

    ASSERT_EQ(_u % _u, 0);
    ASSERT_EQ(_v % _v, 0);
    ASSERT_EQ(_w % _w, 0);
}