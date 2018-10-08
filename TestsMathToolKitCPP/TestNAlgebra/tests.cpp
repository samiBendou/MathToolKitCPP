//
// Created by Sami Dahoux on 09/05/2018.
//
#include "tests.h"

using namespace std;

bool testNConstantField() {
    cout << endl<< "**** CONSTANT FIELD ****" << endl << endl;
    NMatrix base = NMatrix::scalar(5, 3);
    vector<NVector> baseCols = base.cols();
    NVector pos = NVector::zeros(3);
    NVector dx = NVector::scalar(1.0 / 3.0, 3);
    NParallelepiped para{base, pos};
    cout << "para : " << para << endl;
    NConstantField field{&para, Vector3(0, 0, 9.81)};
    field.h = dx;
    cout << "field.meshMatrix() : " << field.meshMatrix() << endl;

    return false;
}

bool testSNewtonianField() {
    cout << endl<< "**** NEWTONIAN FIELD ****" << endl << endl;
    const double sunMass = 1.9891e+30, earthSunDistance = 1.47098074e+11; //earthSpd = 3.0287e+4;

    NMatrix base = NMatrix::scalar(1 * earthSunDistance, 3);
    vector<NVector> baseCols = base.cols();
    NVector pos = NVector::zeros(3);
    NVector dx = NVector::scalar(1.0 / 3, 3);
    NParallelepiped para{base, pos};

    cout << "para : " << para << endl;

    cout << "Earth-Sun system simulation" << endl;

    std::vector<double> mass{sunMass};
    std::vector<Vector3> r{Vector3(0, 0, 0), Vector3(earthSunDistance, 0, 0)};
    SNewtonianField field{&para, -6.67408e-11, mass, r};
    field.h = dx;
    cout << "field.meshMatrix() : " << field.meshMatrix() << endl;
    cout << "field(earth) : " << field(Vector3(earthSunDistance, 0, 0)) << endl;
    return false;
}

bool testODESolver() {

    cout << endl<< "**** ODE SOLVER ****" << endl << endl;
    NMatrix base = NMatrix::scalar(5, 3);
    vector<NVector> baseCols = base.cols();
    NVector pos = NVector::zeros(3);
    NVector dx = NVector::scalar(1.0 / 3.0, 3);
    NParallelepiped para{base, pos};
    cout << "para : " << para << endl;
    NConstantField f{&para, Vector3(0, 0, 9.81)};
    f.h = dx;

    std::vector<NVector> solution = NOde::euler(NVector::zeros(6), f);
    for (int k = 0; k <solution.size(); ++k) {
        cout << "solution " << k << " : " << solution[k] << endl;
    }
    NPMatrix matSol{solution};
    cout << matSol << endl;

    return false;
}





