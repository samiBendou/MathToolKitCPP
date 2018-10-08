//
// Created by Sami Dahoux on 04/10/2018.
//

#include <NMatrix.h>
#include "gtest/gtest.h"


class NMatrixTest : public ::testing::Test {

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

TEST_F(NMatrixTest, Equality) {
    ASSERT_FALSE(_a == _b);
    ASSERT_TRUE(_a != _b);

    ASSERT_TRUE(_a == _a);
    ASSERT_FALSE(_a != _a);
}

TEST_F(NMatrixTest, Affectation) {
    NPMatrix copy_b{_b};

    _a = copy_b;
    ASSERT_EQ(_a, _b);

    _a = _c;
    ASSERT_EQ(_a, _c);
}

TEST_F(NMatrixTest, Construction) {

    _a = NMatrix(5);
    ASSERT_EQ(_a.n(), 5);
    ASSERT_EQ(_a.p(), 5);
    ASSERT_TRUE(_a == 0);


    _a = NMatrix(_b);
    ASSERT_EQ(_a, _b);

    _a = NMatrix("  (0 0 0) \
                    (1 2 1) \
                    (5 10 2)"
    );
    ASSERT_EQ(_a, _c);
}

TEST_F(NMatrixTest, Add) {
    NMatrix copy_b{_b};
    NMatrix expect_add_b{"  ( 4 -2 0) \
                            (-2 4 -2) \
                            (0 -2 4)"
    };

    _b += copy_b;
    ASSERT_EQ(_b, expect_add_b);

    _b -= copy_b;
    ASSERT_EQ(_b, copy_b);
}

TEST_F(NMatrixTest, Prod) {
    NMatrix copy_b{_b};
    NMatrix expect_prod_b{" ( 4 -2 0) \
                            (-2 4 -2) \
                            (0 -2  4)"
    };

    double x = 2;

    _b *= x;
    ASSERT_EQ(_b, expect_prod_b);

    _b /= x;
    ASSERT_EQ(_b, copy_b);

}

TEST_F(NMatrixTest, MatrixProd) {
    auto expect_prod_b{2 * _b};

    _b *= (2 * _a);
    ASSERT_EQ(_b, expect_prod_b);
}

TEST_F(NMatrixTest, Pow) {
    NMatrix b_pow_2 = _b *_b;
    NMatrix b_pow_3 = _b * _b * _b;

    EXPECT_EQ(_b ^ 2, b_pow_2);
    EXPECT_EQ(_b ^ 3, b_pow_3);

    _b ^= 2;
    ASSERT_EQ(_b, b_pow_2);
}

TEST_F(NMatrixTest, LUP) {
    NMatrix b_lup_low = _b.lupL();
    NMatrix b_lup_up = _b.lupU();

    NMatrix expect_lup_low{"(1      0      0) \
                            (-0.5   1      0) \
                            (0      -0.666 1)"

    };
    expect_lup_low(2, 1) = -2.0/3.0;
    ASSERT_NEAR(b_lup_low / expect_lup_low, 0, 0);

    NMatrix expect_lup_up{" (2  -1   0      ) \
                            (0  1.5  -1     ) \
                            (0  0    1.333  )"

    };
    expect_lup_up(2, 2) = 4.0/3.0;
    ASSERT_NEAR(b_lup_up / expect_lup_up, 0, 2.2204460492503131e-16);

    ASSERT_EQ(b_lup_low * b_lup_up, _b);
}

TEST_F(NMatrixTest, Inv) {

    NMatrix expect_b_inv{"  (0.75 0.5 0.25) \
                            (0.50 1.0 0.50) \
                            (0.25 0.5 0.75)" };
    NMatrix expect_a{_a};

    ASSERT_EQ(_a^-1, _a);
    ASSERT_EQ(_b^-1, expect_b_inv);
    ASSERT_NEAR(_b * (_b^-1) / expect_a, 0, 2.5589376332604516e-16);
}

TEST_F(NMatrixTest, Det) {
    ASSERT_DOUBLE_EQ(_a.det(), 1);
    ASSERT_DOUBLE_EQ((-_a).det(), -1);

    ASSERT_DOUBLE_EQ(_b.det(), 4);
    ASSERT_DOUBLE_EQ((_b^-1).det(), 0.25);
    ASSERT_DOUBLE_EQ((_b * (_b^-1)).det(), 1);

    ASSERT_DOUBLE_EQ(_c.det(), 0);
}

TEST_F(NMatrixTest, Solve) {
    NVector u{"(1 2 5)"}, expect_sol{"(3 5 5)"};

    ASSERT_NEAR(_b % u / expect_sol, 0, 1.3322676295501878e-15);
    ASSERT_NEAR(_b * (_b % u) / u, 0, 1.2560739669470201e-15);
}

TEST_F(NMatrixTest, StaticGenerators) {
    ASSERT_EQ(NMatrix::eye(3), _a);
    ASSERT_EQ(NMatrix::scalar(1, 3), _a);

    std::vector<NVector> data{NVector("(-1 -1)"),
                              NVector("(2 2 2)"),
                              NVector("(-1 -1)")};

    ASSERT_EQ(NMatrix::ndiag(data), _b);

    ASSERT_EQ(NMatrix::nscalar({-1, 2}, 3), _b);
}