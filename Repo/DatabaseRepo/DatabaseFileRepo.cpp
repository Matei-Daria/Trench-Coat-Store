#include <fstream>
#include "DatabaseFileRepo.h"
#include "../../Utilities/Exceptions.h"
#include <iostream>

DatabaseFileRepo::DatabaseFileRepo(const std::string &filename)
{
    this->filename = filename;
    this->readFromFile();
}

void DatabaseFileRepo::readFromFile()
{
    std::ifstream file(this->filename);

    if (!file.is_open())
        throw FileError("The file cannot be opened.");

    TrenchCoat tc;
    while (file >> tc)
    {
        this->trenchCoats.push_back(tc);
    }

    file.close();
}

void DatabaseFileRepo::writeToFile()
{
    std::ofstream file(this->filename);

    if (!file.is_open())
        throw FileError("The file cannot be opened.");

    for (auto tc : this->trenchCoats)
        file << tc;

    file.close();
}

void DatabaseFileRepo::addToEnd(const TrenchCoat &tc)
{
    this->trenchCoats.push_back(tc);
    this->writeToFile();
}

void DatabaseFileRepo::removeFromPos(int pos)
{
    this->trenchCoats.erase(this->trenchCoats.begin() + pos);
    this->writeToFile();
}

void DatabaseFileRepo::updateOnPos(int pos, const TrenchCoat& newDetails)
{
    this->trenchCoats[pos] = newDetails;
    this->writeToFile();
}

int DatabaseFileRepo::getPos(TrenchCoat &tc)
{
    std::vector<TrenchCoat>::iterator pos;
    pos = std::find(this->trenchCoats.begin(), this->trenchCoats.end(), tc);
    if (pos == this->trenchCoats.end())
        return -1;
    else
        return int(std::distance(this->trenchCoats.begin(), pos));
}
