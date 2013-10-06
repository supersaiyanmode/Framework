#include "OptParse.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
    
OptParse::OptParse(OptParseData* data, size_t len, const char* prefix):
         optionPrefix(prefix){
    std::vector<std::string> shortOptSeen, longOptSeen;
    for (size_t i=0; i<len; i++) {
        if (std::find(shortOptSeen.begin(), shortOptSeen.end(), data[i].shortOption) != shortOptSeen.end() ||
                std::find(longOptSeen.begin(), longOptSeen.end(), data[i].longOption) != longOptSeen.end()) 
            throw "Invalid OptParse Data";
        shortOptSeen.push_back(data[i].shortOption);
        longOptSeen.push_back(data[i].longOption);
        optParseData.push_back(data[i]);
    }
    appName = "<App-Name>";
}
OptParse::~OptParse(){}

void OptParse::displayHelp() {
    std::cout<<appName<<std::endl;
    std::cout<<"Valid parameters are: \n";
    for (std::vector<OptParseData>::iterator it=optParseData.begin(); it!=optParseData.end(); it++){
        std::string option = optionPrefix + it->longOption + ", " + optionPrefix+ it->shortOption;
        std::cout<<std::setw(20)<<std::left<<option<<std::right<<it->helpString<<std::endl;
    }
    std::cout<<std::endl;
}

bool OptParse::parse(int argc, char** argv) {
    if (argc < 1 || !argv)
        return false;
    appName = argv[0];
    bool prefixedParam = false;
    std::string previousPrefix;
    unsigned prefixLen = optionPrefix.length();
    
    for (int i=1; i<argc; i++){
        char *curParam = argv[i];
        if (std::strlen(curParam) > prefixLen && //Is prefix wala param?
                !std::strncmp(curParam, optionPrefix.c_str(), prefixLen)) {
            //first check for boolean option type.
            bool found = false;
            for (std::vector<OptParseData>::iterator it=optParseData.begin();
                            !found && it!=optParseData.end(); it++) {
                if (it->isBoolType)
                    found = true;
            }
            if (found) {
                map[curParam] = "";
            } else {
                previousPrefix = curParam;
                prefixedParam = true;
            }
        } else if (prefixedParam && previousPrefix.length() > 0){
            prefixedParam = false;
            map[previousPrefix] = curParam;
            previousPrefix = "";
        } else {
            extra.push_back(curParam);
        }
    }
    return true;
}

std::string OptParse::operator[](const std::string& arg) const {
    std::map<std::string, std::string>::const_iterator it = map.find(optionPrefix + arg);
    return it == map.end()? "" : it->second;
}

std::string OptParse::operator[](int pos) const {
    return pos < (int)extra.size() && pos >= 0? extra[pos] : "";
}

bool OptParse::exists(const std::string& arg) const {
    return map.find(arg) != map.end();
}


//TODO: Test this unit!