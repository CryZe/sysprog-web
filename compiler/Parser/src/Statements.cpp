/*
 * Statements.cpp
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */
#include <iostream>
//strncpy
#include <stdio.h>
#include <string.h>
#include <sstream>

#include "Statements.h"
#include "ParseTree.h"
#include "Expression.h"
#include  "TypecheckError.h"

#include "../../Scanner/src/Scanner.h"
#include "../../Scanner/src/Token.h"
#include "../../Automat/src/TokenType.h"
using namespace std;
/*
 * Statements
 */

ParseTree* Statements::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();

	ParseTree *ret;
	if(tokentype ==  IDENTIFIER || tokentype == KEYWORD_IF ||tokentype == KEYWORD_WHILE || tokentype == KEYWORD_PRINT ||
		tokentype == KEYWORD_READ || tokentype == BRACES_OPEN_SIGN ){
		Statements1 *statment = new Statements1();
		statment->parsetree(scan);
		ret = statment;

	}else if (tokentype == FILE_END || tokentype == BRACES_CLOSED_SIGN){

		ret = new Statements2();
	}
	else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
	return ret;
}

/*
 * Statements1
 */
Statements1::Statements1() {

	//cout<<"Statements1"<<endl;
}

Statements1::~Statements1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	//cout<<"delete Statements1"<<endl;
}
void Statements1::parsetree(Scanner *scan){
	this->node[0] = Statement::parsetree(scan);

	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();

	if(tokentype == SEMICOLON_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
	}
	else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}

	this->node[1] = Statements::parsetree(scan);

}
void Statements1::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	node[1]->typecheck(symboltable);
	this->nodeType == noType;
}
void Statements1::makeCode(ostringstream &out, Symboltable *symboltable){
	node[0]->makeCode(out,symboltable);
	node[1]->makeCode(out,symboltable);
}

/*
 * Statements2
 */
Statements2::Statements2() {
	//cout<<"Statements2"<<endl;
}

Statements2::~Statements2() {
	//cout<<"delete Statements2"<<endl;
}
void Statements2::typecheck(Symboltable *symboltable){
	 this->nodeType == noType;
}
void Statements2::makeCode(ostringstream &out, Symboltable *symboltable){
	out<<" NOP ";
}

/*
 * Statement
 */
ParseTree* Statement::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	ParseTree *ret = 0;

	if(tokentype == IDENTIFIER){
		Statement1 *statement = new Statement1();
		statement->parsetree(scan);
		ret = statement;

	}else if(tokentype == KEYWORD_PRINT){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Statement2 *statement = new Statement2();
		statement->parsetree(scan);
		ret = statement;

	}else if(tokentype == KEYWORD_READ){
		scan->deleteToken(lastToken);
		scan->nextToken();

		Statement3 *statement = new Statement3();
		statement->parsetree(scan);
		ret = statement;

	}else if(tokentype == BRACES_OPEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();

		Statement4 *statement = new Statement4();
		statement->parsetree(scan);
		ret = statement;

	}else if(tokentype == KEYWORD_IF){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Statement5 *statement = new Statement5();
		statement->parsetree(scan);
		ret = statement;

	}else if(tokentype == KEYWORD_WHILE){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Statement6 *statement = new Statement6();
		statement->parsetree(scan);
		ret = statement;

	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
	return ret;
}
/*
 * Statement1
 */
Statement1::Statement1() {
	this->token = 0;
	//cout<<"Statement1"<<endl;
}

Statement1::~Statement1() {
	for(int i = 0; i<3;i++){
			if(this->node[i]){
				delete node[i];
			}else{
				break;
			}
		}
	delete token;
}

void Statement1::parsetree(Scanner* scan){
	Token *lastToken = scan->getLastToken();
	this->token = lastToken;
	lastToken = scan->nextToken();
	this->node[0] = Index::parsetree(scan);
	lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if(tokentype == EQUALS_SIGN){
		scan->deleteToken(lastToken);
		lastToken = scan->nextToken();
		this->node[1] = Expression::parsetree(scan);
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}
void Statement1::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	node[1]->typecheck(symboltable);
	NodeType nodeType = symboltable->lookup(token->getKey())->getNodeType();
	if( nodeType == noType){
		cerr<<"identifier not defined"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		this->nodeType = errorType;
		TypecheckError::getTypecheckError();
	}else if((node[1]->getNodeType() == intType )&&( (nodeType == intType && node[0]->getNodeType() == noType) ||
				(nodeType == intArrayType && node[0]->getNodeType() ==arrayType ) )){
		this->nodeType = noType;
	}
	else{
		cerr<<"incompatible Types"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		this->nodeType = errorType;
		TypecheckError::getTypecheckError();
	}
}
void Statement1::makeCode(ostringstream &out, Symboltable *symboltable){
	node[1]->makeCode(out,symboltable);
	out<<" LA "<<"$";
	int lenght = (unsigned char) symboltable->lookup(token->getKey())->lexem[0];
	for (int i = 1; i <= lenght; i++) {
		out<<symboltable->lookup(token->getKey())->lexem[i];
	}
	node[0]->makeCode(out,symboltable);
	out<<" STR ";
}
/*
 * Statement2
 */
