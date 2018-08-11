#include "Rule.h"

std::string rule::toString() {
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
	beforeColon = predicate;
}

void rule::addBCParameter(parameter* parameter) {
	beforeColon->addParameter(parameter);
	return;
}

void rule::addACParameter(parameter* parameter, int pos) {
	afterColon[pos]->addParameter(parameter);
	return;
}

void rule::addACPredicate(predicate* predicate) {
	afterColon.push_back(predicate);
	return;
}

predicate* rule::getBCPredicate() {
	return beforeColon;
}

std::vector<predicate*> rule::getACPredicates() {
	return afterColon;
}

predicate* rule::getACPredicate(int i) {
	return afterColon[i];
}

void rule::clear() {
	delete beforeColon;

	for (int i = 0; i < afterColon.size(); i++)
		delete afterColon[i];

	afterColon.clear();
	return;
}