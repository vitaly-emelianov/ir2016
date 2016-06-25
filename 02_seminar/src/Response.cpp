#include "../include/Response.h"
#include "../include/Document.h"
#include <vector>

Response::Response(Document doc, double docRank, std::map<int, double> queryRanks)
{
    this->doc = doc;
    this->docRank = docRank;
    this->queryRanks = queryRanks;
}

Response::~Response()
{
    //dtor
}

bool Response::operator <(const Response& other) const{
    return docRank < other.docRank;
}
