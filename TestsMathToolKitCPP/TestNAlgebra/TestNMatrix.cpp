//
// Created by Sami Dahoux on 04/10/2018.
//

#include <NPMatrix.h>
#include "gtest/gtest.h"


class NMatrixTest : public ::testing::Test {

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