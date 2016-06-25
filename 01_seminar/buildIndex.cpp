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
        std::cout << "Type path after \'buildIndex\' command" << std::endl;
        exit(0);
    } else {
        auto ib = new IndexBuilder(std::string(argv[1]));
        ib->buildBooleanIndex();
        std::cout << "Index was built successfully" << std::endl;
    }
    return 0;
}
