#ifndef CMS_HEADER_SET
#define CMS_HEADER_SET

#include <map>
#include <vector>
#include <string>

class CMSHeaderSet {
    std::map<std::string, std::string> headers;
public:
    std::string str();
    
    inline std::string& operator[](const std::string&);
    bool exists(const std::string&) const;
    std::string get(const std::string&) const;
    
    static bool parseStandardHeaders(const std::vector<std::string>&, CMSHeaderSet&);
    static bool parseCustomHeaders(const std::vector<std::string>&, CMSHeaderSet&);
};


//INLINE FUNCTIONS

inline bool CMSHeaderSet::exists(const std::string& h) const{
    return headers.find(h) != headers.end();
}

inline std::string& CMSHeaderSet::operator[](const std::string& h) {
    return headers[h];
}
#endif