/*
 * ParseTree.cpp
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */

#include <string>
#include <sstream>
#include <iostream>
#include "ParseTree.h"
#include "Declarations.h"
#include "Statements.h"
#include "../../Scanner/src/Scanner.h"
#include "../../Scanner/src/Token.h"
#include "../../Symboltable/src/Symboltable.h"

#include "UnexpectedToken.h"
using namespace std;
/*
 * ParseTree
 */

 ParseTree* ParseTree::parsetree(Scanner *scan){
	return Prog::parsetree(scan);
}

 NodeType ParseTree::getNodeType(){
	return this->nodeType;
 }
 ParseTree* ParseTree::getNode(int a){
	 return this->node[a];
 }

/*
 * Prog
 */

 ParseTree* Prog::parsetree(Scanner *scan){
	Prog1 *prog = new Prog1();
	prog->parsetree(scan);
	return prog;
}

/*
 * Prog1
 */

Prog1::Prog1(){
	//cout<<"Prog1 "<<endl;
}
Prog1::~Prog1(){
	for(int i = 0; i<3;i++){
		if(this->node[i]){
			delete node[i];
		}else{
			break;
		}
	}
//	cout<<"Delete Prog1 "<<endl;
}

void Prog1::parsetree(Scanner *scan){
	scan->nextToken();
	this->node[0] = Declarations::parsetree(scan);
	this->node[1] = Statements::parsetree(scan);

}
void Prog1::typecheck(Symboltable *symboltable){
	node[0]->typecheck(symboltable);
	node[1]->typecheck(symboltable);
	this->nodeType = noType;
}

void Prog1::makeCode(ostringstream &out, Symboltable *symboltable){
	node[0]->makeCode(out,symboltable);
	node[1]->makeCode(out,symboltable);
	out<<" STP ";
}
