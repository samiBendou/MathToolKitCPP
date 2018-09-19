//
// Created by Sami Dahoux on 07/05/2018.
//

#ifndef MATHTOOLKIT_NDSET_H
#define MATHTOOLKIT_NDSET_H


#include "NCompact.h"

class NDSet : public NCompact {
public:
    NDSet();

    explicit  NDSet(std::vector<ENVector>& vectors);

    std::string str() const override;

    bool isIn(const ENVector& x) const override;

    bool isEmpty() const override;

    void uni(const NSet* set) override;

    void inter(const NSet* set) override;

    int card() const override;

    NCompact* border() const override;

    std::vector<ENVector> mesh() const;

    std::vector<ENVector> mesh(const ENVector& h) const  override;

    void push(const ENVector& x);

    ENVector& pop();

protected:
    std::vector <ENVector> _data;
};


#endif //MATHTOOLKIT_NDSET_H
