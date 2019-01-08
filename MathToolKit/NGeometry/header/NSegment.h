//
// Created by Sami Dahoux on 06/05/2018.
//

#ifndef MATHTOOLKIT_SEGMENT_H
#define MATHTOOLKIT_SEGMENT_H


#include <NVector.h>
#include <NCompact.h>

/**
 * @ingroup NGeometry
 * @{
 */

class NSegment : public NCompact {
public:
    explicit NSegment(const vec_t &a = vec_t::zeros(0), const vec_t &b = vec_t::zeros(0));

    std::string str() const override;

    vec_t a() const;

    vec_t b() const;

    void setA(const vec_t &a);

    void setB(const vec_t &b);

    std::vector<vec_t> border() const override;

    std::vector<vec_t > mesh(double h) const;

    std::vector<vec_t > mesh(const vec_t &h) const override;

    bool isIn(const vec_t &x) const override;

    bool isEmpty() const override;

protected:
    vec_t _a;
    vec_t _b;



    int card() const override;
};

/** @} */

#endif //MATHTOOLKIT_SEGMENT_H
