#ifndef SCHEME
#define SCHEME

#include <string>
#include <vector>

class scheme {
public:
	scheme() {};
	~scheme() {};

	void addAttributeName(std::string attributeName);
	void addAttributeNames(std::vector<std::string> allNames);
	std::string getAttributeName(int position);
	std::vector<std::string> getAttributeNames();
private:
	std::vector<std::string> attributeNames;
};

#endif
