#pragma once

#include <vector>
#include "../../Entities/TrenchCoat.h"

class CartRepo
{
public:
    virtual void addToEnd(const TrenchCoat& tc) {};
    virtual float getTotalAmount() = 0;
    virtual int getSize() = 0;
    virtual TrenchCoat& operator[](int pos) = 0;
    virtual void increaseTotalAmount(float amount) {};
    virtual std::vector<TrenchCoat> getRepo() = 0;
    virtual std::string getFilename() = 0;
    virtual ~CartRepo() = default;
};