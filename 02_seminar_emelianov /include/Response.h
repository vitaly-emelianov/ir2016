#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <map>
#include "Document.h"


struct Response
{
    Response(Document doc, double docRank, std::map<int, double> queryRanks);
    virtual ~Response();
    Document doc;
    double docRank;
    std::map<int, double> queryRanks;

    bool operator < (const Response& other) const;
};

#endif // RESPONSE_H
