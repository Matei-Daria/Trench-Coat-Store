#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-use-anyofallof"
#include "Validators.h"
#include "../Repo/DatabaseRepo/DatabaseFileRepo.h"

void Validator::validateNewTrenchCoat(const std::string& price, const std::string& quantity)
{
    if (price != "-")
    {
        if (!validFloat(price))
            throw TrenchCoatError("The price must be a rational number.");
        float float_price = std::stof(price);
        if (float_price < 0)
            throw TrenchCoatError("The price cannot be negative.");
    }
    if (quantity != "-")
    {
        if (!validInteger(quantity))
            throw TrenchCoatError("The quantity must be an integer number.");
        int int_quantity = std::stoi(quantity);
        if (int_quantity < 0)
            throw TrenchCoatError("The quantity cannot be negative.");
    }
}

bool Validator::validFloat(std::string input)
{
    for (int c = 0; c < input.size(); c++)
        if (!(std::isdigit(input[c])))
        {
            if (c != 0 and c != input.size() - 1)
            {
                if (!(std::isdigit(input[c - 1]) and std::isdigit(input[c + 1])))
                    return false;
            } else
                return false;
        }
    return true;
}

bool Validator::validInteger(const std::string& input)
{
    for (char c: input)
    {
        if (!std::isdigit(c))
            return false;
    }
    return true;
}

void Validator::validateInteger(const std::string &value)
{
    if (!validInteger(value))
        throw ValueError("The number you entered is not a valid integer.");
}

void Validator::validateIndex(int index, int start, int end)
{
    if (!(index >= start && index <= end))
        throw IndexError("The position you entered is not a valid one.");
}

void Validator::validateDeleteTC(const TrenchCoat& tc)
{
    if (tc.getQuantity() != 0)
        throw TrenchCoatError("Cannot delete a trench coat that is not sold out.");
}

void Validator::validateAddIdenticalTC(std::vector<TrenchCoat> repo, TrenchCoat &tc)
{
    bool identical = std::any_of(repo.begin(), repo.end(),
                       [&tc](const TrenchCoat &otherTC)
                       { return otherTC == tc; });
    if (identical)
        throw DatabaseRepoError("This trench coat already exists.");
}

void Validator::validateBuyTC(const TrenchCoat& tc)
{
    if (tc.getQuantity() == 0)
        throw CartRepoError("This item is sold out. It hasn't been added to the cart.");
}

void Validator::validateUserResponse(const std::string& response)
{
    if (response != "no" && response != "yes" && response != "photo" && response != "exit")
        throw ValueError("The command you entered is not valid.");
}

void Validator::validateUpdateIdenticalTC(std::vector<TrenchCoat> repo, TrenchCoat &tc)
{
    bool identical = std::any_of(repo.begin(), repo.end(),
                                [&tc](const TrenchCoat &otherTC)
                                { return otherTC == tc && otherTC.getQuantity() == tc.getQuantity() &&
                                otherTC.getPrice() == tc.getPrice(); });
    if (identical)
        throw DatabaseRepoError("This trench coat already exists.");
}

