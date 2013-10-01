#ifndef DYNAMIC_HTTP_ENDPOINT_HANDLER
#define DYNAMIC_HTTP_ENDPOINT_HANDLER

#include "HTTPEndPointHandler.h"

class StaticFileHTTPEndPointHandler : public HTTPEndPointHandler {
    std::string filePath;
public:
    StaticFileHTTPEndPointHandler(const std::string&);
    virtual HTTPResponse handle(const HTTPRequest&);
};

#endif