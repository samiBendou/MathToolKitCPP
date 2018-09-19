//
// Created by Sami Dahoux on 07/05/2018.
//

#include "../header/NDSet.h"


NDSet::NDSet() : NCompact(0), _data()
{

}

NDSet::NDSet(std::vector<ENVector>& vectors) : NCompact(vectors[0].dim()), _data(vectors)
{

}

std::string NDSet::str() const {
    std::string str = "{ ";
    for (int k = 0; k < card() - 1; ++k) {
        str += _data[k].str() + ", ";
    }
    str += _data[card() - 1].str() + " }";
    return str;
}

bool NDSet::isIn(const ENVector &x) const {
    for (int k = 0; k < card(); ++k) {
        if(x == _data[k]) {
            return true;
        }
    }
    return false;
}

bool NDSet::isEmpty() const {
    return card() == 0;
}

void NDSet::uni(const NSet* set) {
    std::vector<ENVector> data = ((NDSet*) set)->_data;
    for(int k = 0; k < data.size(); ++k) {
        if(!isIn(data[k]))
            _data.push_back(data[k]);
    }
}

void NDSet::inter(const NSet* set) {
    std::vector<ENVector> data = ((NDSet*) set)->_data;
    std::vector<ENVector> dataInter;
    for(int k = 0; k < data.size(); ++k) {
        for (int l = 0; l < _data.size(); ++l) {
            if(isIn(data[k]) && set->isIn(_data[l]))
                dataInter.push_back(data[k]);
        }
    }
    _data = dataInter;
}

int NDSet::card() const {
    return (int) _data.size();
}

NCompact *NDSet::border() const {
    NDSet* newThis{new NDSet(*this)};
    return newThis;
}

std::vector<ENVector> NDSet::mesh() const {
    return std::vector<ENVector>(_data);
}

std::vector<ENVector> NDSet::mesh(const ENVector &h) const {
    return NDSet::mesh();
}

void NDSet::push(const ENVector &x) {
    _data.push_back(x);
}

ENVector& NDSet::pop() {
    ENVector ret = ENVector(_data[card() - 1]);
    _data.pop_back();
    return ret;
}






