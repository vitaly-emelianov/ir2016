#ifndef SEARCHROBOT_H
#define SEARCHROBOT_H
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Response.h"
#include "Document.h"


class SearchRobot {
    public:
        SearchRobot();
        virtual ~SearchRobot();
        std::vector<Response> searchQuery(const std::string& query);
        void uploadWordId(const std::string& path);
        void uploadDocId(const std::string& path);
        void uploadIndex(const std::string& path);
        std::map<int, std::map<int, int> > index;
        std::map<std::string, int> wordId;
        std::map<int, Document> docId;
    protected:
    private:



};

#endif // SEARCHROBOT_H
