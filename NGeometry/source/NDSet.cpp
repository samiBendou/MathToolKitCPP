//
// Created by Sami Dahoux on 07/05/2018.
//

#include "../header/NDSet.h"


NDSet::NDSet() : NCompact(0), std::set<vec_t>() {

}

NDSet::NDSet(std::vector<vec_t> &vectors) : NCompact(vectors[0].dim()), std::set<vec_t>() {
}

std::string NDSet::str() const {
    std::stringstream stream;
    iterator it;
    stream << "{ ";
    for (it = this->begin(); it != this->end(); ++it) {
        stream << (*it).str() << ", ";
    }
    stream << (*it).str() << " }";
    return stream.str();
}

bool NDSet::isIn(const vec_t &x) const {
    return std::find(this->begin(), this->end(), x) != this->end();
}

bool NDSet::isEmpty() const {
    return card() == 0;
}

void NDSet::uni(const NDSet &set) {
    std::vector<vec_t> data{mesh()}, data_set{set.mesh()}, res;
    std::set_union(data.begin(), data.end(), data_set.begin(), data_set.end(), res.begin());
    *this = NDSet(res);
}

void NDSet::inter(const NDSet &set) {
    std::vector<vec_t> data{mesh()}, data_set{set.mesh()}, res;
    std::set_intersection(data.begin(), data.end(), data_set.begin(), data_set.end(), res.begin());
    *this = NDSet(res);
}

int NDSet::card() const {
    return this->size();
}

std::vector<vec_t> NDSet::border() const {
    //TODO : Implement border calculation from triangulation of points contained in underlying set
    return mesh();
}

std::vector<vec_t > NDSet::mesh() const {
    return std::vector<vec_t>(this->begin(), this->end());
}

std::vector<vec_t > NDSet::mesh(const vec_t &h) const {
    return NDSet::mesh();
}






