#include <iostream>

#include "Plugin.h"

/*
    GeneralPluginException
*/
GeneralPluginException::GeneralPluginException(const std::string &m) : msg(m){
    
}

GeneralPluginException::~GeneralPluginException() throw() {
    
}

const char* GeneralPluginException::what() const throw() {
    return msg.c_str();
}



/*
    Platform_PluginHandle
*/



#if defined(PLATFORM_LINUX) || defined(PLATFORM_MAC)
#include <dlfcn.h>

namespace {
    PLUGIN_HANDLE loadPlugin(const char* path) {
        void* lib = dlopen(path,RTLD_LAZY);
        if (!lib) {
            std::cout<<"Unable to load plugin."<<std::endl;
            throw GeneralPluginException("Unable to load library");
        }
        return lib;
    }
    
    void* loadFunction(PLUGIN_HANDLE handle, const char* funcName) {
        void * func = dlsym(handle, funcName);
        if (!func) {
            std::cout<<"Unable to lookup function name: "<<funcName<<std::endl;
            throw GeneralPluginException("Unable to lookup function name.");
        }
        return func;
    }
    
    void unloadFunction(PLUGIN_HANDLE handle) {
        dlclose(handle);
    }
}
#endif


Platform_PluginHandle::Platform_PluginHandle(const std::string& path):filePath(path) {
    handle = loadPlugin(path.c_str());
    loaded = true;
}

Platform_PluginHandle::~Platform_PluginHandle() {
    unloadFunction(handle);
}

void* Platform_PluginHandle::load(const std::string& functionName) const {
    return loadFunction(handle, functionName.c_str());
}



/*
    Dynamic class Instantiation
*/

extern "C" {    
    PLUGIN_DLL_EXPORT PluginClass* createInstance(const char* className) {
        const PluginClient& pc = PluginClient::getInstance();
        PluginClassFactory* factory = pc.getFactory(className);
        if (!factory) {
            std::cout<<"Unable to retrieve factory for type: " <<className<<std::endl;
            return NULL;
        }
        return factory->createInstance();
    }
    
    PLUGIN_DLL_EXPORT void destroyInstance(PluginClass* instance) {
        delete instance;
    }
}

