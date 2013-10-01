#include "ThreadPoolHTTPServer.h"
#include "Plugin.h"
#include "ConfigurationFileParser.h"
#include "ThreadPoolTCPServer.h"
#include "HTTPParser.h"

ThreadPoolHTTPServer::ThreadPoolHTTPServer(int p, int w, int q): ThreadPoolTCPServer(p,this,w,q),
                    port(p), workers(w), queueSize(q),
                    configuration("http.config") {
}

ThreadPoolHTTPServer::~ThreadPoolHTTPServer() {
    ThreadPoolHTTPServer::shutdown(); //Will ignore if already shutdown.
}

void ThreadPoolHTTPServer::registerHandler(const HTTPRequestProperty& prop, HTTPEndPointHandler* handler) {
    HTTPServiceMapper::registerHandler(prop, handler);
}

void ThreadPoolHTTPServer::unregisterHandler(const HTTPRequestProperty& prop) {
    HTTPServiceMapper::unregisterHandler(prop);
}

void ThreadPoolHTTPServer::initialise() {
    ThreadPoolTCPServer::initialise();
    std::cout<<"HTTP Server initialised, and listening on port: "<<port<<std::endl;
}

void ThreadPoolHTTPServer::onIncomingConnection(Connection c){
    std::cout<<"Got an incoming connection from: "<<c.remoteAddressStr()<<std::endl;
    HTTPParser parser(c);
    if (!parser.parse()) {
        std::cout<<"Invalid HTTP Request.\n";
        c.write(HTTPResponse(400, "Bad Request").str());
        c.close();
        return;
    }
    c.closeReading();
    HTTPRequest request(parser.getRequest());
    
    HTTPEndPointHandler* handler = HTTPServiceMapper::getHTTPEndPointHandler(request.method(), request.url());
    
    if (!handler) {
        std::cout<<"URL Not Found.\n";
        c.write(HTTPResponse(404, "Not Found").str());
        c.close();
        return;
    }
    
    HTTPResponse response;
    try {
        response = handler->handle(request);
    } catch (...) {
        response = HTTPResponse(500, "Internal Server Error.");
    }
    
    c.write(response.str());
    c.close();
}
