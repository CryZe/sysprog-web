/*
 * Token.h
 *
 *  Created on: 30.10.2013
 *      Author: rainer
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include "../../Automat/src/TokenType.h"
#include "../../Symboltable/src/Symboltable.h"

class Token{
public:
	Token(TokenType type,unsigned int row, unsigned int column,
			Symboltable::Key key, long int integerValue, char errorCharacter);
	~Token();
	int getRow();
	int getColumn();
	TokenType getTokenType();
	Symboltable::Key getKey();
	char getErrorCharacter();
	long int getIntegerValue();

private:
	TokenType type;
	unsigned int row;
	unsigned int column;
	Symboltable::Key key;
	long int integerValue;
	char errorCharacter;

};


#endif /* TOKEN_H_ */
