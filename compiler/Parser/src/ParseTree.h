/*
 * ParseTree.h
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_
#include "NodeType.h"
#include "UnexpectedToken.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
class Scanner;
class Token;
class Symboltable;
using namespace std;

/*
 * ParseTree
 */

class ParseTree{
protected:
 ParseTree *node[3] = {};
 NodeType nodeType = noType;
public:
	virtual ~ParseTree(){}
	static ParseTree* parsetree(Scanner *);

	ParseTree* getNode(int);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable *symboltable){}
	virtual NodeType getNodeType();

};

/*
 * Prog
 */

class Prog: public ParseTree {
public:
	virtual ~Prog(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable *symboltable) = 0;
};

/*
 * Prog
 */

class Prog1: public Prog{
public:
	Prog1();
	~Prog1();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable *symboltable);
};

#endif /* PARSETREE_H_ */
