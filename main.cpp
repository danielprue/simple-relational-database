#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Database.h"

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
		int fileCount = 11;

		for (int i = 0; i < fileCount; i++) {

			scanner* mainScanner = new scanner();
			mainScanner->setInfile("input" + std::to_string(i) + ".txt");
			mainScanner->scan();

			parser* mainParser = new parser(mainScanner->getList());
			mainParser->parseDatalogProgram();

			database* mainDatabase = new database();
			mainDatabase->evaluateDatalog(mainParser->getDatalogProgram(),i);
			
			delete mainDatabase;
			delete mainParser;
			delete mainScanner;
		}

	return 0;
}