#pragma once

#include "../Service/DatabaseService.h"
#include "../Service/CartService.h"
#include "../Utilities/Validators.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UI
{
private:
    DatabaseService databaseService;
    CartService cartService;

    void printAllTC();
    void adminPrintOneTC(TrenchCoat &tc);
    void userPrintOneTC(TrenchCoat &tc);
    void uiAddTC();
    bool printSoldOut();
    bool uiRemoveTC();
    void uiUpdateTC();
    void userViewAll();
    void printCart();
    void uiAddToCart(TrenchCoat& tc);
    void viewCartOpenFile();

    //print/run menus
    void printMainMenu();
    void printAdminMenu();
    bool runAdmin(int option);
    void printUserMenu();
    bool runUser(int option);

public:
    explicit UI(DatabaseService databaseServ, CartService cartServ);

    void start();
};