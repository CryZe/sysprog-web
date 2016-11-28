/*
 * Declarations.cpp
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */
#include <iostream>
#include <string>
#include <sstream>
#include "ParseTree.h"
#include "Declarations.h"
#include "UnexpectedToken.h"
#include  "TypecheckError.h"
#include "../../Scanner/src/Scanner.h"
#include "../../Scanner/src/Token.h"
#include "../../Automat/src/TokenType.h"



#include <stdio.h>
#include <string.h>
using namespace std;
/*
 * Declarations
 */
ParseTree* Declarations::parsetree(Scanner *scan){
	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();

	ParseTree *ret = 0;

	if(tokentype == KEYWORD_INT){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Declarations1 *node = new Declarations1();
		node->parsetree(scan);
		ret = node;

	}else if(tokentype ==  IDENTIFIER || tokentype == KEYWORD_IF ||tokentype == KEYWORD_WHILE || tokentype == KEYWORD_PRINT ||
			 tokentype == KEYWORD_READ || tokentype == BRACES_OPEN_SIGN || tokentype == FILE_END){
		Declarations2 *node = new Declarations2();
		ret = node;
	}else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}

return ret;
}
/*
 * Declarations1
 */

Declarations1::Declarations1() {
	//cout<<"Declarations1"<<endl;
}

Declarations1::~Declarations1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	//cout<<"delete Declarations1"<<endl;
}

void Declarations1::parsetree(Scanner *scan){
	this->node[0] = Declaration::parsetree(scan);

	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();

	if(tokentype == SEMICOLON_SIGN){
		scan->deleteToken(lastToken);
		scan->nextToken();
	}
	else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}

	this->node[1] = Declarations::parsetree(scan);

}
 void Declarations1::typecheck(Symboltable *sym){
	node[0]->typecheck(sym);
	node[1]->typecheck(sym);
	this->nodeType = noType;
}

 void Declarations1::makeCode(ostringstream &out, Symboltable *symboltable){
	  node[0]->makeCode(out, symboltable);
	  node[1]->makeCode(out, symboltable);
 }
/*
 * Declarations2
 */

Declarations2::Declarations2() {
	//cout<<"Declarations2"<<endl;
}

Declarations2::~Declarations2() {
}

/*
 * Declaration
 */

ParseTree* Declaration::parsetree(Scanner *scan){
	Declaration1 *decel =new Declaration1();
	decel->parsetree(scan);
	return decel;
}
/*
 * Declaration1
 */

Declaration1::Declaration1() {
	this->token = 0;
	//cout<<"Declaration1"<<endl;
}

Declaration1::~Declaration1() {
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	delete token;
	//cout<<"delete Declaration1"<<endl;
}
void Declaration1::parsetree(Scanner *scan){
	node[0]= Array::parsetree(scan);

	Token *lastToken = scan->getLastToken();
	int tokentype = lastToken->getTokenType();

	if(tokentype == IDENTIFIER){
		 this->token = lastToken;
		 scan->nextToken();
	}
	else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}

}

 void Declaration1::typecheck(Symboltable *symboltable){
	this->node[0]->typecheck(symboltable);
	if(symboltable->lookup(token->getKey())->getNodeType() != noType){
		cerr<<"identifier already defined"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		TypecheckError::getTypecheckError();
		this->nodeType = errorType;
	}else if(node[0]->getNodeType() == errorType){
		this->nodeType = errorType;
	}else{
		this->nodeType = noType;
		if (node[0]->getNodeType() == arrayType) {
			symboltable->lookup(this->token->getKey())->setNodeType(intArrayType);
		}else{
			symboltable->lookup(this->token->getKey())->setNodeType(intType);
		}
	}

}
 void Declaration1::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" DS "<<"$";
	 int lenght = (unsigned char) symboltable->lookup(token->getKey())->lexem[0];
	 for (int i = 1; i <= lenght; i++) {
		 out<<symboltable->lookup(token->getKey())->lexem[i];
	 }
	 node[0]->makeCode(out,symboltable);
 }
/*
 *Array
 */
 ParseTree* Array::parsetree(Scanner *scan) {
	 Token *lastToken = scan->getLastToken();
	 int tokentype = lastToken->getTokenType();

	 ParseTree *ret;

	if(tokentype == SQUARE_BRACKET_OPEN_SIGN ){
		scan->deleteToken(lastToken);
		scan->nextToken();
		Array1 *array = new Array1();
		array->parsetree(scan);
		ret = array;
	}
	else if(tokentype == IDENTIFIER ){
		ret = new Array2();
	}
	else {
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
	return ret;
}


/*
 *Array1
 */

Array1::Array1(){
this->token = 0;
//cout<<"Array1"<<endl;
}

Array1::~Array1(){
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
	delete this->token;
//	cout<<"delete Array1"<<endl;
}
void Array1::parsetree(Scanner *scan){
	 Token *lastToken = scan->getLastToken();
	 int tokentype = lastToken->getTokenType();

	 if(tokentype == INTEGER ){
		 this->token = lastToken;
		 lastToken = scan->nextToken();
		 if(lastToken->getTokenType() == SQUARE_BRACKET_CLOSE_SIGN){
			 scan->deleteToken(lastToken);
			 scan->nextToken();
		 }else{
			 UnexpectedToken::getUnexpectedToken(lastToken);
		 }

	}
	else{
		UnexpectedToken::getUnexpectedToken(lastToken);
	}
}
 void Array1::typecheck(Symboltable *symboltable) {
	if(token->getIntegerValue() > 0){
		this->nodeType = arrayType;
	}else{
		cerr<<"no valid dimension"<<endl;
		cerr<<"Zeile:"<<this->token->getRow()<<" Spalte:"<<this->token->getColumn()<<endl;
		TypecheckError::getTypecheckError();
		this->nodeType = errorType;
	}

}
 void Array1::makeCode(ostringstream &out, Symboltable *symboltable){
	 out<<" "<<token->getIntegerValue()<<" ";
  }
/*
 *Array2
 */

Array2::Array2(){
	//cout<<"Array2"<<endl;
}

Array2::~Array2(){
//	cout<<"delete Array2"<<endl;
}
 void Array2::typecheck(Symboltable *symboltable) {
	 this->nodeType = noType;
}
 void Array2::makeCode(ostringstream &out, Symboltable*){
	 out<<" "<<1<<" ";
  }
