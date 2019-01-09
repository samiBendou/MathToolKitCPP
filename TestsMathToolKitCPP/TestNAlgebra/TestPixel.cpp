//
// Created by Sami Dahoux on 25/12/2018.
//

#include <Pixel.h>
#include "gtest/gtest.h"

class PixelTest : public ::testing::Test {

protected:
    void SetUp() override {
        _a = Pixel(10);
        _b = Pixel(10, 11, 12);
        _c = Pixel(Pixel::GScale);
        _d = Pixel(Pixel::RGB);

    }

    Pixel _a, _b, _c, _d;
};


TEST_F(PixelTest, Getters) {
    ASSERT_EQ(_a.grey(), 10);
    ASSERT_EQ(_a.red(), 10);
    ASSERT_EQ(_a.green(), 10);
    ASSERT_EQ(_a.blue(), 10);


    ASSERT_EQ(_b.grey(), 11);
    ASSERT_EQ(_b.red(), 10);
    ASSERT_EQ(_b.green(), 11);
    ASSERT_EQ(_b.blue(), 12);

    ASSERT_EQ(_c.grey(), 0);

    ASSERT_EQ(_d.red(), 0);
    ASSERT_EQ(_d.green(), 0);
    ASSERT_EQ(_d.blue(), 0);
}