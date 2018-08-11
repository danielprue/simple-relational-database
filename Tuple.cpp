#include "Tuple.h"

void tuple::addAttribute(std::string attribute) {
	attributes.push_back(attribute);
	return;
}

void tuple::addAttributes(std::vector<std::string> newAttributes) {
	attributes = newAttributes;
	return;
}

std::string tuple::getAttribute(int position) {
	return attributes[position];
}

std::vector<std::string> tuple::getAttributes() {
	return attributes;
}