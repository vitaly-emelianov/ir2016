#include "../include/Filesystem.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>


Filesystem::Filesystem() {
    //ctor
}

Filesystem::~Filesystem() {
    //dtor
}

std::vector<std::string> Filesystem::listOfEntries(const std::string& path=".") {
    std::vector<std::string> entries;
    auto dir = opendir(path.c_str());
    auto pdir = readdir(dir);
    while ( (pdir = readdir(dir)) ) {
        entries.push_back(pdir->d_name);
    }
    return entries;
}

bool Filesystem::isTextFile(const std::string& path) {
    if (path.find(".txt") != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

std::vector<std::string> Filesystem::listOfFiles(const std::string& path=".") {
    auto entries = listOfEntries(path);
    std::vector<std::string> files;

    for (const auto& f: entries) {
        if (isTextFile(f)) {
            files.push_back(f);
        }
    }
    return files;
}
