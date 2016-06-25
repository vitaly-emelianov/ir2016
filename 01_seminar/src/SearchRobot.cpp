#include "../include/SearchRobot.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include "../include/Parser.h"

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
    size_t pos = 0;
    std::string doc;
    size_t id = 0;
    while (std::getline(infile, line)) {
        pos = line.find(' ');
        id = std::stoi(line.substr(0, pos));
        doc = line.substr(pos + 1, line.length() - pos);
        docId[id] = doc;
    }
}

void SearchRobot::uploadIndex(const std::string& path) {
    std::ifstream infile(path);
    std::string line;
    size_t startPos = 0;
    size_t endPos = 0;
    int doc = 0;
    int word = 0;
    while (std::getline(infile, line)) {
        endPos = line.find_first_of(' ', startPos);
        word = std::stoi(line.substr(startPos, endPos));
        startPos = endPos + 1;
        while (endPos != std::string::npos) {
            endPos = line.find_first_of(' ', startPos);
            doc = std::stoi(line.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            index[word].insert(doc);
        }
    }
}


std::vector<std::string> SearchRobot::searchQuery(const std::string& queryLine) {

    std::set<std::set<int> > docIds;
    std::vector<std::string> tokens;
    Parser::parseLine(tokens, queryLine);
    std::vector<int> query;
    std::vector<std::string> answer;

    for (const auto& token: tokens) {
        if (wordId.find(token) != wordId.end()) {
            query.push_back(wordId[token]);
        } else {
            return answer;
        }
    }

    for (const auto& id: query) {
        if (index.find(id) != index.end()) {
            docIds.insert(index[id]);
        }
    }

    std::map<int, int> counter;
    for (const auto& setDocId: docIds) {
        for (int id: setDocId) {
            counter[id]++;
        }
    }

    int docIdsSize = docIds.size();
    for (const auto& item: counter) {
        if (counter[item.first] == docIdsSize) {
            answer.push_back(docId[item.first]);
        }
    }
    return answer;
}
