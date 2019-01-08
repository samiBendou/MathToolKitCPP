//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_NDSET_H
#define MATHTOOLKIT_NDSET_H

#include <set>
#include <NCompact.h>

/**
 * @ingroup NGeometry
 * @{
 */

class NDSet : public NCompact, std::set<vec_t> {
public:
    NDSet();

    explicit NDSet(std::vector<vec_t> &vectors);

    std::string str() const override;

    bool isIn(const vec_t &x) const override;

    bool isEmpty() const override;

    void uni(const NDSet &set);

    void inter(const NDSet &set);

    int card() const override;

    std::vector<vec_t> border() const override;

    std::vector<vec_t > mesh() const;

    std::vector<vec_t > mesh(const vec_t &h) const override;

};

/** @} */

#endif //MATHTOOLKIT_NDSET_H
