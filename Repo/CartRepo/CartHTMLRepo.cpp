#include "CartHTMLRepo.h"
#include <fstream>

CartHTMLRepo::CartHTMLRepo(const std::string &file)
{
    this->totalAmount = 0;
    this->filename = file;
}

void CartHTMLRepo::addToEnd(const TrenchCoat &tc)
{
    this->cartItems.push_back(tc);
    this->writeToHTML();
}

void CartHTMLRepo::writeToHTML()
{
    std::ofstream file(this->filename);

    file << "<!DOCTYPE html> <html> <head> <title> Shopping cart </title> </head>";
    file << "<body> <table>";
    file << "<tr> <td>NO</td> <td>SIZE</td> <td>COLOR</td> <td>PHOTO</td> <td>PRICE</td> </tr>";

    int pos = 1;

    for (TrenchCoat item: this->cartItems)
    {
        file << "<tr>";
        file << "<td>" << pos << "</td>";
        file << "<td>" << item.getSize() << "</td>";
        file << "<td>" << item.getColor() << "</td>";
        file << "<td><a href=\"" << item.getPhoto() << "\">Link</a></td>";
        file << "<td>" << item.getPrice() << "</td>";
        file << "</tr>";
        pos++;
    }

    file << "<tr> <td> </td> <td> </td> <td> </td> <td> </td> <td> </td> </tr> ";
    file << "<tr> <td> </td> <td> </td> <td> </td> <td> TOTAL </td> <td>" << this->getTotalAmount()
         << " </td> </tr> ";

    file << "</table> </body> </html>";

    file.close();
}
