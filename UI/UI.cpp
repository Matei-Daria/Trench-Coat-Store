#pragma clang diagnostic push
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include "UI.h"
#include <string>
#include <iostream>
#include <utility>
#include "libfort/fort.hpp"
#include "../Utilities/Utils.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31mERROR: "
#define MAGENTA "\033[35m"
#define GREEN   "\033[32m"

UI::UI(DatabaseService databaseServ, CartService cartServ) : databaseService(std::move(databaseServ)),
                                                             cartService(std::move(cartServ))
{}

void UI::printAllTC()
{
    cout << "\n";
    fort::char_table table;
    table.set_border_style(FT_BASIC_STYLE);
    table << fort::header << "NO." << "Size" << "Color" << "Photo" << "Price" << "Quantity" << fort::endr;

    std::vector<TrenchCoat> tcRepo = this->databaseService.getRepoVector();
    int pos = 1;

    for (TrenchCoat tc: tcRepo)
    {
        table << pos++ << tc.getSize() << tc.getColor() << tc.getPhoto() << tc.getPrice() << tc.getQuantity()
              << fort::endr;
    }
    cout << table.to_string();
}

void UI::uiAddTC()
{
    string size, color, photo, price, quantity;

    cout << "\nEnter the details of the trench coat.\n";
    cout << "Size: ";
    getline(cin, size);

    cout << "Color: ";
    getline(cin, color);

    cout << "Photo link: ";
    getline(cin, photo);

    cout << "Price: ";
    getline(cin, price);

    cout << "Quantity: ";
    getline(cin, quantity);

    Validator::validateNewTrenchCoat(price, quantity);

    this->databaseService.addTC(size, color, photo, stof(price), stoi(quantity));
}

bool UI::printSoldOut()
{
    cout << "\nThe only coats that can be deleted are ones that are sold out.\n";
    bool found = false;
    fort::char_table table;
    table.set_border_style(FT_BASIC_STYLE);
    table << fort::header << "NO." << "Size" << "Color" << "Photo" << "Price" << "Quantity" << fort::endr;

    std::vector<TrenchCoat> tcRepo = this->databaseService.getRepoVector();
    int pos = 1;

    for (TrenchCoat tc: tcRepo)
    {
        if (tc.getQuantity() == 0)
        {
            table << pos << tc.getSize() << tc.getColor() << tc.getPhoto() << tc.getPrice() << tc.getQuantity()
                  << fort::endr;
            found = true;
        }
        pos++;
    }

    if (found)
        cout << "The coats that can be deleted are:\n" << table.to_string();
    else
        cout << "There are no coats that are sold out.\n";

    return found;
}

bool UI::uiRemoveTC()
{
    if (!this->printSoldOut())
        return false;

    cout << "Enter the index of the coat to delete: ";

    string string_pos;
    getline(cin, string_pos);
    Validator::validateInteger(string_pos);
    int pos = stoi(string_pos);

    this->databaseService.removeTC(pos - 1);

    return true;
}

void UI::uiUpdateTC()
{
    cout << "\nEnter the index of the trench coat to update: ";
    string pos;
    getline(cin, pos);
    Validator::validateInteger(pos);

    int integer_pos = stoi(pos);
    integer_pos--;
    Validator::validateIndex(integer_pos, 0, this->databaseService.getSize() - 1);
    cout << "\nThe current details of this product are:";
    TrenchCoat tc = this->databaseService.getOnPos(integer_pos);
    adminPrintOneTC(tc);

    cout << "\nEnter the new details. Enter - to leave unchanged.\n";

    string size, color, photo, price, quantity;

    cout << "Size: ";
    getline(cin, size);

    cout << "Color: ";
    getline(cin, color);

    cout << "Photo link: ";
    getline(cin, photo);

    cout << "Price: ";
    getline(cin, price);

    cout << "Quantity: ";
    getline(cin, quantity);

    Validator::validateNewTrenchCoat(price, quantity);

    this->databaseService.updateTC(integer_pos, size, color, photo, price, quantity);
}

