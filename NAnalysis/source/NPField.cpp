//
// Created by Sami Dahoux on 06/05/2018.
//

#include <NPField.h>

using namespace std;

template<typename T>
NPField<T>::NPField(ul_t dim_in, ul_t dim_out, NVector<T> h) : _dim_in(dim_in), _dim_out(dim_out), h(h){

}

template<typename T>
NVector<T> NPField<T>::operator()(const NVector<T> &u) const {
    return g(u);
}

template<typename T>
vector<NVector<T>> NPField<T>::operator()(const vector<NVector<T>> &vectors) const {
    return map(vectors);
}

template<typename T>
vector<NVector<T>> NPField<T>::operator()(const NCompact &domain) const {
    return mesh(domain);
}

template<typename T>
vector<NVector<T>> NPField<T>::map(const vector<NVector<T>> &vectors) const {
    vector<NVector<T>> mesh_out(vectors.size());
    for (int k = 0; k < vectors.size(); ++k) {
        mesh_out[k] = g(vectors[k]);
    }
    return mesh_out;
}

template<typename T>
vector<NVector<T>> NPField<T>::mesh(const NCompact &domain) const {
    return map(domain.mesh(h));
}

template
class NPField<double>;



