#include "Scheme.h"

void scheme::addAttributeName(std::string attributeName) {
	//adds an string to the end of the attributeNames vector
	attributeNames.push_back(attributeName);
	return;
}

void scheme::addAttributeNames(std::vector<std::string> allNames) {
	//replaces the attributeNames vector of strings with a new vector of strings 
	attributeNames = allNames;
	return;
}

std::string scheme::getAttributeName(int position) {
	//returns the string from attributeNames at position position
	return attributeNames[position];
}

std::vector<std::string> scheme::getAttributeNames() {
	//returns the attributeNames vector of strings
	return attributeNames;
}