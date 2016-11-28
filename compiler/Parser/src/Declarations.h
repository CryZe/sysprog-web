/*
 * Declarations.h
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */


#ifndef DECLARATIONS_H_
#define DECLARATIONS_H_
#include <string>
#include <sstream>
#include "ParseTree.h"
#include "UnexpectedToken.h"


/*
 * Declarations
 */

class Declarations : public ParseTree {

public:
	virtual ~Declarations(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *)  = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;

};

/*
 * Declarations1
 */

class Declarations1 : public Declarations {
public:
	Declarations1();
	 ~Declarations1();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Declarations2
 */

class Declarations2 : public Declarations {
public:
	Declarations2();
	 ~Declarations2();
	void parstree(Scanner *);
	virtual void typecheck(Symboltable *){this->nodeType = noType;}
	virtual void makeCode(ostringstream &, Symboltable*){}
};
/*
 * Declaration
 */
class Declaration : public ParseTree {
public:
	virtual ~Declaration(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};

/*
 * Declaration1
 */

class Declaration1 : public Declaration{
private:
	 Token	*token;
public:
	Declaration1();
	 ~Declaration1();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Array
 */

class Array : public ParseTree{

public:
	virtual ~Array(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};

/*
 * Array1
 */

class Array1 : public Array{
private:
	Token *token;
public:
	Array1();
	 ~Array1();
	 void parsetree(Scanner *);
	 virtual void typecheck(Symboltable *);
	 virtual void makeCode(ostringstream &, Symboltable*);
};

/*
 * Array2
 */

class Array2 : public Array{
public:
	Array2();
	 ~Array2();
	 virtual void typecheck(Symboltable *);
	 virtual void makeCode(ostringstream &, Symboltable*);
};
#endif /* DECLARATIONS_H_ */
