    //
// Created by Sami Dahoux on 27/09/2018.
//

#include <NPMatrix.h>
#include "gtest/gtest.h"


class NPMatrixFuncOpTest : public ::testing::Test {

protected:
    void SetUp() override {

        _a = {{1, 0, 0},
              {0, 1, 0},
              {0, 0, 1}};

        _b = {{2,  -1, 0},
              {-1, 2,  -1},
              {0,  -1, 2}};

        _c = {{0, 0,  0},
              {1, 2,  1},
              {5, 10, 2}};
    }

    mat_t _a;
    mat_t _b;
    mat_t _c;
};


TEST_F(NPMatrixFuncOpTest, Dim) {

}

TEST_F(NPMatrixFuncOpTest, Equality) {

    mat_t expect_b1122{{2,  -1},
                       {-1, 2}};

    mat_t copy_b{_b};

    ASSERT_TRUE(_b(1, 1, 2, 2) == expect_b1122);
    ASSERT_TRUE(_b(1, 1, 2, 2) == copy_b(1, 1, 2, 2));
    ASSERT_TRUE(_b == copy_b(0, 0, 2, 2));
}

TEST_F(NPMatrixFuncOpTest, AffectationAccess) {

    mat_t expect_b0011{{3,  -1},
                       {-1, 2}};

    mat_t new_b0011{{6,  -1},
                    {-1, 2}};

    mat_t expect_a0011{{1, 0},
                       {0, 1}};

    mat_t expect_b1122{{1,  1},
                       {-1, 2}};

    ASSERT_EQ(_b(0, 0), 2);
    ASSERT_EQ(_b(0, 1), -1);
    ASSERT_EQ(_b(1, 0), -1);

    _b(0, 0) = 3;
    ASSERT_EQ(_b(0, 0), 3);

    ASSERT_EQ(_b(0, 0, 1, 1), expect_b0011);

    ASSERT_EQ(_b.n(), 3);
    ASSERT_EQ(_b.p(), 3);

    _b(0, 0, 1, 1) = new_b0011;

    ASSERT_EQ(_b.n(), 3);
    ASSERT_EQ(_b.p(), 3);

    ASSERT_EQ(_b(0, 0, 1, 1), new_b0011);

    _b(0, 0, 1, 1) = _a(0, 0, 1, 1);

    ASSERT_EQ(_b.n(), 3);
    ASSERT_EQ(_b.p(), 3);

    ASSERT_EQ(_b(0, 0, 1, 1), expect_a0011);

    _c = _b(0, 0, 2, 2);
    ASSERT_EQ(_c, _b);
}

TEST_F(NPMatrixFuncOpTest, Add) {
    mat_t expect_a1122{{3,  -1},
                       {-1, 3}};

    mat_t expect_a{{3,  -1, 0},
                   {-1, 3,  0},
                   {0,  0,  1}};

    EXPECT_EQ(_a(1, 1, 2, 2) + _b(0, 0, 1, 1), expect_a1122);

    _a(0, 0, 1, 1) += _b(0, 0, 1, 1);
    ASSERT_EQ(_a, expect_a);
}

TEST_F(NPMatrixFuncOpTest, Sub) {
    mat_t expect_a1122{{-1, 1},
                       {1,  -1}};

    mat_t expect_a{{-1, 1,  0},
                   {1,  -1, 0},
                   {0,  0,  1}};

    EXPECT_EQ(_a(1, 1, 2, 2) - _b(0, 0, 1, 1), expect_a1122);

    _a(0, 0, 1, 1) -= _b(0, 0, 1, 1);
    ASSERT_EQ(_a, expect_a);
}

TEST_F(NPMatrixFuncOpTest, Prod) {

    mat_t expect_b0011{{10, -5},
                       {-5, 10}};

    mat_t expect_a{{1, 0, 0},
                   {0, 5, 0},
                   {0, 0, 5}};

    double x = 5;
    ASSERT_EQ(_b(0, 0, 1, 1) * x, expect_b0011);

    _a(1, 1, 2, 2) *= x;
    ASSERT_EQ(_a, expect_a);
}

