#ifndef PARAM_PLUGIN_H
#define PARAM_PLUGIN_H

#include <string>
#include "../../Plugin.h"

class Param {
    int a,b;
public:
    Param(int a1, int b1);
    virtual std::string calc(int);
    
};

class ParamFactory : public PluginClass {
    int num1, num2;
public:
    virtual void setNum(int n, int m);
    
    virtual Param* createInstance();
};

#endif