void UI::adminPrintOneTC(TrenchCoat &tc)
{
    cout << "\n";
    fort::char_table table;
    table.set_border_style(FT_BASIC_STYLE);
    table << fort::header << "Size" << "Color" << "Photo" << "Price" << "Quantity" << fort::endr;
    table << tc.getSize() << tc.getColor() << tc.getPhoto() << tc.getPrice() << tc.getQuantity() << fort::endr;
    cout << table.to_string();
}

void UI::userPrintOneTC(TrenchCoat &tc)
{
    cout << "\n";
    fort::char_table table;
    table.set_border_style(FT_BASIC_STYLE);
    table << "Size" << tc.getSize() << fort::endr;
    table << "Color" << tc.getColor() << fort::endr;
    table << "Photo" << tc.getPhoto() << fort::endr;
    table << "Price" << tc.getPrice() << fort::endr;
    table << "Quantity" << tc.getQuantity() << fort::endr;
    cout << table.to_string();
}

void UI::userViewAll()
{
    cout << "\nEnter your size or enter - if you want to see all sizes:";
    string size;
    getline(cin, size);

    auto givenSizeTC = this->databaseService.getAllWithSize(size);

    if (givenSizeTC.empty())
    {
        cout << "\nThere are no trench coats with the given size.\n";
        return;
    }

    int i = 0;
    bool goToNext = true;
    TrenchCoat tc = givenSizeTC[0];
    userPrintOneTC(tc);
    while (goToNext)
    {
        cout << "\nDo you want to buy? [yes/no]\n";
        cout << "Do you want to see the photo? [photo]\n";
        cout << "Do you want to stop viewing? [exit]\n>";
        try
        {
            string response;
            getline(cin, response);

            Validator::validateUserResponse(response);

            if (response == "yes")
            {
                this->uiAddToCart(tc);
                givenSizeTC[i].decreaseQuantity();
            }

            if (response == "exit")
            {
                goToNext = false;
            }
            else if (response == "photo")
            {
                cout << "\nOpening url...\n";
                CartService::executeOpen(tc.getPhoto());
            }
            else
            {
                if (i == givenSizeTC.size() - 1)
                    i = 0;
                else
                    i++;
                tc = givenSizeTC[i];
                userPrintOneTC(tc);
            }
        }
        catch (CartRepoError &cre)
        {
            cout << endl << RED << cre.what() << " Enter another command." << RESET << endl;
        }
        catch (ValueError &ve)
        {
            cout << endl << RED << ve.what() << " Enter another command." << RESET << endl;
        }
    }

}

void UI::uiAddToCart(TrenchCoat &tc)
{
    this->cartService.addToEnd(tc);
    cout << GREEN << "\nThe item has been successfully added to your cart.\n" << RESET;
    cout << "Your current shopping cart total amount is " << this->cartService.getTotalAmount()
         << " RON.\n";
    int databasePos = this->databaseService.getPos(tc);
    this->databaseService.decreaseQuantity(databasePos);
}

void UI::printCart()
{
    if (this->cartService.getSize() == 0)
    {
        cout << "\nThere are no items in the shopping cart.\n";
        return;
    }

    cout << "\n";
    fort::char_table table;
    table.set_border_style(FT_BASIC_STYLE);
    table << fort::header << "NO" << "Size" << "Color" << "Photo" << "Price" << fort::endr;

    std::vector<TrenchCoat> repoCart = this->cartService.getRepoVector();
    int pos = 1;

    for (TrenchCoat tc: repoCart)
    {
        table << pos++ << tc.getSize() << tc.getColor() << tc.getPhoto() << tc.getPrice() << fort::endr;
    }
    cout << table.to_string();
    cout << "Total amount: " << MAGENTA << this->cartService.getTotalAmount() << " RON.\n" << RESET;
}

void UI::viewCartOpenFile()
{
    cout << "\nOpening file...\n";
    this->cartService.openFile();
}

void UI::printMainMenu()
{
    cout << "\n";
    cout << "   ---MAIN MENU----------\n";
    cout << "   1. Administrator mode\n";
    cout << "   2. User mode\n";
    cout << "   3. Exit the application\n";
    cout << "   ----------------------\n";
    cout << "   Enter an option: ";
}

