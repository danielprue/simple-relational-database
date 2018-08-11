#ifndef RELATION
#define RELATION

#include "Tuple.h"
#include "Scheme.h"

#include <vector>
#include <algorithm>
#include <functional>

class relation {
public:
	relation(std::string name, scheme* scheme, std::vector<tuple*> tuples) : name(name), rScheme(scheme), tuples(tuples) {};
	~relation() { clear(); };

	std::string getName();
	tuple* getTuple(int position);
	std::vector<tuple*> getTuples();
	int getTuplesSize();
	scheme* getScheme();
	void addTuple(tuple* newTuple);

	relation* selectByValue(int position, std::string value);
	relation* selectByComparison(int position1, int position2);
	relation* project(std::vector<int> positions);
	relation* rename(scheme* scheme);
	relation* unionCombine(relation* first, relation* second);
	relation* joinCombine(relation* first, relation* second);

	relation* removeDups();
	void sortTuples();

	bool compareTuples(const std::vector<std::string> &V1, const std::vector<std::string> &V2, int pos);
	void clear();
private:
	std::string name;
	scheme* rScheme;
	std::vector<tuple*> tuples;
};

#endif
