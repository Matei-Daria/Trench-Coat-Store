#pragma once

#include "Exceptions.h"
#include "../Entities/TrenchCoat.h"
#include <string>
#include <vector>

class Validator
{
public:
    static void validateNewTrenchCoat(const std::string& price, const std::string& quantity);
    static void validateDeleteTC(const TrenchCoat& tc);
    static void validateAddIdenticalTC(std::vector<TrenchCoat> repo, TrenchCoat& tc);
    static void validateUpdateIdenticalTC(std::vector<TrenchCoat> repo, TrenchCoat& tc);
    static void validateInteger(const std::string& value);
    static void validateIndex(int index, int start, int end);
    static void validateBuyTC(const TrenchCoat& tc);
    static void validateUserResponse(const std::string& response);

private:
    static bool validFloat(std::string input);
    static bool validInteger(const std::string& input);
};