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

    NPMatrix _a{0, 0};
    NPMatrix _b{0, 0};
    NPMatrix _c{0, 0};
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

    _a = NPMatrix(5);
    ASSERT_EQ(_a.n(), 5);
    ASSERT_EQ(_a.p(), 5);
    ASSERT_TRUE(_a == 0);


    _a = NPMatrix(_b);
    ASSERT_EQ(_a, _b);


    _a = NPMatrix(NVector("(0 0 0)"));
    ASSERT_EQ(_a.n(), 1);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_TRUE(_a == 0);


    _a = NPMatrix(NVector("(0 0 0 1 2 1 5 10 2)"), 3, 3);
    ASSERT_EQ(_a.n(), 3);
    ASSERT_EQ(_a.p(), 3);
    ASSERT_EQ(_a, _c);


    std::vector<std::vector<double> > expect_c{{0, 0, 0},
                                               {1, 2, 1},
                                               {5, 10, 2}};
    _a = NPMatrix(expect_c);
    ASSERT_EQ(_a, _c);


    std::vector<NVector> expect_b{
            NVector("( 2 1 0)"),
            NVector("( -1 2 1)"),
            NVector("( 0 -1 2)")
    };
    _a = NPMatrix(expect_b);
    ASSERT_EQ(_a, _b);


    _a = NPMatrix(" (0 0 0) \
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
    NPMatrix mat_b{_b};

    _b.swap(0, 1, 1, 0);
    _b.swap(0, 1, 1, 0);
    ASSERT_EQ(_b, mat_b);

    _b.swapCol(0, 1);
    _b.swapCol(0, 1);
    ASSERT_EQ(_b, mat_b);

    _b.swapRow(0, 1);
    _b.swapRow(0, 1);
    ASSERT_EQ(_b, mat_b);
}

TEST_F(NPMatrixTest, Shift) {
    NPMatrix copy_b{_b};

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

/*
TEST_F(NPMatrixTest, MaxAbsIndexRowCol) {
    ASSERT_EQ(_b.maxAbsIndexRow(0, 0), 0);
    ASSERT_EQ(_b.maxAbsIndexRow(0, 1), 1);
    ASSERT_EQ(_b.maxAbsIndexRow(0, 2), 2);

    ASSERT_EQ(_c.maxAbsIndexRow(0, 0), 0);
    ASSERT_EQ(_c.maxAbsIndexRow(0, 1), 1);
    ASSERT_EQ(_c.maxAbsIndexRow(0, 2), 2);
}
*/

TEST_F(NPMatrixTest, Add) {
    NPMatrix copy_b{_b};
    NPMatrix expect_add_b{" ( 4 2 0) \
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
    NPMatrix copy_b{_b};
    NPMatrix expect_prod_b{"( 4 2 0) \
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
    NPMatrix expect_trans_c{"   (0 1 5) \
                                (0 2 10) \
                                (0 1 2)"
                                  };


    ASSERT_EQ(_c.transposed(), expect_trans_c);

    NPMatrix u = NPMatrix(_c.col(1));
    NPMatrix v = u.transposed();

    EXPECT_EQ(u.n(), 1);
    ASSERT_EQ(u.p(), 3);

    EXPECT_EQ(v.n(), 3);
    ASSERT_EQ(v.p(), 1);
}

TEST_F(NPMatrixTest, MatrixProd) {
    auto expect_prod_b{2 * _b};
    NPMatrix expect_prod_vu{"   (1 2) \
                                (2 4)" };

    EXPECT_EQ(_b * (2 * _a), expect_prod_b);
    _b *= (2 * _a);
    ASSERT_EQ(_b, expect_prod_b);

    NPMatrix u = NPMatrix("(1 2)");
    NPMatrix v{u.transposed()};


    ASSERT_EQ(u * v, NPMatrix("(5)"));

    ASSERT_EQ(v * u, expect_prod_vu);
}

TEST_F(NPMatrixTest, VectorProd) {
    NVector u{"(1 2 3)"};
    NVector expect_prod_cu{"(0 8 31)"};

    ASSERT_EQ(_c * u, expect_prod_cu);
}

TEST_F(NPMatrixTest, GaussJordan) {
    _c = _b.shifted(_a);
    _c.reduce();
    ASSERT_EQ(_c(0, 0, 2, 2), _a);
}

TEST_F(NPMatrixTest, StaticGenerators) {
    NPMatrix expect_zeros{" (0 0 0)\
                            (0 0 0)"
    };
    EXPECT_EQ(NPMatrix::zeros(2, 3), expect_zeros);

    NPMatrix expect_ones{"  (1 1 1)\
                            (1 1 1)"
    };
    EXPECT_EQ(NPMatrix::ones(2, 3), expect_ones);

    NPMatrix expect_canonical{" (0 0 0)\
                                (0 1 0)"
    };
    EXPECT_EQ(NPMatrix::canonical(1, 1, 2, 3), expect_canonical);
}