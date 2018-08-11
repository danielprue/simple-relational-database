#ifndef PARAMETER
#define PARAMETER

#include <string>

class parameter {
public:
	parameter(std::string type, std::string value) : type(type), value(value) {};
	~parameter() {};

	std::string getType();
	std::string getValue();

private:
	std::string type;
	std::string value;
};

#endif