#include <sstream>

#include "JSONParser.h"
#include "JSON.h"



const char *str = 
"{ \n"
"    \"columns\": [\"name\", \"age\", \"gender\", \"marks\"],\n"
"    \"entries\": [\n"
"        {\"name\": \"srivatsan\", \"age\":22, \"gender\":\"m\", \"marks\":100},\n"
"        {\"name\": \"ram\", \"age\":13, \"gender\":\"m\", \"marks\":10},\n"
"        {\"name\": \"iyer\", \"age\":29, \"gender\":\"m\", \"marks\":70}\n"
"    ],\n"
"    \"blah\":[1, 23, 45],\n"
"    \"key\":{}\n"
"}";


int main() {
    std::stringstream ssIn;
    ssIn<<str;
    std::cout<<"Parsing: "<<ssIn.str()<<std::endl<<std::endl;
    JSONParser j(ssIn.str());
	const JSONBase& root = *j.get();
    std::cout<<j.get()->str()<<std::endl;
	std::cout<<root["entries"][0]["name"].value<std::string>()<<std::endl;
    return 0;
}
