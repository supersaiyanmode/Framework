#include "Protocol/CMSMessage/Header/CMSHeaderSet.h"
#include "StringUtils.h"

//NOTE: This includes the last \n too!
std::string CMSHeaderSet::str() {
    std::string ret;
    for (std::map<std::string, std::string>::const_iterator it=headers.begin();
                    it != headers.end(); it++){
                    
        if (it->second.length())
            ret += it->first + ": " + it->second + "\n";
    }
    return ret;
}

std::string CMSHeaderSet::get(const std::string& h) const {
    std::map<std::string, std::string>::const_iterator it = headers.find(h);
    if (it != headers.end())
        return it->second;
    return "";
}

bool CMSHeaderSet::parseStandardHeaders(const std::vector<std::string>& lines, CMSHeaderSet& out){
    CMSHeaderSet headers;
    if (!parseCustomHeaders(lines, headers))
        return false;
    headers.headers.swap(out.headers);
    return true;
}

bool CMSHeaderSet::parseCustomHeaders(const std::vector<std::string>& lines, CMSHeaderSet& out){
    CMSHeaderSet headers;
    for (std::vector<std::string>::const_iterator it=lines.begin();
                    it != lines.end(); it++){
        /*RegexMatcher re("^\\s*([A-Za-z0-9-]+)\\s*:\\s*(.*)$");
        if (!re.search(*it))
            return false;
        ExtractResult er = re.extract();
        headers.headers[er[1].value] = er[2].value; */
        std::vector<std::string> ret(StringUtils::splitAny(*it, ":"));
        if (ret.size() != 2)
            return false;
        //TODO: Assert proper [A-Za-z0-9-] for key and value
        headers.headers[StringUtils::trim(ret[0])] = StringUtils::trim(ret[1]);
    }
    headers.headers.swap(out.headers);
    return true;
}

