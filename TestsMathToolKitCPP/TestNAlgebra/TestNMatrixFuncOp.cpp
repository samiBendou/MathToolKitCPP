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
    NMatrix expect_b0011_inv{"  (2 1) \
                                (1 2)"};
    NMatrix expect_b_inv{_b};
    NMatrix expect_a{_a};

    NMatrix b0011_inv = _b(0, 0, 1, 1)^-1;

    expect_b0011_inv /= 3;

    expect_b_inv(0, 0, 1, 1) = expect_b0011_inv;

    ASSERT_EQ(b0011_inv, expect_b0011_inv);

    ASSERT_DOUBLE_EQ((_b(0, 0, 1, 1) * b0011_inv) / _a(0, 0, 1, 1), 0);

    _b(0, 0, 1, 1) ^= -1;
    ASSERT_EQ(_b, expect_b_inv);
}

TEST_F(NMatrixFuncOpTest, Det) {
    ASSERT_EQ(_c(1, 1, 2, 2).det(), -6);
}

TEST_F(NMatrixFuncOpTest, Solve) {
    NVector u{"(1 2 5)"}, sol{"(4 5)"};
    NMatrix copy_b0011{_b(0, 0, 1, 1)};

    sol /= 3;

    EXPECT_NEAR(_b(0, 0, 1, 1) * (copy_b0011 % u(0, 1)) / u(0, 1), 0, 2.2204460492503131e-16);
    ASSERT_NEAR(_b(0, 0, 1, 1) % u(0, 1) / sol, 0, 2.2204460492503131e-16);
}

