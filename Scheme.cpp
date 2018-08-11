#include "Scheme.h"

void scheme::addAttributeName(std::string attributeName) {
	attributeNames.push_back(attributeName);
	return;
}

void scheme::addAttributeNames(std::vector<std::string> allNames) {
	attributeNames = allNames;
	return;
}

std::string scheme::getAttributeName(int position) {
	return attributeNames[position];
}

std::vector<std::string> scheme::getAttributeNames() {
	return attributeNames;
}