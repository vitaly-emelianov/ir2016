#ifndef INDEXBUILDER_H
#define INDEXBUILDER_H
#include <string>
#include <map>
#include <set>


class IndexBuilder {
    public:
        IndexBuilder(const std::string& path);
        virtual ~IndexBuilder();
        void buildBooleanIndex();
        void saveDocId(const std::string& path);
        void saveWordId(const std::string& path);
        void saveIndex(const std::string& path);
    protected:
    private:
        std::string path;
        std::map<std::string, std::set<int> > wordToDocId;
        std::map<int, std::string> docId;
        std::map<std::string, int> wordId;
};

#endif // INDEXBUILDER_H
