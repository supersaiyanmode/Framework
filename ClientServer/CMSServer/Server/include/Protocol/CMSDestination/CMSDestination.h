#ifndef CMS_DEST_GROUP
#define CMS_DEST_GROUP

#include <string>
#include <vector>

#include "CMSDestGroup.h"

class CMSDestination : public CMSDestGroup {
public:
    CMSDestination();
    CMSDestination(const std::string&);
    ~CMSDestination();
    
    operator std::string() const;
    std::string str();
    
};

inline CMSDestination::operator std::string() const{
    return destination;
}

inline std::string CMSDestination::str() {
    return destination;
}

#endif