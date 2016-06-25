#ifndef INDEXBUILDER_H
#define INDEXBUILDER_H
#include <string>
#include <map>
#include <set>


class IndexBuilder {
    public:
        IndexBuilder(const std::string& path);
        virtual ~IndexBuilder();
        void buildIndex();
        void saveDocId(const std::string& path);
        void saveWordId(const std::string& path);
        void saveIndex(const std::string& path);
    protected:
    private:
        std::string path;
        std::map<std::string, std::map<int, int> > wordToIndex;
        std::map<int, std::pair<std::string, int> > docId;
        std::map<std::string, int> wordId;
};

#endif // INDEXBUILDER_H
