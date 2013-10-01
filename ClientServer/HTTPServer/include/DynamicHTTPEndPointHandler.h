#ifndef DYNAMIC_HTTP_ENDPOINT_HANDLER
#define DYNAMIC_HTTP_ENDPOINT_HANDLER

#include "HTTPEndPointHandler.h"

class DynamicHTTPEndPointHandler : public HTTPEndPointHandler {
public:
    virtual HTTPResponse handle(const HTTPRequest&);
};

#endif