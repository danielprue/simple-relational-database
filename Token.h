#ifndef TOKEN
#define TOKEN

#include <string>

class token {
public:
	token(std::string type, std::string value, int line) : type(type), value(value), line(line) {};
	~token() {};

	std::string getType();
	std::string getValue();
	int getLine();
	std::string printToken();

private:
	std::string type;
	std::string value;
	int line;
};

#endif 