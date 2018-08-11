#include "Token.h"

std::string token::getType() {
	return type;
}

std::string token::getValue() {
	return value;
}

int token::getLine() {
	return line;
}

std::string token::printToken() {
	std::string temp;
	temp = "(" + type + "," + "\"" + value + "\"," + std::to_string(line) + ")";
	return temp;
}