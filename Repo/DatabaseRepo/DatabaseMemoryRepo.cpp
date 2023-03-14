#include <cassert>
#include "DatabaseMemoryRepo.h"

void DatabaseMemoryRepo::generateEntities()
{
    TrenchCoat tc1("XL", "Light Yellow", "https://tinyurl.com/proper-trench-11", 299.99, 202);
    addToEnd(tc1);
    TrenchCoat tc2("L", "Medium Brown", "https://tinyurl.com/proper-trench-22", 259.99, 20);
    addToEnd(tc2);
    TrenchCoat tc3("XXS", "Beige", "https://tinyurl.com/proper-trench-39", 199.99, 112);
    addToEnd(tc3);
    TrenchCoat tc4("XL", "Light Brown", "https://tinyurl.com/proper-trench-45", 219.59, 244);
    addToEnd(tc4);
    TrenchCoat tc5("M", "Light Yellow", "https://tinyurl.com/proper-trench-43", 199.59, 0);
    addToEnd(tc5);
    TrenchCoat tc6("S", "Black", "https://tinyurl.com/proper-trench-67", 599.99, 10);
    addToEnd(tc6);
    TrenchCoat tc7("XXXL", "Dark Brown", "https://tinyurl.com/proper-trench-88", 349.49, 206);
    addToEnd(tc7);
    TrenchCoat tc8("M", "Light Blue", "https://tinyurl.com/proper-trench-90", 109.99, 256);
    addToEnd(tc8);
    TrenchCoat tc9("M", "Grey", "https://tinyurl.com/proper-trench-55", 199.09, 0);
    addToEnd(tc9);
    TrenchCoat tc10("S", "Black", "https://tinyurl.com/proper-trench-80", 499.99, 23);
    addToEnd(tc10);
}

void DatabaseMemoryRepo::addToEnd(const TrenchCoat &tc)
{
    this->trenchCoats.push_back(tc);
}

void DatabaseMemoryRepo::removeFromPos(int pos)
{
    this->trenchCoats.erase(this->trenchCoats.begin() + pos);
}

void DatabaseMemoryRepo::updateOnPos(int pos, const TrenchCoat& newDetails)
{
    this->trenchCoats[pos] = newDetails;
}

int DatabaseMemoryRepo::getPos(TrenchCoat &tc)
{
    std::vector<TrenchCoat>::iterator pos;
    pos = std::find(this->trenchCoats.begin(), this->trenchCoats.end(), tc);
    if (pos == this->trenchCoats.end())
        return -1;
    else
        return int(std::distance(this->trenchCoats.begin(), pos));
}

void DatabaseMemoryRepo::testDatabaseMemoryRepo()
{
    DatabaseMemoryRepo repo;
    repo.generateEntities();

    repo.testAddToEnd();
    repo.testRemoveFromPos();
    repo.testUpdateOnPos();
}

void DatabaseMemoryRepo::testAddToEnd()
{
    auto size = getSize();
    TrenchCoat tc1("L", "Black", "proper-trench.com/l-black-27/", 399.99, 26);
    this->addToEnd(tc1);
    assert(this->trenchCoats[this->getSize() - 1] == tc1);
    assert(this->getSize() == size + 1);
    TrenchCoat tc2("XS", "Beige", "proper-trench.com/xs-beige-13/", 299.99, 112);
    this->addToEnd(tc2);
    assert(this->getSize() == size + 2);
}

void DatabaseMemoryRepo::testRemoveFromPos()
{
    auto size = getSize();
    TrenchCoat tcOn3 = this->trenchCoats[3];
    assert(tcOn3 == this->trenchCoats[3]);
    this->removeFromPos(3);
    assert(!(tcOn3 == this->trenchCoats[3]));
    assert(getSize() == size - 1);
    this->removeFromPos(int(this->getSize() - 1));
}

void DatabaseMemoryRepo::testUpdateOnPos()
{
    assert(!(this->trenchCoats[1] == this->trenchCoats[2]));
    this->updateOnPos(1, this->trenchCoats[2]);
    assert(this->trenchCoats[1] == this->trenchCoats[2]);
    this->updateOnPos(2, this->trenchCoats[7]);
    assert(!(this->trenchCoats[1] == this->trenchCoats[2]));
}
