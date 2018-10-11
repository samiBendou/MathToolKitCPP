//
// Created by Sami Dahoux on 22/09/2018.
//

#include <NPMatrix.h>
#include "gtest/gtest.h"


class NPMatrixTest : public ::testing::Test {

protected:
    void SetUp() override {

        _a = "  (1 0 0) \
                (0 1 0) \
                (0 0 1)";

        _b = "  ( 2 -1 0) \
                (-1 2 -1) \
                (0 -1 2)";

        _c = "  (0 0 0) \
                (1 2 1) \
                (5 10 2)";
    }

    mat_t _a{0, 0};
    mat_t _b{0, 0};
    mat_t _c{0, 0};
};


TEST_F(NPMatrixTest, Dim) {
    ASSERT_EQ(_a.n(), 3);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_TRUE(_a.isSquare());
}

TEST_F(NPMatrixTest, Equality) {
    ASSERT_FALSE(_a == _b);
    ASSERT_TRUE(_a != _b);

    ASSERT_TRUE(_a == _a);
    ASSERT_FALSE(_a != _a);
}

TEST_F(NPMatrixTest, Affectation) {
    _a = "  ( 2 -1 0) \
            (-1 2 -1) \
            (0 -1 2)";

    ASSERT_EQ(_a, _b);

    _a = _c;
    ASSERT_EQ(_a, _c);
}

TEST_F(NPMatrixTest, Construction) {

    _a = mat_t(5);
    ASSERT_EQ(_a.n(), 5);
    ASSERT_EQ(_a.p(), 5);
    ASSERT_TRUE(_a == 0);


    _a = mat_t(_b);
    ASSERT_EQ(_a, _b);


    _a = mat_t(vec_t("(0 0 0)"));
    ASSERT_EQ(_a.n(), 1);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_TRUE(_a == 0);


    _a = mat_t(vec_t("(0 0 0 1 2 1 5 10 2)"), 3, 3);
    ASSERT_EQ(_a.n(), 3);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_EQ(_a, _c);


    std::vector<std::vector<double> > expect_c{{0, 0,  0},
                                               {1, 2,  1},
                                               {5, 10, 2}};
    _a = mat_t(expect_c);
    ASSERT_EQ(_a, _c);


    std::vector<vec_t> expect_b{
            vec_t("( 2 -1 0)"),
            vec_t("( -1 2 -1)"),
            vec_t("( 0 -1 2)")
    };
    _a = mat_t(expect_b);
    ASSERT_EQ(_a, _b);


    _a = mat_t(" (0 0 0) \
                    (1 2 1) \
                    (5 10 2)"
    );
    ASSERT_EQ(_a, _c);
}

TEST_F(NPMatrixTest, Getters) {
    std::vector<std::string> expect_rows_c{"(0 0 0)", "(1 2 1)", "(5 10 2)"};
    std::vector<std::string> expect_col_c{"(0 1 5)", "(0 2 10)", "(0 1 2)"};

    auto rows_c = _c.rows();
    auto cols_c = _c.cols();

    for (int k = 0; k < 3; ++k) {
        ASSERT_EQ(_c.row(k), expect_rows_c[k]);
        ASSERT_EQ(_c.col(k), expect_col_c[k]);

        ASSERT_EQ(rows_c[k], expect_rows_c[k]);
        ASSERT_EQ(cols_c[k], expect_col_c[k]);
    }
}

TEST_F(NPMatrixTest, Setters) {
    _a.setRow(_b.row(0), 0);
    _a.setRow(_b.row(1), 1);
    _a.setRow(_b.row(2), 2);

    ASSERT_EQ(_a, _b);

    auto rows_c = _c.rows();
    _a.setRows(rows_c);
    ASSERT_EQ(_a, _c);

    auto cols_b = _b.cols();
    _a.setCols(cols_b);
    ASSERT_EQ(_a, _b);
}

