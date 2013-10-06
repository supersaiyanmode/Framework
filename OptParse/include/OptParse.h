#ifndef OPT_PARSE_H
#define OPT_PARSE_H
#include <string>
#include <map>
#include <vector>

//TODO: Display of options. --help menu.

struct OptParseData {
    std::string shortOption;
    std::string longOption;
    std::string helpString;
    int isBoolType;
};

class OptParse {
    std::string optionPrefix;
    std::string appName;
    std::map<std::string, std::string> map;
    std::vector<std::string> extra;
    std::vector<OptParseData> optParseData;
public:
    OptParse(OptParseData*, size_t, const char* = "-");
    ~OptParse();
    
    bool parse(int argc, char** argv);
    
    void displayHelp();
    
    std::string operator[](const std::string&) const;
    std::string operator[](int) const;
    
    bool exists(const std::string&) const;
};

#endif