#ifndef SCANNER
#define SCANNER

#include "Token.h"
#include <iostream>
#include <fstream>
#include <vector>

class scanner {
public:
	scanner() : currentLine(1) {};
	~scanner() { clearList(); };

	void scan();
	void addToken();
	void setInfile(std::string fileName);
	void printList(std::string fileName);
	void clearList();

	std::vector<token*> getList();

private:
	std::ifstream infile;
	std::vector<token*> list;
	int currentLine;
};

#endif