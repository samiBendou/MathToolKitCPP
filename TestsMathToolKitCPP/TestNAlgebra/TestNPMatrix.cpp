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

        _b = "  ( 2 1 0) \
                (-1 2 1) \
                (0 -1 2)";

        _c = "  (0 0 0) \
                (1 2 1) \
                (5 10 2)";
    }

    NPMatrix<double> _a{0, 0};
    NPMatrix<double> _b{0, 0};
    NPMatrix<double> _c{0, 0};
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
    _a = "  ( 2 1 0) \
            (-1 2 1) \
            (0 -1 2)";

    ASSERT_EQ(_a, _b);

    _a = _c;
    ASSERT_EQ(_a, _c);
}

TEST_F(NPMatrixTest, Construction) {

    _a = NPMatrix<double>(5);
    ASSERT_EQ(_a.n(), 5);
    ASSERT_EQ(_a.p(), 5);
    ASSERT_TRUE(_a == 0);


    _a = NPMatrix<double>(_b);
    ASSERT_EQ(_a, _b);


    _a = NPMatrix<double>(NVector<double>("(0 0 0)"));
    ASSERT_EQ(_a.n(), 1);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_TRUE(_a == 0);


    _a = NPMatrix<double>(NVector<double>("(0 0 0 1 2 1 5 10 2)"), 3, 3);
    ASSERT_EQ(_a.n(), 3);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_EQ(_a, _c);


    std::vector<std::vector<double> > expect_c{{0, 0, 0},
                                               {1, 2, 1},
                                               {5, 10, 2}};
    _a = NPMatrix<double>(expect_c);
    ASSERT_EQ(_a, _c);


    std::vector<NVector<double> > expect_b{
            NVector<double>("( 2 1 0)"),
            NVector<double>("( -1 2 1)"),
            NVector<double>("( 0 -1 2)")
    };
    _a = NPMatrix<double>(expect_b);
    ASSERT_EQ(_a, _b);


    _a = NPMatrix<double>(" (0 0 0) \
                    (1 2 1) \
                    (5 10 2)"
                  );
    ASSERT_EQ(_a, _c);
}

TEST_F(NPMatrixTest, Getters) {
    ASSERT_EQ(_b.row(0), "(2 1 0)");
    ASSERT_EQ(_b.row(1), "(-1 2 1)");
    ASSERT_EQ(_b.row(2), "(0 -1 2)");

    ASSERT_EQ(_b.col(0), "(2 -1 0)");
    ASSERT_EQ(_b.col(1), "(1 2 -1)");
    ASSERT_EQ(_b.col(2), "(0 1 2)");

    auto rows_b = _b.rows();
    auto cols_b = _b.cols();

    ASSERT_EQ(rows_b[0], "(2 1 0)");
    ASSERT_EQ(rows_b[1], "(-1 2 1)");
    ASSERT_EQ(rows_b[2], "(0 -1 2)");

    ASSERT_EQ(cols_b[0], "(2 -1 0)");
    ASSERT_EQ(cols_b[1], "(1 2 -1)");
    ASSERT_EQ(cols_b[2], "(0 1 2)");
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
    NPMatrix<double> expect_a_swap_1110{"   (1  0  0) \
                                    (1  0  0) \
                                    (0  0  1)"
    };
    NPMatrix<double> expect_b_swap_col_01{" (1  2   0) \
                                    (2  -1  1) \
                                    (-1 0   2)"
    };

    NPMatrix<double> expect_c_swap_row_01{" (1  2   1) \
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
    NPMatrix<double> copy_b{_b};

    _b.shiftRow(0, 1);
    ASSERT_EQ(_b.row(0), "(1 0 2)");

    _b.shiftRow(0, -1);
    ASSERT_EQ(_b, copy_b);

    _b.shiftRow(0, 2);
    ASSERT_EQ(_b.row(0), "(0 2 1)");

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
    NPMatrix<double> copy_b{_b};
    NPMatrix<double> expect_add_b{" ( 4 2 0) \
                            (-2 4 2) \
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
    NPMatrix<double> copy_b{_b};
    NPMatrix<double> expect_prod_b{"( 4 2 0) \
                            (-2 4 2) \
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
    NPMatrix<double> expect_trans_c{"   (0 1 5) \
                                (0 2 10) \
                                (0 1 2)"
                                  };


    ASSERT_EQ(_c.transposed(), expect_trans_c);

    NPMatrix<double> u = NPMatrix<double>(_c.col(1));
    NPMatrix<double> v = u.transposed();

    EXPECT_EQ(u.n(), 1);
    ASSERT_EQ(u.p(), 3);

    EXPECT_EQ(v.n(), 3);
    ASSERT_EQ(v.p(), 1);
}

TEST_F(NPMatrixTest, MatrixProd) {
    auto expect_prod_b{2 * _b};
    NPMatrix<double> expect_prod_vu{"   (1 2) \
                                (2 4)" };

    EXPECT_EQ(_b * (2 * _a), expect_prod_b);
    _b *= (2 * _a);
    ASSERT_EQ(_b, expect_prod_b);

    NPMatrix<double> u = NPMatrix<double>("(1 2)");
    NPMatrix<double> v{u.transposed()};


    ASSERT_EQ(u * v, NPMatrix<double>("(5)"));

    ASSERT_EQ(v * u, expect_prod_vu);
}

TEST_F(NPMatrixTest, VectorProd) {
    NVector<double> u{"(1 2 3)"};
    NVector<double> expect_prod_cu{"(0 8 31)"};

    ASSERT_EQ(_c * u, expect_prod_cu);
}

TEST_F(NPMatrixTest, GaussJordan) {
    _c = _b.shifted(_a);
    _c.reduce();
    ASSERT_EQ(_c(0, 0, 2, 2), _a);
}

TEST_F(NPMatrixTest, StaticGenerators) {
    NPMatrix<double> expect_zeros{" (0 0 0)\
                            (0 0 0)"
    };
    EXPECT_EQ(NPMatrix<double>::zeros(2, 3), expect_zeros);

    NPMatrix<double> expect_ones{"  (1 1 1)\
                            (1 1 1)"
    };
    EXPECT_EQ(NPMatrix<double>::ones(2, 3), expect_ones);

    NPMatrix<double> expect_canonical{" (0 0 0)\
                                (0 1 0)"
    };
    EXPECT_EQ(NPMatrix<double>::canonical(1, 1, 2, 3), expect_canonical);
}