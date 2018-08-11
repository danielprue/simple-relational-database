#ifndef TUPLE
#define TUPLE

#include <vector>

class tuple {
public:
	tuple() {};
	~tuple() {};

	void addAttribute(std::string attribute);
	void addAttributes(std::vector<std::string> newAttributes);
	std::string getAttribute(int position);
	std::vector<std::string> getAttributes();
private:
	std::vector<std::string> attributes;
};

#endif
