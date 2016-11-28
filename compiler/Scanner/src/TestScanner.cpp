#include "Scanner.h"
#include "Token.h"
#include "../../Automat/src/TokenType.h"
#include "../../Symboltable/src/Symboltable.h"
#include <iostream>
#include <fstream>
#include <ctime>
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

//const char* keywordStr[] = { "ID", "IF_KEY", "WHILE_KEY" };


int main(int argc, char** argv) {

	time_t start = time(NULL);
	Symboltable* symboltable = new Symboltable();
	Scanner* scanner = new Scanner(symboltable, argv[1]);
	ofstream output;
	output.open (argv[2]);

	Token* token ;
	while( (scanner->nextToken()->getTokenType() != FILE_END) ) {
		token = scanner->getLastToken();
		TokenType type = token->getTokenType();

		if(type == ERROR_SIGN) {
			cerr << "Unbekanntes Zeichen: " << token->getErrorCharacter() << "\tin Zeile "
					<< token->getRow() << ":" << token->getColumn() << "\n";
		}
		else{
			output << "Zeile: " << token->getRow() << "\t Spalte: " << token->getColumn()
					<< "\t Typ: " << tokenTypeStr[token->getTokenType()];

			if(type == INTEGER) {
				output << "\t\tWert: " << token->getIntegerValue() << "\n";
			}
			else if(type == IDENTIFIER) {
				InfoContainer* info = symboltable->lookup(token->getKey());
				unsigned char length = (unsigned char) *(info->lexem);
				char* lexem = (info->lexem + 1);
				output << "\tLexem: ";
				for(unsigned char i = 0; i < length; i++) {
					output << lexem[i];
				}
				/*if(info->keyword != ID) {
					output << "\tKeyword: " << keywordStr[info->keyword];
				}*/
				output << "\n";
			}
			else {
				output << "\n";
			}
		}
		scanner->deleteToken(token);
	}
	output.close();
	delete scanner;
	delete symboltable;
	time_t end = time(NULL);
	//time_t end = time(0);
	//double diff = difftime(end, start);
	cout << "Zeit: " << (end - start) << "s" << endl;
	return 0;
}


/*
 while( (token = scanner->nextToken()) ) {

		cout << "Zeile: " << token->getRow() << "\t Spalte: " << token->getColumn()
				<< "\t Typ: " << tokenTypeStr[token->getTokenType()];

		TokenType type = token->getTokenType();
		if(type == INTEGER) {
			cout << "\t\tWert: " << token->getIntegerValue() << endl;
		}
		else if(type == ERROR_SIGN) {
			cout << "\tZeichen: " << token->getErrorCharacter() << endl;
		}
		else if(type == IDENTIFIER) {
			InfoContainer* info = symboltable->lookup(token->getKey());
			int length = (int) *(info->lexem);
			char* lexem = (info->lexem + 1);
			cout << "\tLexem: ";
			for(int i = 0; i < length; i++) {
				cout << lexem[i];
			}
			if(info->keyword != ID) {
				cout << "\tKeyword: " << keywordStr[info->keyword];
			}
			cout << endl;
		}
		else {
			cout << endl;
		}
	}
 *
 */
