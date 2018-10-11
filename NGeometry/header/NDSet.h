//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_NDSET_H
#define MATHTOOLKIT_NDSET_H

#include "NCompact.h"

class NDSet : public NCompact {
public:
    NDSet();

    explicit NDSet(std::vector<NVector<double>> &vectors);

    std::string str() const override;

    bool isIn(const NVector<double> &x) const override;

    bool isEmpty() const override;

    void uni(const NSet *set) override;

    void inter(const NSet *set) override;

    int card() const override;

    NCompact *border() const override;

    std::vector<NVector<double> > mesh() const;

    std::vector<NVector<double> > mesh(const NVector<double> &h) const override;

    void push(const NVector<double> &x);

    NVector<double> pop();

protected:
    std::vector<NVector<double>> _data;
};


#endif //MATHTOOLKIT_NDSET_H
