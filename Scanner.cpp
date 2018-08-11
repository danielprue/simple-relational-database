#include "Scanner.h"

//set infile
void scanner::setInfile(std::string fileName) {
	infile.open(fileName);
	return;
}

//start loop to addToken
void scanner::scan() {
	while (infile.peek() != EOF) {
		if (infile.peek() == '\n') {
			infile.get();
			currentLine++;
		}
		else
			addToken();
	}
	currentLine++;
	list.push_back(new token("EOF", "", currentLine));
}

//take next character and decide what that token it is
//add token to the list
void scanner::addToken() {
	//take next char from file
	char c = infile.get();

	//initializations
	std::string temp = "";
	char a;
	int tempLine;
	bool foundEnd;

	//switch to determine token type
	switch (c) {

		//White space: ignore
	case ' ':
		break;

		//Simple case: COMMA
	case ',':
		list.push_back(new token("COMMA", ",", currentLine));
		break;

		//Simple case: PERIOD
	case '.':
		list.push_back(new token("PERIOD", ".", currentLine));
		break;

		//Simple case: Q_MARK
	case '?':
		list.push_back(new token("Q_MARK", "?", currentLine));
		break;

		//Simple case: LEFT_PAREN
	case '(':
		list.push_back(new token("LEFT_PAREN", "(", currentLine));
		break;

		//Simple case: RIGHT_PAREN
	case ')':
		list.push_back(new token("RIGHT_PAREN", ")", currentLine));
		break;

		//Check here for COLON or COLON_DASH
	case ':':
		//COLON_DASH
		if (infile.peek() == '-') {
			infile.get();
			list.push_back(new token("COLON_DASH", ":-", currentLine));
		}
		//COLON
		else
			list.push_back(new token("COLON", ":", currentLine));
		break;

		//Simple case: MULTIPLY
	case '*':
		list.push_back(new token("MULTIPLY", "*", currentLine));
		break;

		//Simple case: ADD
	case '+':
		list.push_back(new token("ADD", "+", currentLine));
		break;

		//STRING: search for end of string
		//UNDEFINED: end of string does not exist
	case '\'':
		temp.push_back(c);
		foundEnd = false;
		//char a;
		tempLine = currentLine;

		while (!foundEnd && infile.peek() != EOF) {
			a = infile.get();
			if (a == '\n')
				currentLine++;
			else if (a == '\'' && infile.peek() != '\'')
				foundEnd = true;
			else if (a == '\'' && infile.peek() == '\'') {
				temp.push_back(a);
				a = infile.get();
			}
			temp.push_back(a);
		}
		if (foundEnd)
			list.push_back(new token("STRING", temp, tempLine));
		else {
			temp.push_back('\n');
			list.push_back(new token("UNDEFINED", temp, tempLine));
		}
		break;

	case '\t':
		break;

		//COMMENT: either a line comment # or a block comment #||#
		//UNDEFINED: block comment beginning with no end
	case '#':
		//block comment
		if (infile.peek() == '|') {
			temp.push_back(c);
			a = infile.get();
			foundEnd = false;
			tempLine = currentLine;

			temp.push_back(a);
			while (!foundEnd && infile.peek() != EOF) {
				a = infile.get();
				if (a == '\n')
					currentLine++;
				else if (a == '|' && infile.peek() == '#') {
					foundEnd = true;
					temp.push_back(a);
					a = infile.get();
				}
				temp.push_back(a);
			}
			if (foundEnd)
				list.push_back(new token("COMMENT", temp, tempLine));
			else
				list.push_back(new token("UNDEFINED", temp, tempLine));
		}
		//line comments
		else {
			temp.push_back(c);
			//char a;
			while (infile.peek() != '\n') {
				a = infile.get();
				temp.push_back(a);
			}
			list.push_back(new token("COMMENT", temp, currentLine));
		}
		break;

		//QUERIES, SCHEMES, FACTS, RULES, ID, and UNDEFINED tests
	default:
		temp.push_back(c);
		//char a;
		bool ID = false;
		if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')) {
			while ((infile.peek() <= 'z' && infile.peek() >= 'a') || (infile.peek() <= 'Z' && infile.peek() >= 'A') || (infile.peek() <= '9' && infile.peek() >= '0')) {
				a = infile.get();
				temp.push_back(a);
			}
			ID = true;
		}
		if (temp == "Schemes")
			list.push_back(new token("SCHEMES", temp, currentLine));
		else if (temp == "Facts")
			list.push_back(new token("FACTS", temp, currentLine));
		else if (temp == "Rules")
			list.push_back(new token("RULES", temp, currentLine));
		else if (temp == "Queries")
			list.push_back(new token("QUERIES", temp, currentLine));
		else if (ID)
			list.push_back(new token("ID", temp, currentLine));
		else
			list.push_back(new token("UNDEFINED", temp, currentLine));
		break;
	}
}

//Output the tokens
void scanner::printList(std::string fileName) {
	std::ofstream outfile;
	outfile.open(fileName);

	for (int i = 0; i < list.size(); i++) {
		outfile << list[i]->printToken();
		outfile << "\n";
	}
	outfile << "Total Tokens = " << std::to_string(list.size());
}

void scanner::clearList() {
	for (int i = 0; i < list.size(); i++)
		delete list[i];
	list.clear();
	return;
}

std::vector<token*> scanner::getList() {
	return list;
}