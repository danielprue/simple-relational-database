#include "Rule.h"

std::string rule::toString() {
	//output a rule as a string
	std::string temp;
	temp += beforeColon->toString();
	temp += " :- ";

	for (int i = 0; i < afterColon.size(); i++) {
		temp += afterColon[i]->toString();
		if (i != afterColon.size() - 1)
			temp += ",";
		else
			temp += ".";
	}

	return temp;
}

void rule::addBCPredicate(predicate* predicate) {
	//add a BCPredicate to the rule
	beforeColon = predicate;
	return;
}

void rule::addBCParameter(parameter* parameter) {
	//add a parameter to the end of beforeColon
	beforeColon->addParameter(parameter);
	return;
}

void rule::addACParameter(parameter* parameter, int pos) {
	//add a parameter to the end of the predicate in position pos of the afterColon vector
	afterColon[pos]->addParameter(parameter);
	return;
}

void rule::addACPredicate(predicate* predicate) {
	//add a predicate to the end of the afterColon vector of predicates
	afterColon.push_back(predicate);
	return;
}

predicate* rule::getBCPredicate() {
	//return the beforeColon predicate
	return beforeColon;
}

std::vector<predicate*> rule::getACPredicates() {
	//return the afterColon vector of predicates
	return afterColon;
}

predicate* rule::getACPredicate(int i) {
	//return the predicate in the position i of the afterColon vector of predicates
	return afterColon[i];
}

void rule::clear() {
	//cleanup function
	delete beforeColon;

	for (int i = 0; i < afterColon.size(); i++)
		delete afterColon[i];

	afterColon.clear();
	return;
}