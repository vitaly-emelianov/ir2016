#ifndef SEARCHROBOT_H
#define SEARCHROBOT_H
#include <vector>
#include <string>
#include <map>
#include <set>


class SearchRobot {
    public:
        SearchRobot();
        virtual ~SearchRobot();
        std::vector<std::string> searchQuery(const std::string& query);
        void uploadWordId(const std::string& path);
        void uploadDocId(const std::string& path);
        void uploadIndex(const std::string& path);
    protected:
    private:
        std::map<int, std::set<int> > index;
        std::map<std::string, int> wordId;
        std::map<int, std::string> docId;


};

#endif // SEARCHROBOT_H
