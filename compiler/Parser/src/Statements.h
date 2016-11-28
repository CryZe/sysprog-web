/*
 * Statements.h
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */

#ifndef STATEMENTS_H_
#define STATEMENTS_H_
#include "ParseTree.h"
class Token;

/*
 * Statements
 */
class Statements: public ParseTree {
public:
	virtual ~Statements(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};

/*
 * Statements1
 */
class Statements1: public Statements{
public:
	Statements1();
	virtual ~Statements1();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Statements2
 */
class Statements2: public Statements{
public:
	Statements2();
	virtual ~Statements2();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Statement
 */
class Statement: public ParseTree {
public:
	virtual ~Statement(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};

/*
 * Statement1
 */
class Statement1: public Statement{
private:
	Token *token;
public:
	Statement1();
	virtual ~Statement1();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Statement2
 */
class Statement2: public Statement{

public:
	Statement2();
	virtual ~Statement2();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Statement3
 */
class Statement3: public Statement{
private:
	Token *token;
public:
	Statement3();
	virtual ~Statement3();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Statement4
 */
class Statement4: public Statement{
public:
	Statement4();
	virtual ~Statement4();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};


/*
 * Statement5
 */
class Statement5: public Statement{
private:
	static int labelCount;
public:
	Statement5();
	static void reset() {
		labelCount = 1;
	}
	virtual ~Statement5();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Statement6
 */
class Statement6: public Statement{
private:
	static int labelCount;
public:
	Statement6();
	static void reset() {
		labelCount = 1;
	}
	virtual ~Statement6();
	void parsetree(Scanner*);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
#endif /* STATEMENTS_H_ */
