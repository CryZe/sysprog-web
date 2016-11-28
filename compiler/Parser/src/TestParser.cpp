#include "Parser.h"
#include <iostream>
#include <ctime>
using namespace std;

extern "C" {
	const char* parse(char* code) {
		ostringstream result;
		try{
			Parser* parser = new Parser(code, result);
			parser->parse();
			delete parser;
			string* str = new string(result.str());
			return str->c_str();
		} catch(exception &e){
			return "Couldn't parse";
		}
	}
}
