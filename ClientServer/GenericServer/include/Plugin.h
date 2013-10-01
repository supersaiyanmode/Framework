#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#define PLUGIN_DLL_EXPORT __attribute__((visibility("default")))

#if defined(_WIN32)
    #define PLATFORM_WINDOWS
    #define PLUGIN_HANDLE 
#elif defined (__linux) || defined(__linux__)
    #define PLATFORM_LINUX
    #define PLUGIN_HANDLE void*
#elif defined (__APPLE__)
    #define PLATFORM_MAC
    #define PLUGIN_HANDLE void*
#endif

#include <string>
#include <exception>
#include <iostream>
#include <map>

class GeneralPluginException : public std::exception {
protected:
    std::string msg;
public:
    GeneralPluginException(const std::string &);
    virtual ~GeneralPluginException() throw();
    
    virtual const char* what() const throw();
};


/* The class that serves as the base class for all dynamic classes. */
class PluginClass {
public:
    virtual ~PluginClass() {}
};

class PluginClassFactory {
public:
    virtual PluginClass* createInstance() = 0;
    virtual ~PluginClassFactory() {}
};

/* Platform specific Plugin Loader */
class Platform_PluginHandle {
    PLUGIN_HANDLE handle;
    std::string filePath;
    bool loaded;
public:
    Platform_PluginHandle(const std::string&);
    virtual ~Platform_PluginHandle();
    
    void* load(const std::string&) const;
};


/* Class for loading classes dynamically from Shared objects. */
class Plugin {
    Platform_PluginHandle handle;
    std::string m_version;
public:
    Plugin(const std::string& filePath) : handle(filePath) {
        
    }

    ~Plugin(){}
    
    
    template <typename T>
    T* createInstance(const std::string& name) const{
        typedef T* (*CreateInstanceFunction)(const char*);
        CreateInstanceFunction createFn;
        //CreateInstanceFunction createFn = (CreateInstanceFunction)handle.load("createInstance");
        *reinterpret_cast<void**>(&createFn) = handle.load("createInstance");
        if (!createFn) {
            throw GeneralPluginException("Unable to get Create function.");
        }
        return createFn(name.c_str());
    }
    
    void destroyInstance(PluginClass* instance) const {
        typedef void* (*DestroyInstanceFunction)(PluginClass*);
        DestroyInstanceFunction destroyFn;
        //DestroyInstanceFunction destroyFn = (DestroyInstanceFunction)handle.load("destroyInstance");
        *reinterpret_cast<void**>(&destroyFn) = handle.load("destroyInstance");
        if (!destroyFn) {
            throw GeneralPluginException("Unable to get Destroy function.");
        }
        destroyFn(instance);
    }
    
    //std::string version() const;
};


template <typename T>
class PluginClassDefaultFactory : public PluginClassFactory {
public:
    T* createInstance() {
        return new T();
    }
};


typedef PluginClass* (*FactoryInstantiator)();

class PluginClient {
    std::map<std::string, PluginClassFactory*> registeredFactories;
    
public:
    bool registerClass(const std::string& name, PluginClassFactory* factory) {
        registeredFactories[name] = factory;
        return true;
    }

    void unregisterClass(const std::string&) {}

    PluginClassFactory* getFactory(const std::string& className) const {
        for (std::map<std::string, PluginClassFactory*>::const_iterator it = registeredFactories.begin();
                    it != registeredFactories.end(); it++) {
            if (it->first == className)
                return it->second;
        }
        return NULL;
    }
    
    static inline PluginClient& getInstance() {
        static PluginClient *pc = NULL;
        if (!pc)
            pc = new PluginClient();
        return *pc;
    }
};


extern "C" {    
    PLUGIN_DLL_EXPORT PluginClass* createInstance(const char* className);
    
    PLUGIN_DLL_EXPORT void destroyInstance(PluginClass* instance);
}



#endif
