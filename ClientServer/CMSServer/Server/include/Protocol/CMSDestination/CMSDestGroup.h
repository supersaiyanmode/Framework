#ifndef CMS_DESTINATION_H
#define CMS_DESTINATION_H

#include <string>
#include <vector>

class CMSDestGroup {
public:
    enum Type {NONE, GROUP, ABSOLUTE};
    CMSDestGroup();
    CMSDestGroup(const std::string&);
    virtual ~CMSDestGroup();
    
    bool valid() const;
    bool matches(const CMSDestGroup&) const;
    
    friend int operator<(const CMSDestGroup&, const CMSDestGroup&);
    virtual operator std::string() const;
    
    
    virtual std::string str();
    
protected:
    std::string destination;
    std::vector<std::string> parts;
    Type type;
};

inline int operator<(const CMSDestGroup& lhs, const CMSDestGroup& rhs) {
    //Dumb, but to enable CMSDestGroup as a key in std::map.
    return lhs.destination < rhs.destination;
}

inline bool CMSDestGroup::valid() const {
    return type != NONE;
}

inline CMSDestGroup::operator std::string() const{
    return destination;
}

inline std::string CMSDestGroup::str() {
    return destination;
}

#endif