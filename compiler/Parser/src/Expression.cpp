/*
 * Expression.cpp
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */
#include <stdio.h>
#include <string.h>

#include "Expression.h"
#include "TypecheckError.h"
#include "../../Scanner/src/Scanner.h"
#include "../../Scanner/src/Token.h"
#include "../../Automat/src/TokenType.h"

using namespace std;
/*
 * Expression
 */
ParseTree* Expression::parsetree(Scanner *scan){
	Expression1 *exp = new Expression1();
	exp->parsetree(scan);
	return exp;
}

/*
 * Expression1
 */
Expression1::Expression1() {
	//cout<<"Expression1"<<endl;
}

Expression1::~Expression1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	//cout<<"delete Expression1"<<endl;
}
void Expression1::parsetree(Scanner *scan){
	this->node[0] = Expression2_0::parsetree(scan);
	this->node[1] = Operant_Exprssion::parsetree(scan);
}

void Expression1::typecheck(Symboltable *symboltable){
	this->node[0]->typecheck(symboltable);
	this->node[1]->typecheck(symboltable);
	if(node[1]->getNodeType() == noType){
		this->nodeType = node[0]->getNodeType();
	}else if(node[1]->getNodeType() != node[0]->getNodeType()){
		this->nodeType = errorType;
	}else{
		this->nodeType = node[0]->getNodeType();
	}
}

void Expression1::makeCode(ostringstream &out, Symboltable *symboltable){
	if(node[1]->getNodeType() == noType){
		node[0]->makeCode(out,symboltable);
	}else if(node[1]->getNode(0)->getNodeType() == opGreater){
		node[1]->makeCode(out,symboltable);
		node[0]->makeCode(out,symboltable);
		out<<" LES ";
	}else if(node[1]->getNode(0)->getNodeType() == opUnEqual){
		node[0]->makeCode(out,symboltable);
		node[1]->makeCode(out,symboltable);
		out<<" NOT ";
	}else{
		node[0]->makeCode(out,symboltable);
		node[1]->makeCode(out,symboltable);
	}
}
/*
 * Expression2_0
 */
ParseTree* Expression2_0::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();

	ParseTree *ret = 0;
	if(tokentype == PARENTHESIS_OPEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Expression2_1 *exp = new Expression2_1();
		exp->parsetree(scan);
		ret = exp;

	}else if(tokentype == IDENTIFIER){
		Expression2_2 *exp = new Expression2_2();
		exp->parsetree(scan);
		ret = exp;
	}else if(tokentype == INTEGER){
		Expression2_3 *exp = new Expression2_3();
		exp->parsetree(scan);
		ret = exp;
	}else if(tokentype == HYPHEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Expression2_4 *exp = new Expression2_4();
		exp->parsetree(scan);
		ret = exp;
	}else if(tokentype == NOT_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Expression2_5 *exp = new Expression2_5();
		exp->parsetree(scan);
		ret = exp;
	}
	else{
		UnexpectedToken::getUnexpectedToken(lastToken);

	}
	return ret;
}


/*
 * Expression2_1
 */
Expression2_1::Expression2_1() {
	//cout<<"Expression2_1"<<endl;
}

Expression2_1::~Expression2_1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	//cout<<"delete Expression2_1"<<endl;
}
void Expression2_1::parsetree(Scanner *scan){
	this->node[0] = Expression::parsetree(scan);
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if (tokentype == PARENTHESIS_CLOSE_SIGN) {
		scan->deleteToken(lastToken);
		scan->nextToken();
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}

void Expression2_1::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	this->nodeType = node[0]->getNodeType();
}

void Expression2_1::makeCode(ostringstream &out, Symboltable *symboltable){
	node[0]->makeCode(out,symboltable);
}
/*
 * Expression2_2
 */
Expression2_2::Expression2_2() {
	this->token = 0;
	//cout<<"Expression2_2"<<endl;
}

Expression2_2::~Expression2_2() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	delete token;
	//cout<<"delete Expression2_2"<<endl;
}
void Expression2_2::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	this->token = lastToken;
	scan->nextToken();
	node[0] = Index::parsetree(scan);
}

void Expression2_2::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	if(symboltable->lookup(token->getKey())->getNodeType() == noType){
		cerr<<"identifier not defined"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		this->nodeType = errorType;
		TypecheckError::getTypecheckError();
	}else if(symboltable->lookup(token->getKey())->getNodeType() == intType && node[0]->getNodeType() == noType){
		this->nodeType = intType;//in folien etwas anderst aber gleich
	}else if(symboltable->lookup(token->getKey())->getNodeType() == intArrayType && node[0]->getNodeType() == arrayType){
		this->nodeType =intType;
	}else{
		cerr<<"no primitive Type"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		this->nodeType = errorType;
		TypecheckError::getTypecheckError();
	}
}
void Expression2_2::makeCode(ostringstream &out, Symboltable *symboltable){
	out<<" LA "<<"$";
	int lenght = (unsigned char) symboltable->lookup(token->getKey())->lexem[0];
	for (int i = 1; i <= lenght; i++) {
		out<<symboltable->lookup(token->getKey())->lexem[i];
	}
	node[0]->makeCode(out,symboltable);
	out<<" LV ";
}
/*
 * Expression2_3
 */
