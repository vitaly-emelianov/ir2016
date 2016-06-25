#include "../include/SearchRobot.h"
#include "../include/Parser.h"
#include "../include/Response.h"
#include "../include/Document.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


SearchRobot::SearchRobot() {
    uploadIndex("./index.txt");
    uploadWordId("./wordId.txt");
    uploadDocId("./docId.txt");
}

SearchRobot::~SearchRobot() {
    //dtor
}

void SearchRobot::uploadWordId(const std::string& path) {
    std::ifstream infile(path);
    std::string line;
    size_t pos = 0;
    std::string word;
    size_t id = 0;
    while (std::getline(infile, line)) {
        pos = line.find(' ');
        word = line.substr(0, pos);
        id = std::stoi(line.substr(pos + 1, line.length() - pos));
        wordId[word] = id;
    }
}

void SearchRobot::uploadDocId(const std::string& path) {
    std::ifstream infile(path);
    std::string line;
    size_t startPos = 0;
    size_t endPos = 0;
    std::string doc;
    int counts = 0;
    size_t id = 0;
    while (std::getline(infile, line)) {
        endPos = line.find_first_of(' ', startPos);
        id = std::stoi(line.substr(startPos, endPos - startPos));
        startPos = endPos + 1;
        endPos = line.find_first_of(' ', startPos);
        doc = line.substr(startPos, endPos - startPos);
        startPos = endPos + 1;
        counts = std::stoi(line.substr(startPos, line.length() - startPos));
        docId[id] = Document(doc, counts);
        startPos = 0;
        endPos = 0;
    }
}

void SearchRobot::uploadIndex(const std::string& path) {
    std::ifstream infile(path);
    std::string line;
    size_t startPos = 0;
    size_t endPos = 0;
    int doc = 0;
    double tf = 0.;
    int word = 0;
    while (std::getline(infile, line)) {
        endPos = line.find_first_of(' ', startPos);
        word = std::stoi(line.substr(startPos, endPos));
        startPos = endPos + 1;
        while (endPos != std::string::npos) {
            endPos = line.find_first_of(' ', startPos);
            doc = std::stoi(line.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            endPos = line.find_first_of(' ', startPos);
            tf = std::stoi(line.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            index[word].insert(std::make_pair(doc, tf));
        }
    }
}


std::vector<Response> SearchRobot::searchQuery(const std::string& queryLine) {

    std::vector<std::string> tokens;
    Parser::parseLine(tokens, queryLine);
    std::vector<int> query;
    for (const auto& token: tokens) {
        if (wordId.find(token) != wordId.end()) {
            query.push_back(wordId[token]);
        }
    }

    std::map<int, double> docToRank;
    std::map<int, std::map<int, double> > docToQueryRank;
    for (const auto& word: query) {
        for (const auto& item: index[word]) {
            int doc = item.first;
            int count = item.second;
            double tf = double(count) / double(docId[doc].length);
            double idf = std::log(double(docId.size()) / double(index[word].size()));
            if (docToQueryRank.find(doc) == docToQueryRank.end()) {
                for (const auto& word: query) {
                    docToQueryRank[doc][word] = 0.;
                }
            }
            docToRank[doc] += tf * idf;
            docToQueryRank[doc][word] = tf * idf;
        }
    }

    std::vector<Response> responses;

    for (const auto& item: docToRank) {
        responses.push_back(Response(docId[item.first], item.second, docToQueryRank[item.first]));
    }

    std::sort(responses.rbegin(), responses.rend());
    return responses;
}
