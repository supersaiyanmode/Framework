#ifndef MATH_HELPER_H
#define MATH_HELPER_H


#include "../../Plugin.h"

class MathHelper : public PluginClass {
public:
    virtual int calc(int, int) = 0;
};

#endif