TEST_F(NPMatrixFuncOpTest, Div) {
    mat_t expect_b0011{{1,    -0.5},
                       {-0.5, 1}};

    mat_t expect_a{{1, 0,   0},
                   {0, 0.5, 0},
                   {0, 0,   0.5}};

    double x = 2;

    ASSERT_EQ(_b(0, 0, 1, 1) / x, expect_b0011);

    _a(1, 1, 2, 2) /= x;
    ASSERT_EQ(_a, expect_a);

}

TEST_F(NPMatrixFuncOpTest, Shift) {
    mat_t expect_a_shift_row_01{{0, 1, 0},
                                {0, 1, 0},
                                {0, 0, 1}};

    mat_t expect_a_shift_col_1m1{{0, 1, 0},
                                 {0, 1, 1},
                                 {0, 0, 0}};

    _a(0, 0, 1, 1).shiftRow(0, 1);
    ASSERT_EQ(_a, expect_a_shift_row_01);


    _a(1, 1, 2, 2).shiftCol(1, -1);
    ASSERT_EQ(_a, expect_a_shift_col_1m1);
}

TEST_F(NPMatrixFuncOpTest, Transposed) {
    mat_t expect_c1122{{2, 10},
                       {1, 2}};

    ASSERT_EQ(_c(1, 1, 2, 2).transposed(), expect_c1122);
}

TEST_F(NPMatrixFuncOpTest, MatrixProd) {
    mat_t expect_b{_b};
    expect_b(1, 1, 2, 2) *= 2;

    EXPECT_EQ(_b(1, 1, 2, 2) * (2 * _a(1, 1, 2, 2)), expect_b(1, 1, 2, 2));

    _b(1, 1, 2, 2) *= (2 * _a(1, 1, 2, 2));
    ASSERT_EQ(_b, expect_b);
}

TEST_F(NPMatrixFuncOpTest, VectorProd) {

    vec_t u{1, 2, 3};
    vec_t expect_prod_cu{0, 5};

    ASSERT_EQ(_c(0, 0, 1, 1) * u(0, 1), expect_prod_cu);

}

TEST_F(NPMatrixFuncOpTest, Pow) {

    mat_t b_pow_2{_b};
    b_pow_2(1, 1, 2, 2) = b_pow_2(1, 1, 2, 2);
    std::cout << b_pow_2;
    b_pow_2(1, 1, 2, 2) *= b_pow_2(1, 1, 2, 2);
    std::cout << b_pow_2;
    std::cout << _b;

    EXPECT_EQ(_b(1, 1, 2, 2) ^ 2, b_pow_2(1, 1, 2, 2));

    _b(1, 1, 2, 2) ^= 2;
    ASSERT_EQ(_b, b_pow_2);
}

TEST_F(NPMatrixFuncOpTest, Inv) {
    mat_t expect_b0011_inv{{2, 1},
                           {1, 2}};
    mat_t expect_b_inv{_b};
    mat_t expect_a{_a};

    mat_t b0011_inv = _b(0, 0, 1, 1) ^-1;

    expect_b0011_inv /= 3;

    expect_b_inv(0, 0, 1, 1) = expect_b0011_inv;

    ASSERT_EQ(b0011_inv, expect_b0011_inv);

    ASSERT_DOUBLE_EQ((_b(0, 0, 1, 1) * b0011_inv) / _a(0, 0, 1, 1), 0);

    _b(0, 0, 1, 1) ^= -1;
    ASSERT_EQ(_b, expect_b_inv);
}

TEST_F(NPMatrixFuncOpTest, Det) {
    ASSERT_EQ(_c(1, 1, 2, 2).det(), -6);
}

TEST_F(NPMatrixFuncOpTest, Solve) {

    const vec_t u{1, 2, 5}, sol = vec_t{4.0 / 3.0, 5.0 / 3.0};
    mat_t copy_b0011{_b(0, 0, 1, 1)};

    EXPECT_NEAR(_b(0, 0, 1, 1) * (copy_b0011 % u(0, 1)) / u(0, 1), 0, 5e-16);
    ASSERT_NEAR(_b(0, 0, 1, 1) % u(0, 1) / sol, 0, 5e-16);

}