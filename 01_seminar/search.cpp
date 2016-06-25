#include <iostream>
#include <vector>
#include <fstream>
#include "include/SearchRobot.h"
#include "include/Filesystem.h"
#include "include/Parser.h"
#include "include/IndexBuilder.h"


using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Type query after \'search\' command" << std::endl;
        exit(0);
    } else {
        auto sr = new SearchRobot();
        auto docs = sr->searchQuery(std::string(argv[1]));
        std::cout << "Total: " << docs.size() << " result(s)" << std::endl;
        if (docs.size() <= 10) {
            for (const auto& doc: docs) {
                std::cout << doc << std:: endl;
            }
        } else {
            for (size_t i=0; i < 10; ++i) {
                std::cout << docs[i] << std::endl;
            }
        }
    }
    return 0;
}
