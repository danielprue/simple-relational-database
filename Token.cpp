#include "Token.h"

std::string token::getType() {
	//returns the type of the token
	return type;
}

std::string token::getValue() {
	//returns the value of the token
	return value;
}

int token::getLine() {
	//returns the line of the token
	return line;
}

std::string token::printToken() {
	//outputs the token as a string
	std::string temp;
	temp = "(" + type + "," + "\"" + value + "\"," + std::to_string(line) + ")";
	return temp;
}