#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <string>
#include <vector>


class Filesystem
{
    public:
        Filesystem();
        virtual ~Filesystem();
        static std::vector<std::string> listOfEntries(const std::string& path);
        static std::vector<std::string> listOfFiles(const std::string& path);
        static bool isTextFile(const std::string& filename);
    protected:
    private:
};

#endif // FILESYSTEM_H
