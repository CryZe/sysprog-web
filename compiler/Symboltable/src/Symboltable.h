#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_
#include "SymtabEntry.h"
class Symboltable {
public:

	Symboltable();
	InfoContainer* insert(char* lexem, int length);
	InfoContainer* lookup(InfoContainer* key);
	static int HashCode(char* lexem, int size);
	virtual ~Symboltable();
	typedef InfoContainer* Key;
private:
	char* GetNewStringtable();
	char* InsertIntoStringtable(char* lexem, int size);
	char* freeP;
    int freeSpace;
	char* Stringtable;
	static const int SPACE = 4000;     // Array of lexem's
	static const int HASHMAP = 1000;  // HashMap length
	SymtabEntry* HashMap[HASHMAP];
	struct CharNode
	{
	      char* data;
	      CharNode *next;
	};
	CharNode* rootPointer;
	CharNode* current;
	CharNode* last;
};

#endif /* SYMBOLTABLE_H_ */

