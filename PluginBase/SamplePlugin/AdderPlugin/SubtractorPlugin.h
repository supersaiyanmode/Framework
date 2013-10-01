#ifndef SUBTRACTOR_PLUGIN_H
#define SUBTRACTOR_PLUGIN_H

#include "MathHelper.h"

class Subtractor : public MathHelper {
public:
    virtual int calc(int, int);
    
};

#endif