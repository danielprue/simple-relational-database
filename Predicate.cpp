#include "Predicate.h"

int predicate::getParameterSize() {
	//return the size of the parameter vector
	return parameters.size();
}

parameter* predicate::getParameter(int position) {
	//return the parameter at position position in the parameter vector
	return parameters[position];
}

std::string predicate::toString() {
	//function turns predicate into a string
	std::string temp;

	temp += ID;
	temp += "(";

	for (int i = 0; i < parameters.size(); i++) {

		temp += parameters[i]->getValue();
		if (i != parameters.size() - 1)
			temp += ",";
	}

	temp += ")";

	if (type == "FACTS")
		temp += ".";
	else if (type == "QUERY")
		temp += "?";

	return temp;
}

void predicate::addParameter(parameter* parameter) {
	//adds a parameter to the end of the parameter vector
	parameters.push_back(parameter);
	return;
}

std::string predicate::getType() {
	//returns predicate's type
	return type;
}

std::string predicate::getID() {
	//returns predicate's ID
	return ID;
}

void predicate::clear() {
	//cleanup function
	for (int i = 0; i < parameters.size(); i++) {
		if(parameters[i] != nullptr)
			delete parameters[i];
	}

	parameters.clear();
	return;
}