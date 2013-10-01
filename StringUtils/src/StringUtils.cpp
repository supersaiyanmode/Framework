#include "StringUtils.h"
#include <cctype>
#include <algorithm>

std::string StringUtils::ltrim(const std::string& s, const std::string& trimChars){
    std::string ret(s);
    size_t pos = ret.find_first_not_of(trimChars);
    if (pos != std::string::npos)
        ret.substr(pos).swap(ret);
    return ret;
}

std::string StringUtils::rtrim(const std::string& s, const std::string& trimChars){
    std::string ret(s);
    size_t pos = ret.find_last_not_of(trimChars);
    if (pos != std::string::npos)
        ret.substr(0, pos+1).swap(ret);
    return ret;
}

std::string StringUtils::trim(const std::string& s, const std::string& trimChars){
    return ltrim(rtrim(s,trimChars), trimChars);
}

std::vector<std::string> StringUtils::splitAny(const std::string& str, const std::string& sep,
                        bool keepEmpty) {
    std::vector<std::string> ret;
    size_t start=0, end;
    while(true) {
        end = str.find_first_of(sep, start);
        if(end == std::string::npos) {
            end = str.length();
            if(start != end || keepEmpty)
                ret.push_back(std::string(str.begin()+start, str.begin()+end));
            break;
        } else {
             if(start != end || keepEmpty)
                 ret.push_back(std::string(str.begin()+start, str.begin()+end));
        }
        start = end + 1;
    }
    return ret;
}

std::vector<std::string> StringUtils::split(const std::string& str, const std::string& sep,
                    bool keepEmpty){
    std::vector<std::string> ret;
    return ret;
}

std::pair<std::string, std::string> StringUtils::partition(const std::string& str, const std::string& splitStr) {
    size_t posSplit = has(str, splitStr);
    if (posSplit == std::string::npos)
        return std::make_pair("","");
    std::string part1, part2;
    if (posSplit != 0)
        part1 = str.substr(0,posSplit-1);
    if (posSplit != str.size() - 1)
        part2 = str.substr(posSplit+1);
    return std::make_pair(part1, part2);
}

std::string StringUtils::toLower(std::string data) {
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

std::string StringUtils::toUpper(std::string data) {
    std::transform(data.begin(), data.end(), data.begin(), ::toupper);
    return data;
}


bool StringUtils::startsWith(const std::string& str1, const std::string& str2) {
    if (str1.size() * str2.size() == 0)
        return false;
    if (str1.size() < str2.size())
        return false;
    return std::equal(str2.begin(), str2.end(), str1.begin());
}

bool StringUtils::endsWith(const std::string& str1, const std::string& str2) {
    if (str1.size() * str2.size() == 0)
        return false;
    if (str1.size() < str2.size())
        return false;
    return std::equal(str2.rbegin(), str2.rend(), str1.rbegin());
}

size_t StringUtils::has(const std::string& str, const std::string& substr) {
    return str.find(substr);
}
