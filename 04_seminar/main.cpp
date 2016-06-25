#include <iostream>
#include <string>
#include "conversion.h"


int main() {
    std::string line = "";
    uint8_t* buffer = new uint8_t[10];
    while(std::cin >> line) {
        uint64_t number = std::strtoull(line.c_str(),'\0', 10);
        size_t outsize = Conversion::encodeVarInt(buffer, number);
        std::cout << Conversion::decodeVarInt(buffer, outsize) << std::endl;
    }
    delete[] buffer;
    return 0;
}