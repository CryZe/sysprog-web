/*
 * Parser.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: Henrik
 */
#include <iostream>
#include <string>
#include <sstream>
#include "Parser.h"
#include "ParseTree.h"
#include "UnexpectedToken.h"
#include "NodeType.h"
#include "TypecheckError.h"
#include "Statements.h"
#include "../../Symboltable/src/Symboltable.h"
#include "../../Scanner/src/Scanner.h"

using namespace std;



Parser::Parser(const char* src, ostringstream &output)throw( std::exception ) :output(output) {
	symboltable = new Symboltable();
	try{
	scanner = new Scanner(symboltable, src);
	}catch(exception &e){
		delete symboltable;
		throw e;
	}
	//this->codepath = codepath;
}

Parser::~Parser(){
	delete scanner;
	delete symboltable;
}

void Parser::parse(){
	cout<<"starting parsing..."<<endl;
	UnexpectedToken::reset();
	TypecheckError::reset();
	Statement5::reset();
	Statement6::reset();
	ParseTree *parseTree = ParseTree::parsetree(scanner);
	UnexpectedToken *error = UnexpectedToken::getUnexpectedToken(0);
	if( error->getValueOfError() > 0 ){
		cout<<"STOP"<<endl;
		error->message();
	}
	else{
		cout<<"start typechecking..."<<endl;
		parseTree->typecheck(symboltable);
		if(TypecheckError::getTypecheckError()->getValueOfError() > 0 ){
			cout<<"STOP"<<endl;
		}
		else{
			cout<<"typecheck done!"<<endl;
			parseTree->makeCode(output,symboltable);
			cout<<"makeCode done!"<<endl;
		}
	}
	delete parseTree;
}
