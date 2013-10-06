#include <iostream>

#include "Protocol/CMSMessage/GenericCMSMessage.h"
#include "IO/Structure/Line/LineReader.h"
#include "IO/Structure/Block/BlockReader.h"
//#include "../../Util/DataType/Primitive/Number.h"
#include "ThreadLogger.h"

namespace {
    bool readHeaders(LineReader& lr, std::vector<std::string>& lines){
        std::string line;
        int linesRead = 0;
        //Read headers
        while (lr.readable() && (line = lr.readLine()) != ""){
            lines.push_back(line);
            linesRead ++;
        }
        
        //Good if more than one line read, and the last line is blank!
        return linesRead > 0 && line == "";
    }
}


GenericCMSMessage::GenericCMSMessage(){}
GenericCMSMessage::~GenericCMSMessage(){}

GenericCMSMessage::GenericCMSMessage(const CMSHeaderSet& h1, const CMSHeaderSet& h2,
            const std::string& msg) : standardHeaders(h1), customHeaders(h2), message_(msg){
    
}

bool GenericCMSMessage::read(Connection& device, GenericCMSMessage& out){
    LineReader lr(device);
    
    std::vector<std::string> standardHeaders, customHeaders;
    
    if (!readHeaders(lr, standardHeaders)){
        std::cout<<"Unexpected end. Invalid CMS Headers\n";
        return false;
    }
    
    //process Headers..
    if (!CMSHeaderSet::parseStandardHeaders(standardHeaders, out.standardHeaders)){
        std::cout<<"Invalid CMS Headers\n";
        return false;
    }
    
    
    if (out.standardHeaders["has-custom-headers"] == "true"){
        //read up and parse custom headers
        if (!readHeaders(lr, customHeaders)){
            std::cout<<"Unexpected end. Invalid CMS Headers\n";
            return false;
        }
        
        if (!CMSHeaderSet::parseCustomHeaders(standardHeaders, out.customHeaders)){
            std::cout<<"Invalid custom headers\n";
            return false;
        }
    }


    int length;
    std::stringstream ssLength(out.standardHeaders["content-length"]);
    if (!(ssLength>>length)) {
        std::cout<<"Invalid header: Content-Length\n";
        return false;
    }

    BlockReader br(device, lr.getBackBuffer());
    out.message_ = br.read(length);
    return true;
}

bool GenericCMSMessage::parse(Connection& device, GenericCMSMessage& out,
                bool (*condition)(const GenericCMSMessage&)){
    
    if (!read(device, out))
        return false;

    if (condition)
        return (*condition)(out);
    return true;
}

bool GenericCMSMessage::parse(Connection& device, GenericCMSMessage& out, 
                const std::vector<bool (*)(const GenericCMSMessage&)>& conditions){
    if (!read(device, out))
        return false;

    for (std::vector<bool (*)(const GenericCMSMessage&)>::const_iterator it=conditions.begin();
                            it != conditions.end(); it++){
        if (*it && !(*it)(out))
            return false;
    }
    return true;    
}


/*bool GenericCMSMessage::parse(InputOutputCapable&, GenericCMSMessage&, 
const std::vector<bool (*)(GenericCMSMessage)>& = std::vector<bool (*)(GenericCMSMessage)>());*/

std::string GenericCMSMessage::str() {
    std::stringstream ss;
    ss<<message_.length();
    
    standardHeaders["content-length"] = ss.str();
    std::string ret(standardHeaders.str() + "\n");
    if (standardHeaders["has-custom-headers"] == "true")
        ret += customHeaders.str() + "\n";
    if (message_.length() > 0)
        ret += message_;
    return ret;
}
