#include <fstream>
#include "CartCSVRepo.h"
#include "../../Utilities/Exceptions.h"

CartCSVRepo::CartCSVRepo(const std::string &file)
{
    this->totalAmount = 0;
    this->filename = file;
}

void CartCSVRepo::writeToCSV()
{
    std::ofstream file(this->filename);

    if (!file.is_open())
        throw FileError("The file cannot be opened.");

    file << "NO,SIZE,COLOR,PHOTO,PRICE\n";
    int pos = 1;

    for (auto item: this->cartItems)
    {
        file << pos << "," << item.getSize() << "," << item.getColor() << "," << item.getPhoto() << ","
             << item.getPrice() << "\n";
        pos++;
    }

    file << "\n,,,TOTAL," << this->getTotalAmount() << "\n";

    file.close();
}

void CartCSVRepo::addToEnd(const TrenchCoat &tc)
{
    this->cartItems.push_back(tc);
    this->writeToCSV();
}
