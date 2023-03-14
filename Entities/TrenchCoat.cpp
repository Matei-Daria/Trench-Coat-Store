#include "TrenchCoat.h"
#include "../Utilities/Validators.h"
#include "../Utilities/Exceptions.h"
#include "../Utilities/Utils.h"
#include <utility>
#include <cassert>

TrenchCoat::TrenchCoat(std::string size, std::string color, std::string photo, float price,
                       int quantity) :
        size(std::move(size)), color(std::move(color)), photo(std::move(photo)), price(price), quantity(quantity)
{}

TrenchCoat::TrenchCoat(const TrenchCoat &trenchCoat)
{
    this->size = trenchCoat.size;
    this->color = trenchCoat.color;
    this->photo = trenchCoat.photo;
    this->price = trenchCoat.price;
    this->quantity = trenchCoat.quantity;
}

TrenchCoat::TrenchCoat() : size(), color(), photo(), price(0), quantity(0)
{}

bool operator==(const TrenchCoat &tc1, const TrenchCoat &tc2)
{
    return (tc1.size == tc2.size and
            tc1.color == tc2.color and
            tc1.photo == tc2.photo);
}

void TrenchCoat::testTrenchCoat()
{
    TrenchCoat tc1("XL", "Light Brown", "proper-trench.com/xl-libr-43/", 219.59, 244);
    TrenchCoat tc2("XL", "Light Brown", "proper-trench.com/xl-libr-43/", 200.59, 12);
    TrenchCoat tc3("XL", "Light Brown", "proper-trench.com/xxs-beige-03/", 199.99, 112);

    assert(tc1 == tc2);
    assert(!(tc1 == tc3));
    assert(tc1.getSize() == "XL");
    assert(tc3.getQuantity() == 112);

    tc3.setPhoto("proper-trench.com/xl-libr-43/");
    assert(tc1 == tc3);
    tc2.setSize("M");
    assert(!(tc1 == tc2));
}

TrenchCoat::~TrenchCoat()
= default;

std::istream &operator>>(std::istream &is, TrenchCoat &tc)
{
    if (is.eof())
    {
        is.setstate(std::ios_base::failbit);
    } else
    {
        std::string line;
        std::getline(is, line, '\n');
        std::vector<std::string> elems = tokenize(line, ',');
        if (line.empty())
            return is;
        if (elems.size() != 5)
        {
            throw FileError("Cannot read a valid entity from a line in the text file.");
        }
        tc.size = elems[0];
        tc.color = elems[1];
        tc.photo = elems[2];
        std::string price, quantity;
        price = elems[3];
        quantity = elems[4];
        Validator::validateNewTrenchCoat(price, quantity);
        tc.price = stof(price);
        tc.quantity = stoi(quantity);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, TrenchCoat &tc)
{
    os << tc.size << "," << tc.color << "," << tc.photo << "," << tc.price << "," << tc.quantity << "\n";
    return os;
}

std::string TrenchCoat::to_string() const
{
    return this->size + ",  " + this->color + ",  " + this->photo;
}


