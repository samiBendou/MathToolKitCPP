//
// Created by Sami Dahoux on 20/09/2018.
//

#include <NVector.h>
#include "gtest/gtest.h"

#define DIM_TEST 3

TEST(TestNVector, add) {
    NVector vector1 = NVector::canonical(1, DIM_TEST) + 2 * NVector::canonical(2, DIM_TEST);
    ASSERT_EQ(vector1, vector1 * 2);
}

