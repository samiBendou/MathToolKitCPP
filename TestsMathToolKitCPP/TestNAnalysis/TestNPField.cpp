//
// Created by Sami Dahoux on 12/10/2018.
//

#include <NConstantField.h>
#include <SNewtonianField.h>
#include <NParallelepiped.h>
#include <NOde.h>

#include <gtest/gtest.h>

TEST(NPFieldTest, NConstantField) {
    ul_t dim = 3;

    // Parallelepiped construction
    double l = 5.0;
    mat_t base = mat_t::scalar(l, dim);
    vec_t pos = vec_t::zeros(dim);
    NParallelepiped para{base, pos};
    cout << "para : " << para << endl;

    // Field construction
    double dx = 0.333;
    vec_t h = vec_t::scalar(dx, dim);

    vec_t g = 9.81 * vec_t::canonical(dim - 1, dim);

    NConstantField field = NConstantField(dim, h, g);

    vector<vec_t> out = field(para);

    for (int k = 0; k < out.size(); ++k) {
        cout << "out[" << k << "] : " << out[k] << endl;
    }
}

TEST(NPFieldTest, SNewtonianField) {
    ul_t dim = 3;
    double sun_mass = 1.9891e+30, earth_sun_distance = 1.47098074e+11; //earth_spd = 3.0287e+4;

    // Parallelepiped construction
    mat_t base = mat_t::scalar(1 * earth_sun_distance, dim);
    vec_t pos = vec_t::zeros(dim);
    NParallelepiped para{base, pos};
    cout << "para : " << para << endl;

    // Field construction
    double dx = earth_sun_distance * 0.333, G = -6.67408e-11;
    vec_t h = vec_t::scalar(dx, dim);

    std::vector<double> mass{sun_mass};
    std::vector<vec_t> r{vec_t::zeros(3)};

    SNewtonianField field = SNewtonianField(dim, h, mass, r, G);

    vector<vec_t> out = field(para);

    for (int k = 0; k < out.size(); ++k) {
        cout << "out[" << k << "] : " << out[k] << endl;
    }
}

TEST(NOde, Euler) {
    ul_t dim = 3;

    // Field construction
    double dx = 0.333;
    vec_t h = vec_t::scalar(dx, dim);

    vec_t g = 9.81 * vec_t::canonical(dim - 1, dim);

    NConstantField field = NConstantField(dim, h, g);

    std::vector<vec_t> solution = NOde::euler(vec_t::zeros(6), field);
    for (int k = 0; k <solution.size(); ++k) {
        cout << "solution[" << k << "] : " << solution[k] << endl;
    }
}