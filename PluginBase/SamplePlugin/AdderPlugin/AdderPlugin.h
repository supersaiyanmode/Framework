#ifndef ADDER_PLUGIN_H
#define ADDER_PLUGIN_H

#include "MathHelper.h"

class Temp {
public:
    int num;
};

class Adder : public MathHelper {
public:
    virtual int calc(int, int);
    virtual Temp* getTemp();
    virtual ~Adder() {}
};



#endif