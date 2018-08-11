#ifndef RULE
#define RULE

#include "Predicate.h"

class rule {
public:
	rule() {};
	~rule() { clear(); };

	std::string toString();
	void addBCPredicate(predicate* predicate);
	void addBCParameter(parameter* parameter);
	void addACPredicate(predicate* predicate);
	void addACParameter(parameter* parameter, int pos);
	predicate* getBCPredicate();
	std::vector<predicate*> getACPredicates();
	predicate* getACPredicate(int i);
	void clear();

private:
	predicate* beforeColon;
	std::vector<predicate*> afterColon;
};

#endif