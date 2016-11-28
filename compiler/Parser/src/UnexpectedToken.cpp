/*
 * UnexpectedToken.cpp
 *
 *  Created on: 11.12.2013
 *      Author: henrik
 */
#include <iostream>
#include "UnexpectedToken.h"
#include "../../Automat/src/TokenType.h"
#include "../../Scanner/src/Token.h"
using namespace std;

const char* tokenTypeStr[] = {
    "INTEGER",
    "IDENTIFIER",
    "KEYWORD_IF",
	"KEYWORD_ELSE",
	"KEYWORD_WHILE",
	"KEYWORD_INT",
	"KEYWORD_PRINT",
	"KEYWORD_READ",
    "PLUS_SIGN",
    "HYPHEN_SIGN",
    "SLASH_SIGN",
    "STAR_SIGN",
    "LESS_THAN_SIGN",
    "MORE_THAN_SIGN",
    "EQUALS_SIGN",
    "DOUBLE_EQUALS_SIGN",
    "NOT_SIGN",
    "AND_SIGN",
    "SEMICOLON_SIGN",
    "PARENTHESIS_OPEN_SIGN",
    "PARENTHESIS_CLOSE_SIGN",
    "EQUAL_NOT_EQUAL_SIGN",
    "BRACES_OPEN_SIGN",
    "BRACES_CLOSED_SIGN",
    "SQUARE_BRACKET_OPEN_SIGN",
    "SQUARE_BRACKET_CLOSE_SIGN",
    "FILE_END",
    "SPACE_SIGN",
    "ERROR_SIGN"
};

UnexpectedToken* UnexpectedToken::singelton = 0;

UnexpectedToken::~UnexpectedToken() {
	// TODO Auto-generated destructor stub
}

UnexpectedToken::UnexpectedToken(Token *token){
	this->token = token;
	this->valueOfError = 0;
}

UnexpectedToken* UnexpectedToken::getUnexpectedToken(Token *token){
	if(!(singelton)){
		singelton = new UnexpectedToken(token);
	}else
	{
		singelton->valueOfError++;
	}
	return singelton;
}

void UnexpectedToken::reset() {
    if(singelton) {
        singelton->valueOfError = -1;
        singelton->token = 0;
    }
}

void UnexpectedToken::message(){
	cerr<<"UnexpectedToken vom Typ "<<tokenTypeStr[this->token->getTokenType()]<<'\n'<<"Zeile:"<<this->token->getRow()
			<<" Spalte:"<<this->token->getColumn()<<'\n'<<this->valueOfError-1<<" (Folgefehler)"<<endl;
}

int UnexpectedToken::getValueOfError(){
	return this->valueOfError;
}

