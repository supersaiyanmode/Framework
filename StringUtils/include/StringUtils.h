#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>
#include <algorithm>

class StringUtils {
public:
    
    static std::string ltrim(const std::string&, const std::string& = " \t\r\n");
    static std::string rtrim(const std::string&, const std::string& = " \t\r\n");
    static std::string trim(const std::string&, const std::string& = " \t\r\n");
    
    static std::vector<std::string> splitAny(const std::string&, const std::string& = " \t\n\r",
                bool = false);
    static std::vector<std::string> split(const std::string&, const std::string& = " \t\n\r",
                bool = false);
    static std::pair<std::string, std::string> partition(const std::string& str,
                const std::string& splitStr);
                
    static std::string toLower(std::string);
    static std::string toUpper(std::string);
    
    static bool startsWith(const std::string& str, const std::string& substr);
    static bool endsWith(const std::string& str, const std::string& substr);
    
    static size_t has(const std::string& str, const std::string& substr);
};


#endif