TEST_F(NPMatrixTest, Swap) {
    mat_t expect_a_swap_1110{"   (1  0  0) \
                                    (1  0  0) \
                                    (0  0  1)"
    };
    mat_t expect_b_swap_col_01{" (-1  2   0) \
                                    (2  -1  -1) \
                                    (-1 0   2)"
    };

    mat_t expect_c_swap_row_01{" (1  2   1) \
                                    (0  0   0) \
                                    (5  10  2)"
    };

    _a.swap(1, 1, 1, 0);
    ASSERT_EQ(_a, expect_a_swap_1110);

    _b.swapCol(0, 1);
    ASSERT_EQ(_b, expect_b_swap_col_01);

    _c.swapRow(0, 1);
    ASSERT_EQ(_c, expect_c_swap_row_01);
}

TEST_F(NPMatrixTest, Shift) {
    mat_t copy_b{_b};

    _b.shiftRow(0, 1);
    ASSERT_EQ(_b.row(0), "(-1 0 2)");

    _b.shiftRow(0, -1);
    ASSERT_EQ(_b, copy_b);

    _b.shiftRow(0, 2);
    ASSERT_EQ(_b.row(0), "(0 2 -1)");

    _b.shiftRow(0, -2);
    ASSERT_EQ(_b, copy_b);

    _b.shiftCol(0, 1);
    ASSERT_EQ(_b.col(0), "(-1 0 2)");

    _b.shiftCol(0, -1);
    ASSERT_EQ(_b, copy_b);

    _b.shiftCol(0, 2);
    ASSERT_EQ(_b.col(0), "(0 2 -1)");

    _b.shiftCol(0, -2);
    ASSERT_EQ(_b, copy_b);
}

TEST_F(NPMatrixTest, Add) {
    mat_t copy_b{_b};
    mat_t expect_add_b{" ( 4 -2 0) \
                            (-2 4 -2) \
                            (0 -2 4)"
    };


    EXPECT_EQ(_b + _b, expect_add_b);

    _b += copy_b;
    ASSERT_EQ(_b, expect_add_b);

    EXPECT_EQ(_b - copy_b, copy_b);

    _b -= copy_b;
    ASSERT_EQ(_b, copy_b);
}

TEST_F(NPMatrixTest, Prod) {
    mat_t copy_b{_b};
    mat_t expect_prod_b{"( 4 -2 0) \
                            (-2 4 -2) \
                            (0 -2 4)"
    };

    double x = 2;

    EXPECT_EQ(x * _b, expect_prod_b);

    _b *= x;
    ASSERT_EQ(_b, expect_prod_b);

    EXPECT_EQ(_b / x, copy_b);

    _b /= x;
    ASSERT_EQ(_b, copy_b);
}


TEST_F(NPMatrixTest, EuclideanOperations) {
    ASSERT_EQ(!_a, sqrt(3));
    ASSERT_EQ(_a | _a, 3);
    ASSERT_EQ(_a / _b, sqrt(7));
}

TEST_F(NPMatrixTest, Transposed) {
    mat_t expect_trans_c{"   (0 1 5) \
                                (0 2 10) \
                                (0 1 2)"
    };


    ASSERT_EQ(_c.transposed(), expect_trans_c);

    mat_t u = mat_t(_c.col(1));
    mat_t v = u.transposed();

    EXPECT_EQ(u.n(), 1);
    ASSERT_EQ(u.p(), 3);

    EXPECT_EQ(v.n(), 3);
    ASSERT_EQ(v.p(), 1);
}

TEST_F(NPMatrixTest, MatrixProd) {
    auto expect_prod_b{2 * _b};
    mat_t expect_prod_vu{"   (1 2) \
                                (2 4)"};

    EXPECT_EQ(_b * (2 * _a), expect_prod_b);
    _b *= (2 * _a);
    ASSERT_EQ(_b, expect_prod_b);

    mat_t u = mat_t("(1 2)");
    mat_t v{u.transposed()};


    ASSERT_EQ(u * v, mat_t("(5)"));

    ASSERT_EQ(v * u, expect_prod_vu);
}

