//
// Created by Sami Dahoux on 25/12/2018.
//

#include <Pixel.h>
#include <gtest/gtest.h>

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
    EXPECT_EQ(_a.grey(), 10);
    EXPECT_EQ(_a.red(), 10);

    EXPECT_EQ(_b.grey(), 11);
    EXPECT_EQ(_b.green(), 11);

    EXPECT_EQ(_c.grey(), 0);

    EXPECT_EQ(_d.blue(), 0);
}

TEST_F(PixelTest, Setters) {
    EXPECT_EQ(_c.setRed(4), Pixel(4, 0, 0));
    EXPECT_EQ(_c.setGrey(5), Pixel(5));

    EXPECT_EQ(_b.setGrey(5), Pixel(5));
    EXPECT_EQ(_b.setRed(4), Pixel(4, 5, 5));
}

TEST_F(PixelTest, Limit) {
    EXPECT_EQ(_a.setGrey(366), Pixel(366));
    EXPECT_EQ(_a.setLimited(true), Pixel(255));
    EXPECT_EQ(_a.setLimited(false), Pixel(255));
}