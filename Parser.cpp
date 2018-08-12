#include "Parser.h"

void parser::parseDatalogProgram() {
	//remove comments from dataLog before parsing
	removeComments();

	//vocabulary
	//if an input doesn't match the vocabulary, throw and exception
	try {
		if (!match("SCHEMES"))
			throw parsePosition;
		if (!match("COLON"))
			throw parsePosition;
		if (!parseScheme())
			throw parsePosition;
		if (!parseSchemeList())
			throw parsePosition;
		if (!match("FACTS"))
			throw parsePosition;
		if (!match("COLON"))
			throw parsePosition;
		if (!parseFactList())
			throw parsePosition;
		if (!match("RULES"))
			throw parsePosition;
		if (!match("COLON"))
			throw parsePosition;
		if (!parseRuleList())
			throw parsePosition;
		if (!match("QUERIES"))
			throw parsePosition;
		if (!match("COLON"))
			throw parsePosition;
		if (!parseQuery())
			throw parsePosition;
		if (!parseQueryList())
			throw parsePosition;
		if (!match("EOF"))
			throw parsePosition;
	}
	catch (int e) {
		//Error message:
		error = dataLog[e];
	}
	return;
}

bool parser::parseSchemeList() {

	if (match("ID")) {
		parsePosition = parsePosition - 1;
		return parseScheme();
	}
	else
		return true;
}

bool parser::parseFactList() {
	if (match("ID")) {
		parsePosition = parsePosition - 1;
		return parseFact();
	}
	else
		return true;
}

bool parser::parseRuleList() {

	if (match("ID")) {
		parsePosition = parsePosition - 1;
		return parseRule();
	}
	else
		return true;
}

bool parser::parseQueryList() {

	if (match("ID")) {
		parsePosition = parsePosition - 1;
		return parseQuery();
	}
	else
		return true;
}

bool parser::parseScheme() {
	int startingParsePosition = parsePosition;
	if (parseHeadPredicate()) {
		output.addScheme(new predicate("SCHEMES", dataLog[startingParsePosition]->getValue()));

		std::string value;
		std::string type;
		for (int i = startingParsePosition + 2; i < parsePosition - 1; i = i + 2) {

			//test if parameter is an expression
			if (dataLog[i]->getType() == "LEFT_PAREN") {
				expressionIncriment = i;
				value = makeExpression(value);
				type = "EXPRESSION";
				i = expressionIncriment;
			}
			else {
				value = dataLog[i]->getValue();
				type = dataLog[i]->getType();
			}
			output.addSchemeParameter(new parameter(type, value), output.getSchemeSize() - 1);
			value = "";
		}
		parseSchemeList();

		return true;
	}
	else
		return false;
	//return(parseHeadPredicate());
}

bool parser::parseFact() {
	int startingParsePosition = parsePosition;

	if (!match("ID"))
		return false;
	if (!match("LEFT_PAREN"))
		return false;
	if (!match("STRING"))
		return false;
	if (!parseStringList())
		return false;
	if (!match("RIGHT_PAREN"))
		return false;
	if (!match("PERIOD"))
		return false;

	output.addFact(new predicate("FACTS", dataLog[startingParsePosition]->getValue()));

	std::string value;
	std::string type;
	for (int i = startingParsePosition + 2; i < parsePosition - 2; i = i + 2) {
		if (dataLog[i]->getType() == "LEFT_PAREN") {
			expressionIncriment = i;
			value = makeExpression(value);
			type = "EXPRESSION";
			i = expressionIncriment;
		}
		else {
			value = dataLog[i]->getValue();
			type = dataLog[i]->getType();
		}
		output.addFactParameter(new parameter(type, value), output.getFactSize() - 1);
		output.addDomain(value);
		value = "";
	}

	parseFactList();

	return true;
}

bool parser::parseRule() {
	int startingParsePosition = parsePosition;

	if (!parseHeadPredicate())
		return false;
	if (!match("COLON_DASH"))
		return false;
	if (!parsePredicate())
		return false;
	if (!parsePredicateList())
		return false;
	if (!match("PERIOD"))
		return false;

	int i = startingParsePosition + 2;
	std::string value;
	std::string type;

	output.addRule(new rule());
	output.addBCRulePredicate(new predicate("RULE?", dataLog[startingParsePosition]->getValue()), output.getRuleSize() - 1);
	while (dataLog[i]->getType() != "RIGHT_PAREN") {

		//test if parameter is an expression
		if (dataLog[i]->getType() == "LEFT_PAREN") {
			expressionIncriment = i;
			value = makeExpression(value);
			type = "EXPRESSION";
			i = expressionIncriment;
		}
		else {
			value = dataLog[i]->getValue();
			type = dataLog[i]->getType();
		}
		output.addBCRuleParameter(new parameter(type, value), output.getRuleSize() - 1);
		if (dataLog[i + 1]->getType() == "RIGHT_PAREN") {
			i++;
			break;
		}
		else
			i = i + 2;
		value = "";
	}
	i = i + 2;

	int predCount = 0;
	int paramCount;

	while (i<parsePosition) {
		output.addACRulePredicate(new predicate("RULE?", dataLog[i]->getValue()), output.getRuleSize() - 1);
		i = i + 2;
		while (dataLog[i - 1]->getType() != "RIGHT_PAREN") {
			//test if parameter is an expression
			if (dataLog[i]->getType() == "LEFT_PAREN") {
				expressionIncriment = i;
				value = makeExpression(value);
				type = "EXPRESSION";
				i = expressionIncriment;
			}
			else {
				value = dataLog[i]->getValue();
				type = dataLog[i]->getType();
			}
			output.addACRuleParameter(new parameter(type, value), output.getRuleSize() - 1, predCount);
			i = i + 2;
			value = "";
		}
		i++;
		predCount++;
	}
	parseRuleList();
	return true;
}

