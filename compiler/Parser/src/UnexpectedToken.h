/*
 * UnexpectedToken.h
 *
 *  Created on: 11.12.2013
 *      Author: henrik
 */

#ifndef UNEXPECTEDTOKEN_H_
#define UNEXPECTEDTOKEN_H_
#include "../../Automat/src/TokenType.h"
class Token;

class UnexpectedToken {
private:
	Token *token;
	int valueOfError;
	UnexpectedToken(Token *token);
	static UnexpectedToken* singelton;
public:
	static UnexpectedToken* getUnexpectedToken(Token *token);
	virtual ~UnexpectedToken();
	void message();
	int getValueOfError();
	static void reset();
};

#endif /* UNEXPECTEDTOKEN_H_ */