TEST_F(NPMatrixTest, VectorProd) {
    vec_t u{"(1 2 3)"};
    vec_t expect_prod_cu{"(0 8 31)"};

    ASSERT_EQ(_c * u, expect_prod_cu);
}

TEST_F(NPMatrixTest, GaussJordan) {
    _c = _b.shifted(_a);
    _c.reduce();
    ASSERT_EQ(_c(0, 0, 2, 2), _a);
}

TEST_F(NPMatrixTest, Pow) {
    mat_t b_pow_2 = _b * _b;
    mat_t b_pow_3 = _b * _b * _b;

    EXPECT_EQ(_b ^ 2, b_pow_2);
    EXPECT_EQ(_b ^ 3, b_pow_3);

    _b ^= 2;
    ASSERT_EQ(_b, b_pow_2);
}

TEST_F(NPMatrixTest, LUP) {
    mat_t b_lup_low = _b.lupL();
    mat_t b_lup_up = _b.lupU();

    mat_t expect_lup_low{"(1      0      0) \
                            (-0.5   1      0) \
                            (0      -0.666 1)"

    };
    expect_lup_low(2, 1) = -2.0 / 3.0;
    ASSERT_NEAR(b_lup_low / expect_lup_low, 0, 0);

    mat_t expect_lup_up{" (2  -1   0      ) \
                            (0  1.5  -1     ) \
                            (0  0    1.333  )"

    };
    expect_lup_up(2, 2) = 4.0 / 3.0;
    ASSERT_NEAR(b_lup_up / expect_lup_up, 0, 2.2204460492503131e-16);

    ASSERT_EQ(b_lup_low * b_lup_up, _b);
}

TEST_F(NPMatrixTest, Inv) {

    mat_t expect_b_inv{"  (0.75 0.5 0.25) \
                            (0.50 1.0 0.50) \
                            (0.25 0.5 0.75)"};
    mat_t expect_a{_a};

    ASSERT_EQ(_a ^ -1, _a);
    ASSERT_EQ(_b ^ -1, expect_b_inv);
    ASSERT_NEAR(_b * (_b ^ -1) / expect_a, 0, 2.5589376332604516e-16);
}

TEST_F(NPMatrixTest, Det) {
    ASSERT_DOUBLE_EQ(_a.det(), 1);
    ASSERT_DOUBLE_EQ((-_a).det(), -1);

    ASSERT_DOUBLE_EQ(_b.det(), 4);
    ASSERT_DOUBLE_EQ((_b ^ -1).det(), 0.25);
    ASSERT_DOUBLE_EQ((_b * (_b ^ -1)).det(), 1);

    ASSERT_DOUBLE_EQ(_c.det(), 0);
}

TEST_F(NPMatrixTest, Solve) {
    vec_t u{"(1 2 5)"}, expect_sol{"(3 5 5)"};

    ASSERT_NEAR(_b % u / expect_sol, 0, 1.3322676295501878e-15);
    ASSERT_NEAR(_b * (_b % u) / u, 0, 1.2560739669470201e-15);
}

TEST_F(NPMatrixTest, StaticGenerators) {
    mat_t expect_zeros{" (0 0 0)\
                            (0 0 0)"
    };
    EXPECT_EQ(mat_t::zeros(2, 3), expect_zeros);

    mat_t expect_ones{"  (1 1 1)\
                            (1 1 1)"
    };
    EXPECT_EQ(mat_t::ones(2, 3), expect_ones);

    mat_t expect_canonical{" (0 0 0)\
                                (0 1 0)"
    };
    EXPECT_EQ(mat_t::canonical(1, 1, 2, 3), expect_canonical);

    EXPECT_EQ(mat_t::eye(3), _a);
    EXPECT_EQ(mat_t::scalar(1, 3), _a);

    std::vector<vec_t> data{vec_t("(-1 -1)"),
                            vec_t("(2 2 2)"),
                            vec_t("(-1 -1)")};

    EXPECT_EQ(mat_t::ndiag(data), _b);

    EXPECT_EQ(mat_t::nscalar({-1, 2}, 3), _b);
}