bool parser::parseQuery() {
	int startingParsePosition = parsePosition;

	if (!parsePredicate())
		return false;
	if (!match("Q_MARK"))
		return false;

	std::string type;
	std::string value;
	output.addQuery(new predicate("QUERY", dataLog[startingParsePosition]->getValue()));
	for (int i = startingParsePosition + 2; i < parsePosition - 2; i = i + 2) {

		//test if parameter is an expression
		if (dataLog[i]->getType() == "LEFT_PAREN") {
			expressionIncriment = i;
			value = makeExpression(value);
			type = "EXPRESSION";
			i = expressionIncriment;
		}
		else {
			value = dataLog[i]->getValue();
			type = dataLog[i]->getType();
		}
		output.addQueryParameter(new parameter(type, value), output.getQuerySize() - 1);
		value = "";
	}

	parseQueryList();
	return true;
}

bool parser::parseHeadPredicate() {
	if (!match("ID"))
		return false;
	if (!match("LEFT_PAREN"))
		return false;
	if (!match("ID"))
		return false;
	if (!parseIDList())
		return false;
	if (!match("RIGHT_PAREN"))
		return false;
	return true;
}

bool parser::parsePredicate() {
	if (!match("ID"))
		return false;
	if (!match("LEFT_PAREN"))
		return false;
	if (!parseParameter())
		return false;
	if (!parseParameterList())
		return false;
	if (!match("RIGHT_PAREN"))
		return false;
	return true;
}

bool parser::parsePredicateList() {
	if (match("COMMA")) {
		if (parsePredicate()) {
			if (parsePredicateList())
				return true;
			else {
				parsePosition = parsePosition - 2;
				return true;
			}
		}
		else {
			parsePosition = parsePosition - 1;
			return true;
		}
	}
	else
		return true;
}

bool parser::parseParameterList() {
	if (match("COMMA")) {
		if (parseParameter()) {
			if (parseParameterList())
				return true;
			else {
				parsePosition = parsePosition - 2;
				return true;
			}
		}
		else {
			parsePosition = parsePosition - 1;
			return true;
		}
	}
	else
		return true;
}

bool parser::parseStringList() {
	if (match("COMMA")) {
		if (match("STRING")) {
			if (parseStringList())
				return true;
			else {
				parsePosition = parsePosition - 2;
				return true;
			}
		}
		else {
			parsePosition = parsePosition - 1;
			return true;
		}
	}
	else
		return true;
}

bool parser::parseIDList() {
	if (match("COMMA")) {
		if (match("ID")) {
			if (parseIDList())
				return true;
			else {
				parsePosition = parsePosition - 2;
				return true;
			}
		}
		else {
			parsePosition = parsePosition - 1;
			return true;
		}
	}
	else
		return true;
}

bool parser::parseParameter() {
	if (match("STRING"))
		return true;
	else if (match("ID"))
		return true;
	else if (parseExpression())
		return true;
	else
		return false;
}

bool parser::parseExpression() {
	if (!match("LEFT_PAREN"))
		return false;
	if (!parseParameter())
		return false;
	if (!parseOperators())
		return false;
	if (!parseParameter())
		return false;
	if (!match("RIGHT_PAREN"))
		return false;
	return true;
}

bool parser::parseOperators() {
	if (match("ADD"))
		return true;
	else if (match("MULTIPLY"))
		return true;
	else
		return false;
}

bool parser::match(std::string check) {
	//use this function to test if the input matches the vocabulary
	if (dataLog[parsePosition]->getType() == check) {
		parsePosition++;
		return true;
	}
	else
		return false;
}

void parser::printOutput(std::string outputFile) {
	//use this function to display results of a parse in a txt file
	std::ofstream outfile;
	outfile.open(outputFile);
	outfile << output.toString(error);
	return;
}

std::string parser::makeExpression(std::string soFar) {
	//use this function when a parameter is an expression

	//Left Paren
	soFar += dataLog[expressionIncriment]->getValue();
	expressionIncriment++;

	//First Element
	if (dataLog[expressionIncriment]->getType() == "LEFT_PAREN")
		soFar = makeExpression(soFar);
	else {
		soFar += dataLog[expressionIncriment]->getValue();
		expressionIncriment++;
	}

	//Operator
	soFar += dataLog[expressionIncriment]->getValue();
	expressionIncriment++;

	//second element
	if (dataLog[expressionIncriment]->getType() == "LEFT_PAREN")
		soFar = makeExpression(soFar);
	else {
		soFar += dataLog[expressionIncriment]->getValue();
		expressionIncriment++;
	}

	//right paren
	soFar += dataLog[expressionIncriment]->getValue();

	return soFar;
}

void parser::removeComments() {
	//comments should be recognized by the scanner but ignored by the parser
	for (int i = 0; i < dataLog.size(); i++) {
		if (dataLog[i]->getType() == "COMMENT") {
			dataLog.erase(dataLog.begin() + i);
			i = i - 1;
		}
	}
}

void parser::clear() {
	//cleanup function

	for (int i = 0; i < output.getSchemeSize(); i++) 
		delete output.getScheme(i);
	for (int i = 0; i < output.getFactSize(); i++)
		delete output.getFact(i);
	for (int i = 0; i < output.getRuleSize(); i++)
		delete output.getRule(i);
	for (int i = 0; i < output.getQuerySize(); i++)
		delete output.getQuery(i);
	return;
}

datalogProgram parser::getDatalogProgram() {
	//returns the datalogprogram
	return output;
}