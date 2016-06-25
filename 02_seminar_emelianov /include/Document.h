#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>

struct Document
{
    Document();
    Document(std::string name, int length);
    virtual ~Document();
    std::string name;
    int length;
};

#endif // DOCUMENT_H
