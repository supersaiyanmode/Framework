#include "ThreadPoolHTTPServer.h"
#include "StaticFileHTTPEndPointHandler.h"

int main() {
    StaticFileHTTPEndPointHandler handler("main.cpp");
    
    ThreadPoolHTTPServer server(9001);
    server.initialise();
    HTTPRequestProperty prop(GET, "/test");
    server.registerHandler(prop, &handler);
    server.serve();
}
