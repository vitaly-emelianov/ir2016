#include "../include/Document.h"
#include <string>

Document::Document() {
}

Document::Document(std::string name, int length) {
    this->name = name;
    this->length = length;
}

Document::~Document() {
    //dtor
}