void UI::printAdminMenu()
{
    cout << "\n";
    cout << "   ---ADMIN MENU --------------\n";
    cout << "   1. View all trench coats\n";
    cout << "   2. Add a trench coat\n";
    cout << "   3. Remove a trench coat\n";
    cout << "   4. Update a trench coat\n";
    cout << "   5. Return to the main menu\n";
    cout << "   ----------------------------\n";
    cout << "   Enter an option: ";
}

bool UI::runAdmin(int option)
{
    switch (option)
    {
        case 1:
        {
            printAllTC();

            return true;
        }
        case 2:
        {
            uiAddTC();
            cout << GREEN << "\nThe trench coat has been successfully added.\n" << RESET;

            return true;
        }
        case 3:
        {
            bool result = uiRemoveTC();
            if (result)
                cout << GREEN << "\nThe trench coat has been successfully deleted.\n" << RESET;
            else
                cout << "\nThere are no trench coats that are sold out.\n";

            return true;
        }
        case 4:
        {
            uiUpdateTC();
            cout << GREEN << "\nThe trench coat has been successfully updated.\n" << RESET;

            return true;
        }
        case 5:
        {
            return false;
        }
    }
    return false;
}

void UI::printUserMenu()
{
    cout << "\n";
    cout << "   ---USER MENU----------------\n";
    cout << "   1. View and buy trench coats\n";
    cout << "   2. View shopping cart\n";
    cout << "   3. View shopping cart in\n"
            "      the chosen format\n";
    cout << "   4. Return to the main menu\n";
    cout << "   ----------------------------\n";
    cout << "   Enter an option: ";
}

bool UI::runUser(int option)
{
    switch (option)
    {
        case 1:
        {
            this->userViewAll();

            return true;
        }
        case 2:
        {
            this->printCart();

            return true;
        }
        case 3:
        {
            viewCartOpenFile();

            return true;
        }
        case 4:
        {
            return false;
        }
    }
    return false;
}

void UI::start()
{
    cout << MAGENTA << "\n   Welcome to the Proper Trench Coats Store!\n" << RESET;
    bool run_main = true;
    while (run_main)
    {
        try
        {
            printMainMenu();
            std::string mode;
            getline(cin, mode);
            Validator::validateInteger(mode);
            int integerMode = stoi(mode);
            Validator::validateIndex(integerMode, 1, 3);

            switch (integerMode)
            {
                case 1:
                {
                    bool run = true;
                    do
                    {
                        try
                        {
                            printAdminMenu();
                            std::string stringOption;
                            getline(cin, stringOption);
                            Validator::validateInteger(stringOption);
                            int integerOption = stoi(stringOption);
                            Validator::validateIndex(integerOption, 1, 5);
                            run = runAdmin(integerOption);
                        }
                        catch (TrenchCoatError &tce)
                        {
                            cout << endl << RED << tce.what() << RESET << endl;
                        }
                        catch (DatabaseRepoError &dre)
                        {
                            cout << endl << RED << dre.what() << RESET << endl;
                        }
                        catch (ValueError &ve)
                        {
                            cout << endl << RED << ve.what() << RESET << endl;
                        }
                        catch (IndexError &ie)
                        {
                            cout << endl << RED << ie.what() << RESET << endl;
                        }

                    } while (run);
                    break;
                }
                case 2:
                {
                    bool run = true;
                    do
                    {
                        try
                        {
                            printUserMenu();
                            std::string stringOption;
                            getline(cin, stringOption);
                            Validator::validateInteger(stringOption);
                            int integerOption = stoi(stringOption);
                            Validator::validateIndex(integerOption, 1, 4);
                            run = runUser(integerOption);
                        }
                        catch (ValueError &ve)
                        {
                            cout << endl << RED << ve.what() << RESET << endl;
                        }
                        catch (IndexError &ie)
                        {
                            cout << endl << RED << ie.what() << RESET << endl;
                        }

                    } while (run);

                    break;
                }
                case 3:
                {
                    run_main = false;
                    break;
                }

            }
        }
        catch (ValueError &ve)
        {
            cout << endl << RED << ve.what() << RESET << endl;
        }
        catch (IndexError &ie)
        {
            cout << endl << RED << ie.what() << RESET << endl;
        }
    }
    cout << MAGENTA << "\n   Goodbye!\n" << RESET;
}


