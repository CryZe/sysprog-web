/*
 * Token.cpp
 *
 *  Created on: 30.10.2013
 *      Author: rainer
 */

#include "Token.h"



Token::Token(TokenType type, unsigned int row, unsigned int column,
		Symboltable::Key key, long int integerValue, char errorCharacter){
	this->type = type;
	this->row = row;
	this->column = column;
	this->key = key;
	this->integerValue = integerValue;
	this->errorCharacter = errorCharacter;
}

Token::~Token(){
}

TokenType Token::getTokenType() {
	return type;
}

int Token::getRow() {
	return row;
}

int Token::getColumn() {
	return column;
}

char Token::getErrorCharacter() {
	return errorCharacter;
}

long int Token::getIntegerValue() {
	return integerValue;
}

Symboltable::Key Token::getKey() {
	return key;
}
