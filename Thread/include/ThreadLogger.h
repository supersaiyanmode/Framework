#ifndef THREAD_LOGGER_H
#define THREAD_LOGGER_H
#include <string>
#include <sstream>

void threadDisplay(const std::string&);

#define tlog(X) do{ \
    std::stringstream ss; \
    ss<<X; \
    threadDisplay(ss.str()); \
}while (0)

#endif
