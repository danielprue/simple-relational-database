#include "DatalogProgram.h"

std::string datalogProgram::toString(token* error) {
	std::string temp;

	//check for error message here
	if (error != nullptr) {
		temp += "Failure!\n  ";
		temp += error->printToken();
		return temp;
	}
	else
		temp += "Success!\n";

	temp += "Schemes(";
	temp += std::to_string(schemes.size());
	temp += "):\n";

	for (int i = 0; i < schemes.size(); i++) {
		temp += "  ";
		temp += schemes[i]->toString();
		temp += "\n";
	}

	temp += "Facts(";
	temp += std::to_string(facts.size());
	temp += "):\n";

	for (int i = 0; i < facts.size(); i++) {
		temp += "  ";
		temp += facts[i]->toString();
		temp += "\n";
	}

	temp += "Rules(";
	temp += std::to_string(rules.size());
	temp += "):\n";

	for (int i = 0; i < rules.size(); i++) {
		temp += "  ";
		temp += rules[i]->toString();
		temp += "\n";
	}

	temp += "Queries(";
	temp += std::to_string(queries.size());
	temp += "):\n";

	for (int i = 0; i < queries.size(); i++) {
		temp += "  ";
		temp += queries[i]->toString();
		temp += "\n";
	}

	std::sort(domain.begin(), domain.end());
	temp += "Domain(";
	temp += std::to_string(domain.size());
	temp += "):";

	for (int i = 0; i < domain.size(); i++) {
		temp += "\n  ";
		temp += domain[i];
	}

	return temp;
}

void datalogProgram::addScheme(predicate* scheme) {

	schemes.push_back(scheme);
	return;
}

void datalogProgram::addFact(predicate* fact) {
	facts.push_back(fact);
	return;
}

void datalogProgram::addRule(rule* rule) {
	rules.push_back(rule);
	return;
}

void datalogProgram::addQuery(predicate* query) {
	queries.push_back(query);
	return;
}

void datalogProgram::addDomain(std::string string) {
	if (std::find(domain.begin(), domain.end(), string) == domain.end())
		domain.push_back(string);
	return;
}

void datalogProgram::addSchemeParameter(parameter* parameter, int pos) {
	schemes[pos]->addParameter(parameter);
	return;
}

void datalogProgram::addFactParameter(parameter* parameter, int pos) {
	facts[pos]->addParameter(parameter);
	return;
}

void datalogProgram::addBCRulePredicate(predicate* predicate, int pos) {
	rules[pos]->addBCPredicate(predicate);
}

void datalogProgram::addBCRuleParameter(parameter* parameter, int pos) {
	rules[pos]->addBCParameter(parameter);
}

void datalogProgram::addACRulePredicate(predicate* predicate, int pos) {
	rules[pos]->addACPredicate(predicate);
	return;
}

void datalogProgram::addACRuleParameter(parameter* parameter, int rulePos, int predPos) {
	rules[rulePos]->addACParameter(parameter, predPos);
	return;
}

void datalogProgram::addQueryParameter(parameter* parameter, int pos) {
	queries[pos]->addParameter(parameter);
	return;
}

predicate* datalogProgram::getScheme(int position) {
	return schemes[position];
}

predicate* datalogProgram::getFact(int position) {
	return facts[position];
}

rule* datalogProgram::getRule(int position) {
	return rules[position];
}

predicate* datalogProgram::getQuery(int position) {
	return queries[position];
}

int datalogProgram::getSchemeSize() {
	return schemes.size();
}

int datalogProgram::getFactSize() {
	return facts.size();
}

int datalogProgram::getRuleSize() {
	return rules.size();
}

int datalogProgram::getQuerySize() {
	return queries.size();
}

void datalogProgram::clear() {
	for (int i = 0; i < schemes.size(); i++)
		//if(schemes[i] != nullptr)
			delete schemes[i];

	for (int i = 0; i < facts.size(); i++)
		//if(facts[i] != nullptr)
			delete facts[i];

	for (int i = 0; i < rules.size(); i++)
		//if(rules[i] != nullptr)
			delete rules[i];

	for (int i = 0; i < queries.size(); i++)
		//if(queries[i] != nullptr)
			delete queries[i];

	schemes.clear();
	facts.clear();
	rules.clear();
	queries.clear();
	domain.clear();
}