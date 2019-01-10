//
// Created by Sami Dahoux on 14/10/2018.
//

#include <sstream>

#include <NParallelepiped.h>

#include <gtest/gtest.h>

#define DIM_TEST 3

using namespace std;

class NParallelepipedTest : public ::testing::Test {

protected:
    void SetUp() override {
    }

    NParallelepiped _para1{mat_t::eye(DIM_TEST), vec_t::zeros(DIM_TEST)};
    // NParallelepiped _para2{2 * mat_t::eye(DIM_TEST), vec_t::zeros(DIM_TEST)};
    // NParallelepiped _para3{mat_t::eye(DIM_TEST), vec_t::cano(0, DIM_TEST)};
};

TEST_F(NParallelepipedTest, IsIn) {
    ASSERT_TRUE(_para1.isIn(vec_t::zeros(DIM_TEST)));
    ASSERT_TRUE(_para1.isIn(vec_t::scalar(1, DIM_TEST)));
    ASSERT_TRUE(_para1.isIn(vec_t::scalar(0.5, DIM_TEST)));

    ASSERT_FALSE(_para1.isIn(vec_t::scalar(1.1, DIM_TEST)));
    ASSERT_FALSE(_para1.isIn(vec_t::scalar(-1, DIM_TEST)));
    ASSERT_FALSE(_para1.isIn(vec_t::scalar(-0.5, DIM_TEST)));
}

TEST_F(NParallelepipedTest, Mesh) {
    double_t dx = 0.33;

    vector<vec_t> mesh_para1 = _para1.mesh(vec_t::scalar(dx, DIM_TEST));
    cout << endl;
    for (int k = 0; k < mesh_para1.size(); ++k) {
        cout << mesh_para1[k] << endl;
    }
}

TEST_F(NParallelepipedTest, Segments) {
    vector<NSegment> seg_para1 = _para1.segments();

    cout << endl;
    for (int k = 0; k < seg_para1.size(); ++k) {
        cout << seg_para1[k] << endl;
    }
}

TEST_F(NParallelepipedTest, Vol) {
    ASSERT_EQ(_para1.vol(), 1);
}