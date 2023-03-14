#include <cassert>
#include "CartService.h"
#include "../Utilities/Validators.h"
#include <windows.h>
#include <algorithm>

CartService::CartService(CartRepo *r)
{
    this->repo = r;
}

void CartService::addToEnd(const TrenchCoat &tc)
{
    Validator::validateBuyTC(tc);

    this->increaseTotalAmount(tc.getPrice());
    this->repo->addToEnd(tc);
}

void CartService::testCartService()
{
    CartMemoryRepo repo;
    CartService serv(&repo);
    serv.testAddToEnd();
    serv.testGetOnPos();
}

void CartService::testAddToEnd()
{
    TrenchCoat tc1("XXS", "Beige", "proper-trench.com/xxs-beige-03/", 199.99, 112);
    TrenchCoat tc2("M", "Light Yellow", "proper-trench.com/m-liyel-35/", 199.59, 0);
    TrenchCoat tc3("S", "Black", "proper-trench.com/s-black-67/", 499.99, 23);
    this->addToEnd(tc1);
    assert(this->getTotalAmount() == float(199.99));
    assert(this->getSize() == 1);
    try
    {
        this->addToEnd(tc2);
        assert(false);
    }
    catch (CartRepoError &cre)
    {
        assert(true);
    }
    assert(this->getSize() == 1);
    assert(this->getTotalAmount() == float(199.99));
    this->addToEnd(tc3);
    assert(this->getSize() == 2);
    assert(this->getTotalAmount() == float(699.98));
}

void CartService::testGetOnPos()
{
    TrenchCoat tc1("XXS", "Beige", "proper-trench.com/xxs-beige-03/", 199.99, 112);
    TrenchCoat tc2("M", "Light Yellow", "proper-trench.com/m-liyel-35/", 199.59, 0);
    TrenchCoat tc3("S", "Black", "proper-trench.com/s-black-67/", 499.99, 23);
    assert(this->getOnPos(0) == tc1);
    assert(this->getOnPos(1) == tc3);
}

void CartService::executeOpen(const std::string& exeString)
{
    ShellExecute(nullptr, reinterpret_cast<LPCWSTR>("open"), reinterpret_cast<LPCWSTR>(exeString.c_str()), nullptr, nullptr, SW_SHOWNORMAL);
}

void CartService::openFile()
{
    CartRepo* cartRepo = this->repo;
    std::string filenamePath = cartRepo->getFilename();
    std::replace(filenamePath.begin(), filenamePath.end(), '/', '\\');

    CartService::executeOpen(filenamePath);
}