Expression2_3::Expression2_3() {
	this->token = 0;
	//cout<<"Expression2_3"<<endl;
}

Expression2_3::~Expression2_3() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	delete token;
	//cout<<"delete Expression2_3"<<endl;
}
void Expression2_3::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	this->token = lastToken;
	scan->nextToken();
}

void Expression2_3::typecheck(Symboltable *symboltable){
	this->nodeType = intType;
}

void Expression2_3::makeCode(ostringstream &out, Symboltable *symboltable){
	out<<" LC "<<token->getIntegerValue();
}
/*
 * Expression2_4
 */
Expression2_4::Expression2_4() {

	//cout<<"Expression2_4"<<endl;
}

Expression2_4::~Expression2_4() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}

	//cout<<"delete Expression2_4"<<endl;
}
void Expression2_4::parsetree(Scanner *scan){
	this->node[0] = Expression2_0::parsetree(scan);
}

void Expression2_4::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	this->nodeType = node[0]->getNodeType() ;
}

void Expression2_4::makeCode(ostringstream &out, Symboltable *symboltable){
	out<<" LC "<<0;
	node[0]->makeCode(out,symboltable);
	out<<" SUB ";
}
/*
 * Expression2_5
 */
Expression2_5::Expression2_5() {

	//cout<<"Expression2_5"<<endl;
}

Expression2_5::~Expression2_5() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	//cout<<"delete Expression2_5"<<endl;
}
void Expression2_5::parsetree(Scanner *scan){
	this->node[0] = Expression2_0::parsetree(scan);
}
void Expression2_5::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	if(node[0]->getNodeType() != intType){
		this->nodeType = errorType;
	}else{
		this->nodeType = intType;
	}
}
 void Expression2_5::makeCode(ostringstream &out, Symboltable *symboltable){
	 node[0]->makeCode(out,symboltable);
	 out<<" NOT ";
 }
/*
 * Index
 */
ParseTree* Index::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	ParseTree *ret = 0;
	if(tokentype == SQUARE_BRACKET_OPEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Index1 *index = new Index1();
		index->parsetree(scan);
		ret = index;

	}else if(tokentype == EQUALS_SIGN || tokentype == PARENTHESIS_CLOSE_SIGN || tokentype == PLUS_SIGN ||tokentype == STAR_SIGN || tokentype == SLASH_SIGN||
			tokentype == LESS_THAN_SIGN || tokentype == MORE_THAN_SIGN || tokentype == DOUBLE_EQUALS_SIGN || tokentype == EQUAL_NOT_EQUAL_SIGN ||
			tokentype == AND_SIGN || tokentype == SEMICOLON_SIGN || tokentype == SQUARE_BRACKET_CLOSE_SIGN || tokentype == HYPHEN_SIGN || tokentype == KEYWORD_ELSE){
		ret = new Index2();

	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);

	}
	return ret;
}
/*
 * Index1
 */
Index1::Index1() {
	//cout<<"Index1"<<endl;
}

Index1::~Index1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}

	//cout<<"delete Index1"<<endl;
}
void Index1::parsetree(Scanner *scan){
	this->node[0] = Expression::parsetree(scan);
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	if (tokentype == SQUARE_BRACKET_CLOSE_SIGN) {
		scan->deleteToken(lastToken);
		scan->nextToken();
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}

void Index1::typecheck(Symboltable *symboltable){
	 this->node[0]->typecheck(symboltable);
	 if(node[0]->getNodeType() == errorType){
		 this->nodeType = errorType;
	 }else {
		 this->nodeType = arrayType;
	 }
}

void Index1::makeCode(ostringstream &out, Symboltable *symboltable){
	node[0]->makeCode(out,symboltable);
	out<<" ADD ";
}
/*
 * Index2
 */
Index2::Index2() {
	//cout<<"Index2"<<endl;
}

Index2::~Index2() {
	//cout<<"delete Index2"<<endl;
}
 void Index2::typecheck(Symboltable *symboltable){
	 this->nodeType = noType;
}
/*
 * Operant_Exprssion
 */
ParseTree* Operant_Exprssion::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	ParseTree *ret = 0;
	if(tokentype == PLUS_SIGN ||tokentype == LESS_THAN_SIGN || tokentype == MORE_THAN_SIGN || tokentype == DOUBLE_EQUALS_SIGN || tokentype == EQUAL_NOT_EQUAL_SIGN ||
			tokentype == AND_SIGN ||  tokentype == STAR_SIGN || tokentype == SLASH_SIGN || tokentype == HYPHEN_SIGN){
		Operant_Exprssion1 *Operant_Exprssion = new Operant_Exprssion1();
		Operant_Exprssion->parsetree(scan);
		ret = Operant_Exprssion;

	}else if( tokentype == PARENTHESIS_CLOSE_SIGN || tokentype == SEMICOLON_SIGN || tokentype == SQUARE_BRACKET_CLOSE_SIGN || tokentype == KEYWORD_ELSE){
		ret = new Operant_Exprssion2();

	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);

	}
 return ret;
}
/*
 * Operant_Exprssion1
 */
