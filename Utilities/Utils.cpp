#include <sstream>
#include "Utils.h"

std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector<std::string> result{};
    std::stringstream s{str};
    std::string token;
    while(std::getline(s, token, delimiter))
        result.push_back(token);
    return result;
}