Statement2::Statement2() {
	//cout<<"Statement2"<<endl;
}

Statement2::~Statement2() {
	for(int i = 0; i<3;i++){
			if(this->node[i]){
				delete node[i];
			}else{
				break;
			}
		}
	//cout<<"delete Statement2"<<endl;
}

void Statement2::parsetree(Scanner* scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if(tokentype == PARENTHESIS_OPEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		this->node[0] = Expression::parsetree(scan);

		lastToken = scan->getLastToken();
		tokentype = lastToken->getTokenType();
		if (tokentype == PARENTHESIS_CLOSE_SIGN) {
			scan->deleteToken(lastToken);
			scan->nextToken();
		}else{
			UnexpectedToken::getUnexpectedToken(lastToken);
		}
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}

void Statement2::typecheck(Symboltable *symboltable){
	this->node[0]->typecheck(symboltable);
	this->nodeType = noType;
}

void Statement2::makeCode(ostringstream &out, Symboltable *symboltable){
	node[0]->makeCode(out,symboltable);
	out<<" PRI ";
}
/*
 * Statement3
 */
Statement3::Statement3() {
	this->token = 0;
	//cout<<"Statement3"<<endl;
}

Statement3::~Statement3() {
	for(int i = 0; i<3;i++){
			if(this->node[i]){
				delete node[i];
			}else{
				break;
			}
		}
	delete token;
	//cout<<"delete Statement3"<<endl;
}

void Statement3::parsetree(Scanner* scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if(tokentype == PARENTHESIS_OPEN_SIGN){//Prüfung auf {
		scan->deleteToken(lastToken);
		lastToken = scan->nextToken();
		tokentype = lastToken->getTokenType();
		if(tokentype == IDENTIFIER){//Prüfung auf Identifier
			this->token = lastToken;
			scan->nextToken();
			this->node[0] = Index::parsetree(scan);
			Token *lastToken = scan->getLastToken();
			int tokentype = lastToken->getTokenType();
			if (tokentype == PARENTHESIS_CLOSE_SIGN) {
				scan->deleteToken(lastToken);
				scan->nextToken();
			}else{
				UnexpectedToken::getUnexpectedToken(lastToken);
			}
		}
		else{
			UnexpectedToken::getUnexpectedToken(lastToken);
		}
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}

void Statement3::typecheck(Symboltable *symboltable){
	this->node[0]->typecheck(symboltable);
	if(symboltable->lookup(this->token->getKey())->getNodeType() == noType ){
		cerr<<"identifier not defined"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		this->nodeType = errorType;
		TypecheckError::getTypecheckError();
	}else if(((symboltable->lookup(this->token->getKey())->getNodeType() == intType) && node[0]->getNodeType() == noType) ||
			((symboltable->lookup(this->token->getKey())->getNodeType() == intArrayType) && node[0]->getNodeType() == arrayType )){
		this->nodeType = noType;
	}else{
		cerr<<"incompatible Types"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		this->nodeType = errorType;
		TypecheckError::getTypecheckError();
	}
}
void Statement3::makeCode(ostringstream &out, Symboltable *symboltable){
	out<<" REA ";
	out<<" LA "<<"$";
	int lenght = (unsigned char) symboltable->lookup(token->getKey())->lexem[0];
	for (int i = 1; i <= lenght; i++) {
		out<<symboltable->lookup(token->getKey())->lexem[i];
	}
	node[0]->makeCode(out,symboltable);
	out<<" STR ";
}
/*
 * Statement4
 */
Statement4::Statement4() {
	//cout<<"Statement4"<<endl;
}

Statement4::~Statement4() {
	for(int i = 0; i<3;i++){
			if(this->node[i]){
				delete node[i];
			}else{
				break;
			}
		}
	//cout<<"delete Statement4"<<endl;
}
void Statement4::parsetree(Scanner* scan){
	this->node[0] = Statements::parsetree(scan);

	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if (tokentype == BRACES_CLOSED_SIGN) {
		scan->deleteToken(lastToken);
		scan->nextToken();
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}

void Statement4::typecheck(Symboltable *symboltable){
	 this->node[0]->typecheck(symboltable);
	 this->nodeType = noType;
}
void Statement4::makeCode(ostringstream &out, Symboltable *symboltable){
	node[0]->makeCode(out,symboltable);
}
/*
 * Statement5
 */
int Statement5::labelCount=1;
	Statement5::Statement5() {
	//cout<<"Statement5"<<endl;
}

Statement5::~Statement5() {
	for(int i = 0; i<3;i++){
			if(this->node[i]){
				delete node[i];
			}else{
				break;
			}
		}
	//cout<<"delete Statement5"<<endl;
}
void Statement5::parsetree(Scanner* scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if(tokentype == PARENTHESIS_OPEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		this->node[0] = Expression::parsetree(scan);
		lastToken = scan->getLastToken();
		tokentype = lastToken->getTokenType();
		if (tokentype == PARENTHESIS_CLOSE_SIGN) {
			scan->deleteToken(lastToken);
			scan->nextToken();
			this->node[1] = Statement::parsetree(scan);

			lastToken = scan->getLastToken();
			tokentype = lastToken->getTokenType();
			if (tokentype == KEYWORD_ELSE){
				scan->deleteToken(lastToken);
				scan->nextToken();
				this->node[2] = Statement::parsetree(scan);

			}else{
				UnexpectedToken::getUnexpectedToken(lastToken);
			}
		}else{
			UnexpectedToken::getUnexpectedToken(lastToken);
		}
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}
void Statement5::typecheck(Symboltable *symboltable){
	 this->node[0]->typecheck(symboltable);
	 this->node[1]->typecheck(symboltable);
	 this->node[2]->typecheck(symboltable);
	 if(node[0]->getNodeType() == errorType){
		this->nodeType = errorType;
	 }else{
		 this->nodeType = noType;
	 }
}
void Statement5::makeCode(ostringstream &out, Symboltable *symboltable){
	int lable1=labelCount++;
	int lable2=labelCount++;
	node[0]->makeCode(out,symboltable);
	out<<" JIN "<<"#"<<"if"<<lable1;
	node[1]->makeCode(out,symboltable);
	out<<" JMP "<<"#"<<"if"<<lable2;
	out<<" #"<<"if"<<lable1<<" NOP ";
	node[2]->makeCode(out,symboltable);
	out<<" #"<<"if"<<lable2<<" NOP ";
}

/*
 * Statement6
 */
int Statement6::labelCount=1;
Statement6::Statement6() {
	//cout<<"Statement6"<<endl;
}

Statement6::~Statement6() {
	for(int i = 0; i<3;i++){
			if(this->node[i]){
				delete node[i];
			}else{
				break;
			}
		}
	//cout<<"delete Statement6"<<endl;
}
void Statement6::parsetree(Scanner* scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if(tokentype == PARENTHESIS_OPEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		node[0] = Expression::parsetree(scan);
		lastToken = scan->getLastToken();
		tokentype = lastToken->getTokenType();
		if(tokentype == PARENTHESIS_CLOSE_SIGN){
			scan->deleteToken(lastToken);
			scan->nextToken();
			this->node[1] = Statement::parsetree(scan);
		}else{
			UnexpectedToken::getUnexpectedToken(lastToken);
		}
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}
 void Statement6::typecheck(Symboltable *symboltable){
	 this->node[0]->typecheck(symboltable);
	 this->node[1]->typecheck(symboltable);
	 if(node[0]->getNodeType() == errorType){
		this->nodeType = errorType;
	 }else{
		 this->nodeType = noType;
	 }
}
 void Statement6::makeCode(ostringstream &out, Symboltable *symboltable){
	 int lable1=labelCount++;
	 int lable2=labelCount++;
	 out<<"#"<<"while"<<lable1<<" NOP ";
	node[0]->makeCode(out,symboltable);
	out<<" JIN "<<"#"<<"while"<<lable2;
	node[1]->makeCode(out,symboltable);
	out<<" JMP "<<"#"<<"while"<<lable1;
	out<<" #"<<"while"<<lable2<<" NOP ";
 }
