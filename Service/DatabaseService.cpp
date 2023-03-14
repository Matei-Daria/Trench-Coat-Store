#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include <cstring>
#include <cassert>
#include <utility>
#include <iostream>
#include <algorithm>
#include "DatabaseService.h"
#include "../Repo/DatabaseRepo/DatabaseMemoryRepo.h"

DatabaseService::DatabaseService(DatabaseRepo* r)
{
    this->repo = r;
}

void DatabaseService::addTC(const std::string &size, const std::string &color,
                            const std::string &photo, float price, int quantity)
{
    TrenchCoat tc(size, color, photo, price, quantity);
    Validator::validateAddIdenticalTC(this->repo->getRepo(), tc);
    this->repo->addToEnd(tc);

    this->undoActions.push_back(std::make_shared<UndoAdd>(*this->repo, tc));
    this->redoActions.clear();
}

void DatabaseService::removeTC(int pos)
{
    Validator::validateIndex(pos, 0, this->repo->getSize() - 1);
    Validator::validateDeleteTC(this->repo->operator[](pos));
    TrenchCoat tc = this->getOnPos(pos);
    this->repo->removeFromPos(pos);

    this->undoActions.push_back(std::make_shared<UndoRemove>(*this->repo, tc));
    this->redoActions.clear();
}

void DatabaseService::updateTC(int pos, const std::string &size, const std::string &color,
                               const std::string &photo, std::string price, std::string quantity)
{
    if (price == "-")
        price = "-1";

    if (quantity == "-")
        quantity = "-1";

    TrenchCoat newDetails(size, color, photo, stof(price), stoi(quantity));

    Validator::validateUpdateIdenticalTC(this->repo->getRepo(), newDetails);

    TrenchCoat tc = getOnPos(pos);
    if (newDetails.getSize() == "-")
        newDetails.setSize(tc.getSize());
    if (newDetails.getColor() == "-")
        newDetails.setColor(tc.getColor());
    if (newDetails.getPhoto() == "-")
        newDetails.setPhoto(tc.getPhoto());
    if (newDetails.getPrice() == -1.)
        newDetails.setPrice(tc.getPrice());
    if (newDetails.getQuantity() == -1)
        newDetails.setQuantity(tc.getQuantity());

    this->repo->updateOnPos(pos, newDetails);

    this->undoActions.push_back(std::make_shared<UndoUpdate>(*this->repo, tc, newDetails));
    this->redoActions.clear();
}

std::vector<TrenchCoat> DatabaseService::getAllWithSize(const std::string &size)
{
    if (size.empty() || size == "-")
        return this->repo->getRepo();

    std::vector<TrenchCoat> tcRepo = this->repo->getRepo();
    std::vector<TrenchCoat> temp (tcRepo.size() - 1);

    auto it = std::copy_if(tcRepo.begin(), tcRepo.end(), temp.begin(),
                  [&size](TrenchCoat tc){ return (tc.getSize() == size);});
    temp.resize(std::distance(temp.begin(), it));

    return temp;
}

void DatabaseService::testDatabaseService()
{
    DatabaseMemoryRepo repo;
    repo.generateEntities();
    DatabaseService serv(&repo);
    serv.testAddTC();
    serv.testRemoveTC();
    serv.testUpdateTC();
}

void DatabaseService::testAddTC()
{
    auto size = this->getSize();
    this->addTC("XL", "Grey", "proper-trench.com/xl-grey-36/", 199.59, 20);
    assert(size == this->getSize() - 1);
    assert(this->getOnPos(size).getPhoto() == "proper-trench.com/xl-grey-36/");
}

void DatabaseService::testRemoveTC()
{
    TrenchCoat tc4 = this->getOnPos(4);
    TrenchCoat tc5 = this->getOnPos(5);
    this->removeTC(4);
    assert(!(this->getOnPos(4) == tc4));
    assert(this->getOnPos(4) == tc5);
}

void DatabaseService::testUpdateTC()
{
    TrenchCoat tc = this->getOnPos(3);
    this->updateTC(3, "XL", "-", "proper-trench.com/l-mebr-45/", "-1", "20");
    assert(this->getOnPos(3).getSize() == "XL");
    assert(this->getOnPos(3).getColor() == tc.getColor());
    assert(this->getOnPos(3).getPrice() == tc.getPrice());
    assert(this->getOnPos(3).getPhoto() != tc.getPhoto());
}

void DatabaseService::undo()
{
    if (undoActions.empty())
        throw DatabaseRepoError("There are no more actions that can be undone.");

    std::shared_ptr<UndoAction> lastAction = move(this->undoActions.back());
    lastAction->undo();
    this->undoActions.pop_back();
    this->redoActions.push_back(move(lastAction));
}

void DatabaseService::redo()
{
    if (redoActions.empty())
        throw DatabaseRepoError("There are no more actions that can be redone.");

    std::shared_ptr<UndoAction> lastAction = move(this->redoActions.back());
    lastAction->redo();
    this->redoActions.pop_back();
    this->undoActions.push_back(move(lastAction));
}



