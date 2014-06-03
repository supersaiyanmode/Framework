#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

#include <exception>
#include <string>

class JSONException : public std::exception {
public:
	JSONException(std::string m) : msg(m) {}
	
	~JSONException() throw() {}
	
	const char* what() const throw() {
		return msg.c_str();
	}

private:
	std::string msg;
};

#endif
