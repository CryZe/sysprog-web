/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include "Scanner.h"
#include "Token.h"
#include "../../Automat/src/Automat.h"
#include "../../Automat/src/Lexem.h"
#include "../../Buffer/src/Buffer.h"
#include "../../Symboltable/src/Symboltable.h"
using namespace std;

const unsigned int identifierSize = 255;

Scanner::Scanner(Symboltable* symboltable, const char* src) throw( std::exception ){
	this->symboltable = symboltable;
	this->automat = new Automat();
	try{
		this->buffer = new Buffer(src);
	}catch(exception &e){
		delete automat;
		throw e;
	}
	this->lastToken = 0;
	this->row = 0;
	this->column = 0;

	this->scannerBufferPtr = &scannerBuffer[0];
	this->lexemLength = 0;
}

Scanner::~Scanner() {
	delete automat;
	delete buffer;
}

void Scanner::deleteToken(Token* token){
	if(token) {
		delete token;
	}
}

void Scanner::resetScanner(){
	scannerBufferPtr = &scannerBuffer[0];
	lexemLength = 0;
}

Token* Scanner::getLastToken()  {
		return lastToken;
}

Token* Scanner::buildToken(Lexem* lexem){
	Token* token;
	TokenType tokenType = lexem->getTokenType();
	Symboltable::Key key = 0;
	long int integerValue = 0;
	char errorCharacter = 0;

	if(tokenType == IDENTIFIER) {
		// Symboltabelle aufrufen und key speichern
		key = symboltable->insert(&scannerBuffer[0], lexemLength);

		TokenType tempType = symboltable->lookup(key)->keyword;
		if (tempType != IDENTIFIER) {
			//Schlüsselwort erkannt und speichern
			tokenType = tempType;
		}
	}
	else if(tokenType == INTEGER) {
		errno = 0;
		integerValue = strtol(&scannerBuffer[0], &scannerBufferPtr, 10);
		// Bereichsüberschreitung
		if(errno == ERANGE) { // hex: 0xffffffffffffffff dec: 18446744073709551615
			cerr << "Ganzzahl in Zeile " << row  << ":" << column
				<< " muss kleiner als (2^(64) - 1) sein! \n";
		}
	}
	else if(tokenType == ERROR_SIGN) {
		errorCharacter = scannerBuffer[0];
	}


		token = new Token(tokenType, row, column, key, integerValue, errorCharacter);

	lastToken = token;
	return token;
}

Token* Scanner::nextToken(){
	Lexem* lexem;
	bool reading = true;
	row = automat->getRow();
	column = automat->getColumn();

	while(reading) {
		if(lexemLength > identifierSize) {
			cerr << "Lexem in Zeile " << row << ":" << column
					<< " überschreitet max. Länge von " << identifierSize << " Zeichen!\n";
			lexemLength = 1;
			scannerBufferPtr = &scannerBuffer[0];
			do{
				*scannerBufferPtr = *(buffer->getNextChar());
				lexem = automat->read(scannerBufferPtr);
			} while(lexem->getNeedNext());

		}
		else{
		*scannerBufferPtr = *(buffer->getNextChar());
		lexemLength++;
		lexem = automat->read(scannerBufferPtr);
		scannerBufferPtr++;
		}
		// Lexem ueberpruefen
		if(!(lexem->getNeedNext())) {
			int bufferBack = lexem->getBufferBack();
			if(bufferBack > 0){
				// es müssen Schritte vom Buffer zurückgegangen werden
				buffer->goBack(bufferBack);
				lexemLength -= bufferBack;

				if(lexemLength > 0) {
					reading = false; //Schleifenende
				}
			}
			else if(bufferBack < 0) {
				// gewisse Anzahl Zeichen verwerfen, NEGATIVE ZAHL!,
				//dann Token bauen, falls noch Zeichen vorhanden
				lexemLength += bufferBack;
				scannerBufferPtr += bufferBack;

				if(lexemLength > 0) {
					reading = false; //Schleifenende
				}
				else {
					scannerBufferPtr = &scannerBuffer[0];
					row = automat->getRow();
					column = automat->getColumn();
				}
			}
			else {//if(lexem->getBufferBack() == 0)
				//OK. Token aus aktuellen Zeichen bauen
				reading = false; //Schleifenende
			}
		}

		//else {
			// Schleife von vorne, naechsteletztesletztesletztess Zeichen von Buffer lesen
		//}
	}// Ende while

	Token* token = this->buildToken(lexem);
	lexem->reset();
	resetScanner();
	return token;
}

