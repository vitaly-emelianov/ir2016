#include "../include/IndexBuilder.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "../include/Filesystem.h"
#include "../include/Parser.h"


IndexBuilder::IndexBuilder(const std::string& path) {
    this->path = path;
}

IndexBuilder::~IndexBuilder() {
    //dtor
}

void IndexBuilder::buildIndex() {
    auto docs = Filesystem::listOfFiles(path);
    int wordCounter = 0;
    for (size_t id = 0; id < docs.size(); ++id) {
        auto words = Parser::parse(path + docs[id]);
        docId[id] = std::make_pair(docs[id], words.size());
        for (const auto& word: words) {
            if (wordToIndex.find(word) == wordToIndex.end()) {
                wordId[word] = wordCounter;
                wordCounter++;
            }
            wordToIndex[word][id] += 1;
        }
    }
    saveDocId("./docId.txt");
    saveWordId("./wordId.txt");
    saveIndex("./index.txt");
}

void IndexBuilder::saveDocId(const std::string& path) {
    std::ofstream file;
    file.open (path);
    for (const auto& item: docId) {
        file << item.first << " " << (item.second).first << " " << (item.second).second << std::endl;
    }
    file.close();
}

void IndexBuilder::saveWordId(const std::string& path) {
    std::ofstream file;
    file.open (path);
    for (const auto& item: wordId) {
        file << item.first << " " << item.second << std::endl;
    }
    file.close();
}


void IndexBuilder::saveIndex(const std::string& path) {
    std::ofstream file;
    file.open (path);
    for (const auto& item: wordToIndex) {
        std::map<int, int> docToCounts = item.second;

        file << wordId[item.first];
        for (const auto& docToCount: docToCounts) {
            file << " " << docToCount.first << " " << docToCount.second;
        }
        file << std::endl;
    }
    file.close();
}
