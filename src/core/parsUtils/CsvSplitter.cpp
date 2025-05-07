// src/parsUtils/CsvSplitter.cpp
#include "core/parsUtils/CsvSplitter.h"
#include <sstream>

std::vector<std::string> CsvSplitter::split(const std::string& input) const {
    
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ';')) {
        tokens.push_back(token);
    }

    return tokens;
}