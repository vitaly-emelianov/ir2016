#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include <algorithm>

const std::string DELIMETERS = " \t\r\n.,:;!?$&\"\'`%#+-*/=|^~<>(){}[]@-";

class Parser
{
    public:
        Parser();
        virtual ~Parser();
        static std::vector<std::string> parse(const std::string& filename);
        static void parseLine(std::vector<std::string>& tokens, const std::string& line);
    protected:
    private:
        static bool isValidToken(const std::string token);
};

#endif // PARSER_H
