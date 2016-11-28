/*
Parser *
 *  Created on: Nov 20, 2013
 *      Author: Henrik
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <exception>
#include <string>
#include <sstream>
class Symboltable;
class Scanner;

class Parser {
public:
	Parser(const char* src, std::ostringstream& output)throw( std::exception ) ;
	~Parser();
	void parse();


private:
	Symboltable *symboltable;
	Scanner *scanner;
	std::ostringstream& output;
};


#endif /* PARSER_H_ */
