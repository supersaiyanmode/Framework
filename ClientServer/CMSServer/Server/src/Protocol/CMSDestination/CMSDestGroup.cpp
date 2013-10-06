#include <algorithm>
#include <iostream>
#include <functional>


#include "StringUtils.h"

#include "Protocol/CMSDestination/CMSDestination.h"
#include "Protocol/Exception/ProtocolException.h"

struct isNotAlnum {
    bool operator()(char c){ 
        return !isalnum(c);
    }
};

//TODO: Have validateParts return -1 for invalid, 0 for group, 1 for absolute
// CMSDestination can reuse this.
CMSDestGroup::Type validateParts(const std::vector<std::string>& parts) {
    if (parts.size() < 2)
        return CMSDestGroup::NONE;
    
    std::vector<std::string>::const_iterator it = parts.begin();
    for (; it!=parts.end(); it++) {
        if (it->length() < 1)
            return CMSDestGroup::NONE;
        if (std::find_if(it->begin(), it->end(), isNotAlnum()) != it->end()) {
            if (&parts.back() != &*it)  //Not the last item
                return CMSDestGroup::NONE;
            if (*it != ">")             //Not the group string
                return CMSDestGroup::NONE;
            return CMSDestGroup::GROUP;
        }
    }
    return CMSDestGroup::ABSOLUTE;
}


CMSDestGroup::CMSDestGroup() {
    type = NONE;
}

CMSDestGroup::CMSDestGroup(const std::string& s) {
    std::vector<std::string> parts = StringUtils::splitAny(s, ".", true);
    type = validateParts(parts);
    if (type == NONE)
        throw ProtocolException("Invalid CMSDestGroup: " + s);
    this->parts = parts;
    this->destination = s;
}

CMSDestGroup::~CMSDestGroup(){
    
}

bool CMSDestGroup::matches(const CMSDestGroup& other) const {
    if (type == NONE || other.type == NONE)
        return false;
    if (parts.size() * other.parts.size() == 0)
        return false;
    
    std::vector<std::string>::const_iterator it1 = parts.begin();
    std::vector<std::string>::const_iterator it2 = other.parts.begin();
    
    while (true) {
        if (it1 == parts.end() && it2 == other.parts.end())
            return true;
            
        if (it1 == parts.end() || it2 == other.parts.end())
            return false;
        
        if (*it1 != *it2) 
            break;
        it1 ++;
        it2 ++;
    }
    
    return *it1 == ">" || *it2 == ">";
}

#if defined(DEST_GROUP_TEST)

int main() {
    std::cout<<CMSDestGroup("A.B.C.D.E").matches(CMSDestGroup("a.>"))<<std::endl;;
}

#endif
