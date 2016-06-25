#include "../include/Parser.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

Parser::Parser() {
    //ctor
}

Parser::~Parser() {
    //dtor
}


bool Parser::isValidToken(const std::string token) {
    std::string::const_iterator it = token.begin();
    while (it != token.end() && std::isdigit(*it)) ++it;
    return !token.empty() && it != token.end();
}

std::vector<std::string> Parser::parse(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<std::string> tokens;
    std::string line;
    while (std::getline(infile, line)) {
        parseLine(tokens, line);
    }
    return tokens;
}

void Parser::parseLine(std::vector<std::string>& tokens, const std::string& line) {
    size_t tokenStartPosition = 0;
    std::string token;
    auto currentPosition = line.find_first_of(DELIMETERS, 0);
    while (currentPosition != std::string::npos) {
        token = line.substr(tokenStartPosition, currentPosition - tokenStartPosition);
        if (isValidToken(token)) {
            std::transform(token.begin(), token.end(), token.begin(), ::tolower);
            tokens.push_back(token);
        }
        tokenStartPosition = currentPosition + 1;
        currentPosition = line.find_first_of(DELIMETERS, tokenStartPosition);
    }
    token = line.substr(tokenStartPosition, currentPosition - tokenStartPosition);
    if (isValidToken(token)) {
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        tokens.push_back(token);
    }
}

