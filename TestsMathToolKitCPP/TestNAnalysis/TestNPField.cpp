//
// Created by Sami Dahoux on 12/10/2018.
//

#include <NConstantField.h>
#include <SNewtonianField.h>
#include <NParallelepiped.h>
#include <NOde.h>

#include <gtest/gtest.h>

TEST(NPFieldTest, NConstantField) {
    size_t dim = 3;

    // Parallelepiped construction
    double l = 5.0;
    NParallelepiped para{mat_t::scalar(l, dim), vec_t::zeros(dim)};
    cout << "para : " << para << endl;

    // Field construction
    double dx = 1.0/3.0;
    vec_t h = vec_t::scalar(dx, dim);

    vec_t g = 9.81 * vec_t::cano(dim - 1, dim);

    NConstantField field = NConstantField(h, g);

    vector<vec_t> out = field(para);

    cout << endl;
    for (int k = 0; k < out.size(); ++k) {
        cout << "out[" << k << "] : " << out[k] << endl;
    }
}

TEST(NPFieldTest, SNewtonianField) {
    size_t dim = 3;
    double sun_mass = 1.9891e+30, d_earth_sun = 1.47098074e+11; //earth_spd = 3.0287e+4;

    // Parallelepiped construction
    NParallelepiped para{mat_t::scalar(d_earth_sun, dim), vec_t::zeros(dim)};

    // Field construction
    double dx = 1.0/2.0, G = -6.67408e-11;
    vec_t h = vec_t::scalar(dx, dim);

    std::vector<double> mass{sun_mass};
    std::vector<vec_t> r{vec_t::zeros(3)};

    SNewtonianField field = SNewtonianField(h, mass, r, G);

    vector<vec_t> out = field(para);

    cout << endl;
    for (int k = 0; k < out.size(); ++k) {
        cout << "out[" << k << "] : " << out[k] << endl;
    }
}

TEST(NOde, Euler) {
    size_t dim = 3;

    // Field construction
    double dx = 0.333;
    vec_t h = vec_t::scalar(dx, dim);

    vec_t g = 9.81 * vec_t::cano(dim - 1, dim);

    NConstantField field = NConstantField(h, g);

    std::vector<vec_t> solution = NOde::euler(vec_t::zeros(dim), field);

    cout << endl;
    for (int k = 0; k <solution.size(); ++k) {
        cout << "solution[" << k << "] : " << solution[k] << endl;
    }
}