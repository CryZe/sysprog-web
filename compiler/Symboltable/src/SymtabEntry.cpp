#include "SymtabEntry.h"
#include <iostream>
using namespace std;

SymtabEntry::SymtabEntry(char* lexem) {
	info = new InfoContainer(lexem);
	next = 0;
}


bool SymtabEntry::compareLex(char* lexem, int size){
	bool isEqual = true;
	//sonst wird bei size >130 fehler passieren
	if( (unsigned char) this->info->lexem[0] != size){
		return false;
	} else {
		for(int i=0; i< size; i++){
			if(this->info->lexem[i+1] != lexem[i]) return false;
		}
	}
	return isEqual;
}


SymtabEntry::~SymtabEntry() {
	delete info;
}
