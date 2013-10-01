#ifdef ADDER_TEST

#include <iostream>

#include "SamplePlugin/AdderPlugin/AdderPlugin.h"
#include "SamplePlugin/AdderPlugin/SubtractorPlugin.h"
#include "SamplePlugin/ParamPlugin/ParamPlugin.h"
#include "Plugin.h"


int main() {
    Plugin pAdder("SamplePlugin/AdderPlugin/add.so");
    Plugin pSubtractor("SamplePlugin/AdderPlugin/subtract.so");
    Plugin pParam("SamplePlugin/ParamPlugin/param.so");
    
    MathHelper *a = pAdder.createInstance<Adder>("Adder");
    std::cout<<a->calc(5,3)<<std::endl;
    Adder *aa = (Adder*)a;
    std::cout<<aa->getTemp()->num<<std::endl;
    pAdder.destroyInstance(a);
    

    MathHelper *a1 = pSubtractor.createInstance<Subtractor>("Subtractor");
    std::cout<<a1->calc(5,3)<<std::endl;
    pSubtractor.destroyInstance(a1);

    std::cout<<"Got1\n";
    ParamFactory *a2 = pParam.createInstance<ParamFactory>("ParamFactory");
    a2->setNum(4,5);
    Param* p3 = a2->createInstance();
    std::cout<<p3->calc(79)<<std::endl;
    delete p3;
    pParam.destroyInstance(a2);
    
    return 0;
}

#endif