Operant_Exprssion1::Operant_Exprssion1() {

	//cout<<"Operant_Exprssion1"<<endl;
}

Operant_Exprssion1::~Operant_Exprssion1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}

	//cout<<"delete Index1"<<endl;
}

void Operant_Exprssion1::parsetree(Scanner *scan){
	this->node[0] = Operant::parsetree(scan);
	this->node[1] = Expression::parsetree(scan);
}

void Operant_Exprssion1::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	node[1]->typecheck(symboltable);
	this->nodeType = node[1]->getNodeType();
}

 void Operant_Exprssion1::makeCode(ostringstream &out, Symboltable *symboltable){
	node[1]->makeCode(out,symboltable);
	node[0]->makeCode(out,symboltable);
}
/*
 * Operant_Exprssion2
 */
Operant_Exprssion2::Operant_Exprssion2() {
	//cout<<"Operant_Exprssion2"<<endl;
}

Operant_Exprssion2::~Operant_Exprssion2() {
	//cout<<"delete Operant_Exprssion2"<<endl;
}

 void Operant_Exprssion2::typecheck(Symboltable *){
	this->nodeType = noType;
}
/*
 * Operant
 */
ParseTree* Operant::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();
	ParseTree *ret = 0;
	if(tokentype == PLUS_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant1();
	}else if(tokentype == LESS_THAN_SIGN ){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant2();
	}else if(tokentype == MORE_THAN_SIGN ){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant3();
	}else if(tokentype == DOUBLE_EQUALS_SIGN ){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant4();
	}else if(tokentype == EQUAL_NOT_EQUAL_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant5();
	}else if(tokentype == AND_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant6();
	}else if(tokentype == STAR_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant7();
	}else if(tokentype == SLASH_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant8();
	}else if(tokentype == HYPHEN_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
		ret = new Operant9();
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);

	}
return ret;
}
/*
 * Operant1
 */
Operant1::Operant1() {
	//cout<<"Operant1"<<endl;
}

Operant1::~Operant1() {
	//cout<<"delete Operant1"<<endl;
}

 void Operant1::typecheck(Symboltable *){
	 this-> nodeType = opPlus;
}
 void Operant1::makeCode(ostringstream &out, Symboltable *symboltable){
 	 out<<" ADD ";
 }
/*
 * Operant2
 */
Operant2::Operant2() {
	//cout<<"Operant2"<<endl;
}

Operant2::~Operant2() {
	//cout<<"delete Operant2"<<endl;
}

void Operant2::typecheck(Symboltable *){
	 this-> nodeType = opLess;
}

void Operant2::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" LES ";
}
/*
 * Operant3
 */
Operant3::Operant3() {
	//cout<<"Operant3"<<endl;
}

Operant3::~Operant3() {
	//cout<<"delete Operant3"<<endl;
}

void Operant3::typecheck(Symboltable *){
	 this-> nodeType = opGreater;
}
void Operant3::makeCode(ostringstream &out, Symboltable *symboltable){

}

/*
 * Operant4
 */
Operant4::Operant4() {
	//cout<<"Operant4"<<endl;
}

Operant4::~Operant4() {
	//cout<<"delete Operant4"<<endl;
}

void Operant4::typecheck(Symboltable *){
	 this-> nodeType = opEqual;
}

void Operant4::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" EQU ";
}

/*
 * Operant5
 */
Operant5::Operant5() {
	//cout<<"Operant5"<<endl;
}

Operant5::~Operant5() {
	//cout<<"delete Operant5"<<endl;
}

void Operant5::typecheck(Symboltable *){
	 this-> nodeType = opUnEqual;
}

void Operant5::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" EQU ";
}


/*
 * Operant6
 */
Operant6::Operant6() {
	//cout<<"Operant6"<<endl;
}

Operant6::~Operant6() {
	//cout<<"delete Operant6"<<endl;
}

void Operant6::typecheck(Symboltable *){
	 this-> nodeType = opAnd;
}

void Operant6::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" AND ";
}

/*
 * Operant7
 */
Operant7::Operant7() {
	//cout<<"Operant7"<<endl;
}

Operant7::~Operant7() {
	//cout<<"delete Operant7"<<endl;
}

void Operant7::typecheck(Symboltable *){
	 this-> nodeType = opMult;
}

void Operant7::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" MUL ";
}

/*
 * Operant8
 */
Operant8::Operant8() {
	//cout<<"Operant8"<<endl;
}

Operant8::~Operant8() {
	//cout<<"delete Operant8"<<endl;
}

void Operant8::typecheck(Symboltable *){
	 this-> nodeType = opDiv;
}

void Operant8::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" DIV ";
}
/*
 * Operant9
 */
Operant9::Operant9() {
	//cout<<"Operant9"<<endl;
}

Operant9::~Operant9() {
	//cout<<"delete Operant9"<<endl;
}

void Operant9::typecheck(Symboltable *){
	 this-> nodeType = opMinus;
}

 void Operant9::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" SUB ";
 }


