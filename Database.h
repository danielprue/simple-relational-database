#ifndef DATABASE
#define DATABASE

#include "Relation.h"
#include "DatalogProgram.h"

#include <vector>
#include <fstream>

class database {
public:
	database() {};
	~database() { clear(); };

	void evaluateDatalog(datalogProgram datalog, int fileNumber);
	void evaluateSchemes(datalogProgram datalog);
	void evaluateFacts(datalogProgram datalog);
	std::string evaluateQuery(predicate* query);
	std::string evaluateRule(rule* rule);

	void clear();
private:
	std::vector<relation*> relations;
};

#endif