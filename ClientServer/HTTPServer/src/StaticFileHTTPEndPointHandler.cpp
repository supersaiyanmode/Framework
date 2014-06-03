#include <fstream>
#include <sstream>

#include "StaticFileHTTPEndPointHandler.h"

StaticFileHTTPEndPointHandler::StaticFileHTTPEndPointHandler(const std::string& p): filePath(p) {
    
}

HTTPResponse StaticFileHTTPEndPointHandler::handle(const HTTPRequest& request) {
    std::ifstream infile;
    infile.open(filePath.c_str());
    
    std::stringstream buffer;
    buffer <<infile.rdbuf();
    
    HTTPResponse response;
    response.write(buffer.str());
    response.setContentType("text/plain");
    return response;
}
