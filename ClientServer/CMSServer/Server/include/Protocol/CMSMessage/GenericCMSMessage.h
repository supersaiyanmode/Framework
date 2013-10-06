#ifndef GENERICCMS_MESSAGE_H
#define GENERICCMS_MESSAGE_H

#include "IO/SocketIO/Connection.h"

#include "Header/CMSHeaderSet.h"
#include "../CMSDestination/CMSDestination.h"
#include "../CMSDestination/CMSDestGroup.h"


class GenericCMSMessage {
    CMSHeaderSet standardHeaders,customHeaders;
    std::string message_;
    
    static GenericCMSMessage read(Connection&);
public:
    enum CMSMessageType {
        Queue=1,
        Topic,
        Register,
        UnRegister
    };
    static std::string CMSMessageTypeToStr(const CMSMessageType&);
    static CMSMessageType strToCMSMessageType(const std::string&);
    
    GenericCMSMessage();
    GenericCMSMessage(const CMSHeaderSet&, const CMSHeaderSet&, const std::string&);
    ~GenericCMSMessage();
    
    
    std::string getStandardHeader(const std::string&) const;
    std::string getCustomHeader(const std::string&) const;
    
    void updateStandardHeader(const std::string&, const std::string&);
    void updateCustomHeader(const std::string&, const std::string&);
    
    
    bool isForward() const;
    CMSMessageType category() const;
    CMSDestGroup destination() const;
    
    std::string str();
    const std::string& message() const;
    
    
    
    static bool read(Connection&, GenericCMSMessage&);
    static bool parse(const std::string&, GenericCMSMessage&, bool (*)(const GenericCMSMessage&)=0);
    static bool parse(const std::string&, GenericCMSMessage&, 
        const std::vector<bool (*)(const GenericCMSMessage&)>&);
    static bool parse(Connection&, GenericCMSMessage&, bool (*)(const GenericCMSMessage&)=0);
    static bool parse(Connection&, GenericCMSMessage&, 
        const std::vector<bool (*)(const GenericCMSMessage&)>&);
};

//INLINE FUNCTIONS


inline std::string GenericCMSMessage::CMSMessageTypeToStr(const GenericCMSMessage::CMSMessageType& t) {
    switch (t){
        case Queue:
            return "queue";
        case Topic:
            return "topic";
        case Register:
            return "register";
        case UnRegister:
            return "unregister";
    }
    return "";
}

inline GenericCMSMessage::CMSMessageType GenericCMSMessage::strToCMSMessageType(const std::string& s) {
    if (s == "queue")           return Queue;
    else if (s == "topic")      return Topic;
    else if (s == "register")   return Register;
    else if (s == "unregister") return UnRegister;
    return (GenericCMSMessage::CMSMessageType)0;
}

inline std::string GenericCMSMessage::getStandardHeader(const std::string& s) const {
    return standardHeaders.get(s);
}

inline std::string GenericCMSMessage::getCustomHeader(const std::string& s) const{
    return customHeaders.get(s);
}

inline void GenericCMSMessage::updateStandardHeader(const std::string& k, const std::string& v) {
    standardHeaders[k] = v;
}
    


inline bool GenericCMSMessage::isForward() const {
    return standardHeaders.get("direction") == "forward";
}

inline GenericCMSMessage::CMSMessageType GenericCMSMessage::category() const {
    return strToCMSMessageType(standardHeaders.get("category"));
}

inline CMSDestGroup GenericCMSMessage::destination() const {
    return standardHeaders.get("destination");
}

inline const std::string& GenericCMSMessage::message() const {
    return message_;
}



#endif