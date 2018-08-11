#ifndef DATALOGPROGRAM
#define DATALOGPROGRAM

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

#include <vector>
#include <string>
#include <algorithm>

class datalogProgram {
public:
	datalogProgram() {};
	~datalogProgram() {};

	std::string toString(token* error);
	void addScheme(predicate* scheme);
	void addFact(predicate* fact);
	void addRule(rule* rule);
	void addQuery(predicate* query);
	void addDomain(std::string string);

	void addSchemeParameter(parameter* parameter, int pos);
	void addFactParameter(parameter* parameter, int pos);
	void addBCRulePredicate(predicate* predicate, int pos);
	void addBCRuleParameter(parameter* parameter, int pos);
	void addACRulePredicate(predicate* predicate, int pos);
	void addACRuleParameter(parameter* parameter, int rulePos, int predPos);
	void addQueryParameter(parameter* parameter, int pos);

	predicate* getScheme(int position);
	predicate* getFact(int position);
	rule* getRule(int position);
	predicate* getQuery(int position);
	int getSchemeSize();
	int getFactSize();
	int getRuleSize();
	int getQuerySize();

	void clear();

private:
	std::vector<predicate*> schemes;
	std::vector<predicate*> facts;
	std::vector<rule*> rules;
	std::vector<predicate*> queries;

	std::vector<std::string> domain;
};

#endif