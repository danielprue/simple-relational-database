#ifndef PARSER
#define PARSER

#include "Token.h"
#include "DatalogProgram.h"

#include <vector>
#include <fstream>

class parser {
public:
	parser(std::vector<token*> dataLog) :dataLog(dataLog), error(nullptr) {};
	~parser() { clear(); };

	void parseDatalogProgram();
	bool parseSchemeList();
	bool parseFactList();
	bool parseRuleList();
	bool parseQueryList();
	bool parseScheme();
	bool parseFact();
	bool parseRule();
	bool parseQuery();
	bool parseHeadPredicate();
	bool parsePredicate();
	bool parsePredicateList();
	bool parseParameterList();
	bool parseStringList();
	bool parseIDList();
	bool parseParameter();
	bool parseExpression();
	bool parseOperators();

	bool match(std::string check);
	void printOutput(std::string outputFile);
	std::string makeExpression(std::string soFar);
	void removeComments();
	void clear();
	datalogProgram getDatalogProgram();

private:
	std::vector<token*> dataLog;
	int parsePosition;
	int expressionIncriment;
	datalogProgram output;
	token* error;
};

#endif
