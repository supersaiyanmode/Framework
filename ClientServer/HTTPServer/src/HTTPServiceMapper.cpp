#include "HTTPServiceMapper.h"

HTTPRequestProperty::HTTPRequestProperty(HTTPMethod m, const std::string& u): method(m), relativeUrl(u) {
    
}
bool HTTPRequestProperty::operator<(const HTTPRequestProperty& other) const {
    if (method < other.method)
        return true;
    if (method > other.method)
        return false;
    return relativeUrl < other.relativeUrl;
}

bool HTTPRequestProperty::operator == (const HTTPRequestProperty& other) const {
    return method == other.method && relativeUrl == other.relativeUrl;
}

HTTPServiceMapper::HTTPServiceMapper() {
    
}

HTTPServiceMapper::~HTTPServiceMapper() {
    
}

void HTTPServiceMapper::registerHandler(const HTTPRequestProperty& property, HTTPEndPointHandler* handler) {
    handlers[property] = handler;
}

void HTTPServiceMapper::unregisterHandler(const HTTPRequestProperty& property) {
    //TODO: remove by key.
}


HTTPEndPointHandler* HTTPServiceMapper::getHTTPEndPointHandler(HTTPMethod method, const std::string& url) const {
    HTTPRequestProperty prop(method, url);
    for (std::map<HTTPRequestProperty, HTTPEndPointHandler*>::const_iterator it=handlers.begin();
            it != handlers.end(); it++){
        if (it->first == prop)
            return it->second;
    }
    return 0;
}
