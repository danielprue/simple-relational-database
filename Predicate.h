#ifndef PREDICATE
#define PREDICATE

#include "Parameter.h"

#include <vector>

class predicate {
public:
	predicate(std::string type, std::string ID) : type(type), ID(ID) {};
	~predicate() { clear(); };

	int getParameterSize();
	parameter* getParameter(int position);
	std::string toString();
	std::string getType();
	std::string getID();
	void addParameter(parameter* parameter);
	void clear();

private:
	std::string type;
	std::string ID;
	std::vector<parameter*> parameters;
};

#endif