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

void IndexBuilder::buildBooleanIndex() {

    auto docs = Filesystem::listOfFiles(path);
    int wordCounter = 0;

    for (size_t id = 0; id < docs.size(); ++id) {
        docId[id] = docs[id];
        auto words = Parser::parse(path + docs[id]);

        for (const auto& word: words) {
            if (wordToDocId.find(word) == wordToDocId.end()) {
                wordId[word] = wordCounter;
                wordCounter++;
            }
            wordToDocId[word].insert(id);
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
        file << item.first << " " << item.second << std::endl;
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
    for (const auto& item: wordToDocId) {
        std::set<int> ids = item.second;

        file << wordId[item.first];
        for (const auto& id: ids) {
            file << " " << id;
        }
        file << std::endl;
    }
    file.close();
}
