#ifndef CONFIGURATION_FILE_PARSER_H
#define CONFIGURATION_FILE_PARSER_H

#include <string>
#include <fstream>
#include <map>

class ConfigurationFile {
    std::ifstream inFile;
    std::map<std::string, std::string> properties;
public:
    ConfigurationFile(const std::string& path);
    ~ConfigurationFile();
    
    bool good();
    void load();
    
    const std::string& operator[](const std::string& key) const;
};

#endif
