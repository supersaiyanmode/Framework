#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

#include "HTTPParser.h"
#include "IO/Structure/Line/LineReader.h"
#include "IO/Structure/Block/BlockReader.h"
#include "StringUtils.h"

std::string HTTPParser::decodeURIComponent(std::string in) {
    return in;
}

std::map<std::string, std::string> HTTPParser::parseQueryString(std::string queryString) {
    std::vector<std::string> paramPairs = StringUtils::splitAny(queryString, "&");
    std::map<std::string, std::string> result;
    for (std::vector<std::string>::iterator it=paramPairs.begin(); it!= paramPairs.end(); it++) {
        if (StringUtils::trim(*it).length() == 0)
            continue;

        //Split on '='
        // TODO: Change below to StringUtils::partition.
        std::vector<std::string> parts = StringUtils::splitAny(*it, "=");
        if (parts.size() != 2)
            continue;
        result[parts[0]] = decodeURIComponent(parts[1]);
    }
    return result;
}

HTTPParser::HTTPParser(Connection& c) : connection(c){
    
}

bool HTTPParser::parse() {
    HTTPMethod method;
    HTTPEndPoint url;
    std::string version;
    std::map<std::string, std::string> queryMap;
    std::map<std::string, std::string> headers;
    std::string body;
    
    LineReader lr(connection, "\r\n");
    
    std::string line = lr.readLine();
    
    if (!line.size())
        return false;
    
    std::vector<std::string> parts(StringUtils::splitAny(line, " "));
    parts[0] = StringUtils::toUpper(parts[0]);
    
    if (parts.size() < 2 || parts.size() > 3) {
        errorMessage = "Invalid Request Line.";
        return false;
    }
    
    if (parts[0] == "GET")
        method = GET;
    else if (parts[0] == "POST")
        method = POST;
    else {
        errorMessage = "Invalid HTTP Method.";
        return false;
    }
    
    url = StringUtils::trim(parts[1]);
    if (url.length() <= 0) {
        errorMessage = "Invalid URL.";
        return false;
    }
    
    //GET Parameters
    std::vector<std::string> urlParts(StringUtils::splitAny(url, "?"));
    if (urlParts.size() > 1) {
        url = urlParts[0];
        queryMap = parseQueryString(urlParts[1]);
    }
    
    if (parts.size() == 3) {
        version = parts[2];
    }

    while ((line=lr.readLine()) != "") {
        std::vector<std::string> parts(StringUtils::splitAny(line, ":"));
        headers[StringUtils::toLower(StringUtils::trim(parts[0]))] = StringUtils::trim(parts[1]);
    }
    
    if (headers.find("content-length") != headers.end()) {
        int length;
        std::stringstream ssLength(headers["content-length"]);
        if (!(ssLength>>length)) {
            std::cout<<"Invalid header: Content-Length\n";
            return false;
        }
        
        if (length) {
            BlockReader br(connection, lr.getBackBuffer());
            body = br.read(length);
            br.close();
        }
    }
    
    request = HTTPRequest(method, url, version, queryMap, headers, body);
    return true;
}
