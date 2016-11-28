#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Symboltable.h"
#include "InfoContainer.h"
using namespace std;

void fill_string_10(char str[])
{
   for (int i=0; i<=10; i++)
     str[i] = 'A' + random() % 26;

}


int main(int argc, char **argv) {

	Symboltable* symboltable;
	symboltable = new Symboltable();

	for (int i = 0; i < 5000; i++) {
		char lexem[11];
	    fill_string_10(lexem);
		symboltable->insert(lexem,10);
	}


	char ende[] = { "ENDE" };
	symboltable->insert(ende,4);
	cout << "Symtabelle test ende";

return 0;
}


