//
// Created by Sami Dahoux on 06/05/2018.
//

#include <NPField.h>

using namespace std;

template<typename T, typename P>
NPField<T, P>::NPField(NVector<T> h) : h(h){

}

template<typename T, typename P>
NVector<P> NPField<T, P>::operator()(const NVector<T> &u) const {
    return apply(u);
}

template<typename T, typename P>
vector<NVector<P>> NPField<T, P>::operator()(const vector<NVector<T>> &vectors) const {
    return map(vectors);
}

template<typename T, typename P>
vector<NVector<P>> NPField<T, P>::operator()(const NCompact &domain) const {
    return mesh(domain);
}

template<typename T, typename P>
vector<NVector<P>> NPField<T, P>::map(const vector<NVector<T>> &vectors) const {
    vector<NVector<T>> mesh_out(vectors.size());
    for (int k = 0; k < vectors.size(); ++k) {
        mesh_out[k] = apply(vectors[k]);
    }
    return mesh_out;
}

template<typename T, typename P>
vector<NVector<P>> NPField<T, P>::mesh(const NCompact &domain) const {
    return map(domain.mesh(h));
}

template
class NPField<double_t>;



