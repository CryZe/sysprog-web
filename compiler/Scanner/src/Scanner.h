/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

class Token;
class Buffer;
class Automat;
class Symboltable;
class Lexem;


class Scanner {
public:
	Scanner(Symboltable* symboltable, const char* src)throw( std::exception );
	virtual ~Scanner();
	Token* nextToken();
	void deleteToken(Token* token);
	Token* getLastToken();


private:
	Buffer* buffer;
	Automat* automat;
	Symboltable* symboltable;
	Token* lastToken;
	char scannerBuffer[512];
	char* scannerBufferPtr;
	unsigned int lexemLength;
	unsigned int row;
	unsigned int column;

	Token* buildToken(Lexem* lexem);
	void resetScanner();
};

#endif /* SCANNER_H_ */
