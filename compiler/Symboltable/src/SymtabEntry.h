/*
 * SymtabEntry.h
 *
 *  Created on: 04.11.2013
 *      Author: craw
 */

#ifndef SYMTABENTRY_H_
#define SYMTABENTRY_H_
#include "InfoContainer.h"
class SymtabEntry {
public:
	SymtabEntry(char* lexem);
	bool compareLex(char* lexem, int size);
	InfoContainer* info;
	SymtabEntry* next;
	virtual ~SymtabEntry();
private:

};

#endif /* SYMTABENTRY_H_ */
