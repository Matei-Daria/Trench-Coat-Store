#include <cassert>
#include "CartMemoryRepo.h"

CartMemoryRepo::CartMemoryRepo(float total)
{
    this->totalAmount = total;
}

void CartMemoryRepo::addToEnd(const TrenchCoat &tc)
{
    this->cartItems.push_back(tc);
}

void CartMemoryRepo::testCartRepo()
{
    CartMemoryRepo repo;
    repo.testAddToEnd();
    repo.testIncreaseTotalAmount();
}

void CartMemoryRepo::testAddToEnd()
{
    TrenchCoat tc1("XXS", "Beige", "proper-trench.com/xxs-beige-03/", 199.99, 112);
    TrenchCoat tc2("M", "Light Yellow", "proper-trench.com/m-liyel-35/", 199.59, 0);
    this->addToEnd(tc1);
    assert(this->cartItems[0] == tc1);
    assert(this->getSize() == 1);
    this->addToEnd(tc2);
    assert(this->cartItems[1] == tc2);
}

void CartMemoryRepo::testIncreaseTotalAmount()
{
    assert(this->getTotalAmount() == 0);
    this->increaseTotalAmount(339.99);
    assert(this->getTotalAmount() == float(339.99));
    this->increaseTotalAmount(120.00);
    assert(this->getTotalAmount() == float(459.99));
}


