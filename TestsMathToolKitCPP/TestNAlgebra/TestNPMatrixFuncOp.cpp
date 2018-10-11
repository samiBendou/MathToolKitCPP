//
// Created by Sami Dahoux on 27/09/2018.
//

#include <NPMatrix.h>
#include "gtest/gtest.h"


class NPMatrixFuncOpTest : public ::testing::Test {

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



TEST_F(NPMatrixFuncOpTest, Dim) {

}

TEST_F(NPMatrixFuncOpTest, Equality) {

    NPMatrix expect_b1122{
            "(2  1) \
             (-1 2)"
    };
    NPMatrix copy_b{_b};

    ASSERT_TRUE(_b(1, 1, 2, 2) == expect_b1122);
    ASSERT_TRUE(_b(1, 1, 2, 2) == copy_b(1, 1, 2, 2));
    ASSERT_TRUE(_b == copy_b(0, 0, 2, 2));
}

TEST_F(NPMatrixFuncOpTest, AffectationAccess) {

    NPMatrix expect_b0011{" (3  1) \
                            (-1 2)"
    };

    NPMatrix new_b0011{"    (6  1) \
                            (-1 2)"
    };

    NPMatrix expect_a0011{" (1  0) \
                            (0  1)"
    };

    NPMatrix expect_b1122{" (1  1) \
                            (-1 2)"
    };

    ASSERT_EQ(_b(0, 0), 2);
    ASSERT_EQ(_b(0, 1), 1);
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
    NPMatrix expect_a1122{" (3  1) \
                            (-1 3)"
    };

    NPMatrix expect_a{"     (3  1   0) \
                            (-1 3   0) \
                            (0  0   1)"
    };

    EXPECT_EQ(_a(1, 1, 2, 2) + _b(0, 0, 1, 1), expect_a1122);

    _a(0, 0, 1, 1) += _b(0, 0, 1, 1);
    ASSERT_EQ(_a, expect_a);
}

TEST_F(NPMatrixFuncOpTest, Sub) {
    NPMatrix expect_a1122{" (-1 -1) \
                            ( 1 -1)"
    };

    NPMatrix expect_a{"     (-1 -1  0) \
                            (1  -1  0) \
                            (0  0   1)"
    };
    EXPECT_EQ(_a(1, 1, 2, 2) - _b(0, 0, 1, 1), expect_a1122);

    _a(0, 0, 1, 1) -= _b(0, 0, 1, 1);
    ASSERT_EQ(_a, expect_a);
}

TEST_F(NPMatrixFuncOpTest, Prod) {

    NPMatrix expect_b0011{" (10 5) \
                            (-5 10)"
    };

    NPMatrix expect_a{"     (1  0   0) \
                            (0  5   0) \
                            (0  0   5)"
    };

    double x = 5;
    ASSERT_EQ( _b(0, 0, 1, 1) * x, expect_b0011);

    _a(1, 1, 2, 2) *= x;
    ASSERT_EQ(_a, expect_a);
}

TEST_F(NPMatrixFuncOpTest, Div) {
    NPMatrix expect_b0011{" (1      0.5 ) \
                            (-0.5   1   )"
    };

    NPMatrix expect_a{"     (1  0   0   ) \
                            (0  0.5 0   ) \
                            (0  0   0.5 )"
    };

    double x = 2;

    ASSERT_EQ(_b(0, 0, 1, 1) / x, expect_b0011);

    _a(1, 1, 2, 2) /= x;
    ASSERT_EQ(_a, expect_a);

}

TEST_F(NPMatrixFuncOpTest, Shift) {
    NPMatrix expect_a_shift_row_01{
            "(0 1 0) \
             (0 1 0) \
             (0 0 1)"
    };

    NPMatrix expect_a_shift_col_1m1{
            "(0 1 0) \
             (0 1 1) \
             (0 0 0)"
    };

    _a(0, 0, 1, 1).shiftRow(0, 1);
    ASSERT_EQ(_a, expect_a_shift_row_01);


    _a(1, 1, 2, 2).shiftCol(1, -1);
    ASSERT_EQ(_a, expect_a_shift_col_1m1);
}

TEST_F(NPMatrixFuncOpTest, Transposed) {
    NPMatrix expect_c1122{" (2 10) \
                            (1  2)"
    };

    ASSERT_EQ(_c(1, 1, 2, 2).transposed(), expect_c1122);
}

TEST_F(NPMatrixFuncOpTest, MatrixProd) {
    auto expect_b{2 * _b(1, 1, 2, 2)};

    EXPECT_EQ(_b(1, 1, 2, 2) * (2 * _a(1, 1, 2, 2)), expect_b);
}

TEST_F(NPMatrixFuncOpTest, VectorProd) {
    NVector<double> u{"(1 2 3)"};
    NVector<double> expect_prod_cu{"(0 5)"};

    ASSERT_EQ(_c(0, 0, 1, 1) * u(0, 1), expect_prod_cu);
}