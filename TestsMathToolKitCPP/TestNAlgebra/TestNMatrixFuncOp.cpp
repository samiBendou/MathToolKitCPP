//
// Created by Sami Dahoux on 07/10/2018.
//

#include <NMatrix.h>
#include "gtest/gtest.h"


class NMatrixFuncOpTest : public ::testing::Test {

protected:
    void SetUp() override {

        _a = "  (1 0 0) \
                (0 1 0) \
                (0 0 1)";

        _b = "  ( 2 -1 0) \
                (-1 2 -1) \
                (0 -1  2)";

        _c = "  (0 0 0) \
                (1 2 1) \
                (5 10 2)";
    }

    NMatrix _a{3};
    NMatrix _b{3};
    NMatrix _c{3};
};

TEST_F(NMatrixFuncOpTest, MatrixProd) {
    NMatrix expect_b{_b};
    expect_b(1, 1, 2, 2) *= 2;

    EXPECT_EQ(_b(1, 1, 2, 2) * (2 * _a(1, 1, 2, 2)), expect_b(1, 1, 2, 2));

    _b(1, 1, 2, 2) *= (2 * _a(1, 1, 2, 2));
    ASSERT_EQ(_b, expect_b);
}

TEST_F(NMatrixFuncOpTest, Pow) {
    NMatrix b_pow_2{_b};
    b_pow_2(1, 1, 2, 2) = b_pow_2(1, 1, 2, 2) * b_pow_2(1, 1, 2, 2);

    EXPECT_EQ(_b(1, 1, 2, 2) ^ 2, b_pow_2(1, 1, 2, 2));

    _b(1, 1, 2, 2) ^= 2;
    ASSERT_EQ(_b, b_pow_2);
}

TEST_F(NMatrixFuncOpTest, Inv) {
    NMatrix expect_b_inv{_b};
    NMatrix expect_a{_a};

    NMatrix b0011_inv = _b(0, 0, 1, 1)^-1;

    expect_b_inv(0, 0) = 2.0/3.0;
    expect_b_inv(0, 1) = 1.0/3.0;
    expect_b_inv(1, 0) = 1.0/3.0;
    expect_b_inv(1, 1) = 2.0/3.0;

    expect_a(1, 0) = 2.7755575615628914e-17;
    expect_a(2, 0) = -5.5511151231257827e-17;
    expect_a(2, 1) = -1.1102230246251565e-16;
    expect_a(2, 2) = 0.99999999999999978;

    ASSERT_EQ(b0011_inv, expect_b_inv(0, 0, 1, 1));

    ASSERT_EQ(_b(0, 0, 1, 1) * b0011_inv, expect_a(0, 0, 1, 1));

    _b(0, 0, 1, 1) ^= -1;
    ASSERT_EQ(_b, expect_b_inv);
}

TEST_F(NMatrixFuncOpTest, Det) {
    ASSERT_EQ(_c(1, 1, 2, 2).det(), -6);
}

TEST_F(NMatrixFuncOpTest, Solve) {
    NVector u{"(1 2 5)"}, expect_sol{2}, expect_u{2};
    NMatrix copy_b0011{_b(0, 0, 1, 1)};

    expect_sol(0) = 1.3333333333333335;
    expect_sol(1) = 1.6666666666666667;

    expect_u(0) = 1.0000000000000002;
    expect_u(1) = 2;

    EXPECT_EQ(_b(0, 0, 1, 1) * (copy_b0011 % u(0, 1)), expect_u);
    ASSERT_EQ(_b(0, 0, 1, 1) % u(0, 1), expect_sol);
}

