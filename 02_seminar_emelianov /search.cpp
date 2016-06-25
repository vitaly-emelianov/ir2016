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
        auto responses = sr->searchQuery(std::string(argv[1]));
        std::cout << "Total: " << responses.size() << " result(s)" << std::endl << std::endl;
        if (responses.size() <= 10) {
            for (auto response: responses) {
                std::cout << response.doc.name << std::endl;
                std::cout << "Document rank " << response.docRank << std::endl;
                std::cout << "Query ranks ";

                for (auto rank: response.queryRanks) {
                    std::cout << rank.second << " ";
                }
                std::cout << std::endl << std::endl;
            }
        } else {
            for (size_t i=0; i < 10; ++i) {
                std::cout << responses[i].doc.name << std::endl;
                std::cout << "Document rank " << responses[i].docRank << std::endl;
                std::cout << "Query ranks ";

                for (auto rank: responses[i].queryRanks) {
                    std::cout << rank.second << " ";
                }
                std::cout << std::endl << std::endl;
            }
        }
    }
    return 0;
}
