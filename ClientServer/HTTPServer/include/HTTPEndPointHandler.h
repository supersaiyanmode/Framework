#ifndef HTTP_END_POINT_HANDLER_H
#define HTTP_END_POINT_HANDLER_H

#include "HTTPRequest.h"
#include "HTTPResponse.h"

class HTTPEndPointHandler {
public:
    virtual HTTPResponse handle(const HTTPRequest&) = 0;
};

#endif
