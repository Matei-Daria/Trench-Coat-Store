#pragma once

#include <vector>
#include "../../Entities/TrenchCoat.h"

class DatabaseRepo
{
public:
    virtual void addToEnd(const TrenchCoat& tc) {};
    virtual void removeFromPos(int pos) {};
    virtual void updateOnPos(int pos, const TrenchCoat& newDetails) {};
    virtual int getSize() = 0;
    virtual TrenchCoat& operator[](int pos) = 0;
    virtual void decreaseQuantity(int pos) {};
    virtual int getPos(TrenchCoat& tc) = 0;
    virtual std::vector<TrenchCoat> getRepo() = 0;
    virtual ~DatabaseRepo() = default;
};