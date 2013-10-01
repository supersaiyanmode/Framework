#include "ConfigurationFileParser.h"
#include "StringUtils.h"

ConfigurationFile::ConfigurationFile(const std::string& path) {
    inFile.open(path.c_str(), std::ios::in);
}

ConfigurationFile::~ConfigurationFile() {}

bool ConfigurationFile::good() {
    return !inFile.bad();
}

void ConfigurationFile::load() {
    std::map<std::string, std::string> props;
    std::string line;
    
    while(std::getline(inFile, line)) {
        std::string trimmed(StringUtils::trim(line));
        if (!trimmed.length() || trimmed[0] == '#')
            continue;
        if (StringUtils::startsWith(trimmed,"@"))
            continue;
        if (!StringUtils::has(trimmed, "="))
            continue;
        std::pair<std::string, std::string> parts = StringUtils::partition(trimmed, "=");
        props[StringUtils::trim(parts.first)] = parts.second;
    }
    //TODO: If everything went well, copy into this->properties
    properties = props;
}

const std::string& ConfigurationFile::operator[](const std::string& key) const {
    const static std::string EMPTY = "";
    for (std::map<std::string, std::string>::const_iterator it=properties.begin(); 
                it != properties.end(); it++){
        if (it->first == key)
            return it->second;
    }
    return EMPTY;
}