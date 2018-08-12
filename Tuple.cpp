#include "Tuple.h"

void tuple::addAttribute(std::string attribute) {
	//adds a string to the end of the vector of attributes vector of strings
	attributes.push_back(attribute);
	return;
}

void tuple::addAttributes(std::vector<std::string> newAttributes) {
	//replaces the attributes vector of strings with a new vector of strings
	attributes = newAttributes;
	return;
}

std::string tuple::getAttribute(int position) {
	//returns the string at position position in the attributes vector of strings
	return attributes[position];
}

std::vector<std::string> tuple::getAttributes() {
	//returns the attributes vector of strings
	return attributes;
}