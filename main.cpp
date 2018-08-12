#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Database.h"

//Macro for dumpling memory to find leaks

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <iostream>

int main() {
	VS_MEM_CHECK

		//edit here to change the number of files to be tested
		//name each input file "input" + n + ".txt"
		int fileCount = 11;

		for (int i = 0; i < fileCount; i++) {

			//scans input and saves them as tokens
			scanner* mainScanner = new scanner();
			mainScanner->setInfile("input" + std::to_string(i) + ".txt");
			mainScanner->scan();

			//parse tokens and store correctly input schemes, facts, rules, queries
			parser* mainParser = new parser(mainScanner->getList());
			mainParser->parseDatalogProgram();

			//evaluate schemes facts rules queries and write output to file
			database* mainDatabase = new database();
			mainDatabase->evaluateDatalog(mainParser->getDatalogProgram(),i);
			
			//cleanup
			delete mainDatabase;
			delete mainParser;
			delete mainScanner;
		}

	return 0;
}