#include "Symboltable.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../../Automat/src/TokenType.h"
//#include "Type.h"
using namespace std;

Symboltable::Symboltable() {
	Stringtable = GetNewStringtable();
	// Set keywords

	char key_while[] = { "while" };
	InfoContainer* info1 = insert(key_while,5);
	info1->keyword = KEYWORD_WHILE;

	char key_WHILE[] = { "WHILE" };
	InfoContainer* info2 = insert(key_WHILE,5);
	info2->keyword = KEYWORD_WHILE;

	char key_else[] = { "else" };
	InfoContainer* info3 = insert(key_else,4);
	info3->keyword = KEYWORD_ELSE;

	char key_ELSE[] = { "ELSE" };
	InfoContainer* info4 = insert(key_ELSE,4);
	info4->keyword = KEYWORD_ELSE;

	char key_if[] = { "if" };
	InfoContainer* info5 = insert(key_if,2);
	info5->keyword = KEYWORD_IF;

	char key_IF[] = { "IF" };
	InfoContainer* info6 = insert(key_IF,2);
	info6->keyword = KEYWORD_IF;

	char key_print[] = { "print" };
	InfoContainer* info7 = insert(key_print,5);
	info7->keyword = KEYWORD_PRINT;

	char key_read[] = { "read" };
	InfoContainer* info8 = insert(key_read,4);
	info8->keyword = KEYWORD_READ;

	char key_int[] = { "int" };
	InfoContainer* info9 = insert(key_int,3);
	info9->keyword = KEYWORD_INT;

}

char* Symboltable::GetNewStringtable(){
	freeSpace = SPACE;
	freeP = new char[SPACE];
	if(rootPointer == 0){
	  rootPointer = new CharNode;
	  rootPointer->data = freeP;
	  rootPointer->next = 0;
	  current = rootPointer;
	} else {
	  last = current;
	  current = new CharNode;
	  current->data = freeP;
	  current->next = 0;
	  last->next = current;
	}
	return freeP;
}

char* Symboltable::InsertIntoStringtable(char* lexem, int size){
	// Noch platz frei
	char* currentLexem = freeP;
	if (size < this->freeSpace){
		memcpy(this->freeP+1,lexem,size);
		this->freeP[0] = (char) size;
		this->freeP += size+1;
		this->freeSpace -= size+1;
	} else {
        // Neuen Platz reservieren
	    Stringtable = GetNewStringtable();
	    currentLexem = Stringtable;
		if (size < this->freeSpace){
	      memcpy(this->freeP+1,lexem,size);
		  this->freeP[0] = (char) size;
		  this->freeP += size+1;
		  this->freeSpace -= size+1;
		} else cerr << "Identifier nur 8 Bit möglich!"<< endl;
	 }
	 return currentLexem;
}

InfoContainer* Symboltable::insert(char* lexem, int size){// HashIndex
	int index = HashCode(lexem,size);
	// Index noch frei -> Lexem nicht vorhanden
	if(HashMap[index] == 0){
		SymtabEntry *root;
		root = new SymtabEntry(InsertIntoStringtable(lexem,size));
		root->next = 0;
		HashMap[index] = root;
		return root->info;
	} else {
	// Index nicht mehr frei -> prüfen
	  SymtabEntry *node = HashMap[index];
	  SymtabEntry *last;
	  do{
	    if(node->compareLex(lexem,size)) return node->info; // Lexem wurde gefunden und wir brauche keins anzulegen
	    last = node;
		node = node->next;
	  } while(node != 0);
	  // Lexem wurde nicht gefunden -> neues anlegen
	  last->next = new SymtabEntry(InsertIntoStringtable(lexem,size));
	  return last->next->info;
	}
}

int Symboltable::HashCode(char* lexem, int size){
	unsigned int  h = 31;
	for(int i=0; i < size; i++) h = (h * 65599) ^ (lexem[i] * 76963);
	return h % HASHMAP;
}

Symboltable::Key Symboltable::lookup(InfoContainer* key){
  return key;
}

Symboltable::~Symboltable() {
	// Delete Lexem Array's
	while(rootPointer != 0){
		CharNode* help = rootPointer;
		rootPointer = rootPointer->next;
		delete[] help->data;
		delete help;
	}
	// Delete SymtabEntry's
	for(int i = 0; i < HASHMAP; i++){
		SymtabEntry* is_SymtabEntry_object = dynamic_cast<SymtabEntry*>(HashMap[i]);
		if(is_SymtabEntry_object){
			SymtabEntry *node = HashMap[i];
			while(node != 0){
				SymtabEntry *help = node;
				node = node->next;
				delete help;
			}
		}
	}
}
