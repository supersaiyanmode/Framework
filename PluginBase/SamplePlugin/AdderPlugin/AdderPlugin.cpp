#include "AdderPlugin.h"
#include <iostream>

bool dummy = PluginClient::getInstance().registerClass("Adder", new PluginClassDefaultFactory<Adder>());

int Adder::calc(int a, int b) {
    return a+b;
}


Temp* Adder::getTemp() {
    Temp* t = new Temp();
    t->num = 4;
    return t;
}