#include "ParamPlugin.h"
#include <iostream>
#include <sstream>


Param::Param(int a1, int a2) {
    a = a1;
    b = a2;
}

std::string Param::calc(int x) {
    std::stringstream ss;
    ss<<a<<"|"<<b<<" = " << x;
    return ss.str();    
}

bool dummy = PluginClient::getInstance().registerClass("ParamFactory", new PluginClassDefaultFactory<ParamFactory>());


void ParamFactory::setNum(int n, int m) {
    num1 = n;
    num2 = m;
}
    
Param* ParamFactory::createInstance() {
    return new Param(num1, num2);
}
