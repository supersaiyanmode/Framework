#include "SubtractorPlugin.h"
#include <iostream>

bool dummy = PluginClient::getInstance().registerClass("Subtractor", new PluginClassDefaultFactory<Subtractor>());

int Subtractor::calc(int a, int b) {
    return a-b;
}