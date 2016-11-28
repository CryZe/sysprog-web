/*
 * Expression.h
 *
 *  Created on: 04.12.2013
 *      Author: rainer
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include "ParseTree.h"
class Token;
using namespace std;

/*
 * Expression
 */
class Expression: public ParseTree{
public:
	virtual ~Expression(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};
/*
 * Expression1
 */
class Expression1: public Expression{
public:
	Expression1();
	virtual ~Expression1();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Expression2_0
 */
class Expression2_0: public ParseTree{
public:
	virtual ~Expression2_0(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};
/*
 * Expression2_1
 */
class Expression2_1: public Expression2_0{
public:
	Expression2_1();
	virtual ~Expression2_1();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Expression2_2
 */
class Expression2_2: public Expression2_0{
private:
	Token *token;
public:
	Expression2_2();
	virtual ~Expression2_2();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Expression2_3
 */
class Expression2_3: public Expression2_0{
private:
	Token *token;
public:
	Expression2_3();
	virtual ~Expression2_3();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Expression2_4
 */
class Expression2_4: public Expression2_0{
public:
	Expression2_4();
	virtual ~Expression2_4();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Expression2_5
 */
class Expression2_5: public Expression2_0{
public:
	Expression2_5();
	virtual ~Expression2_5();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Index
 */
class Index: public ParseTree{
public:
	virtual ~Index(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};
/*
 * Index1
 */
class Index1: public Index{
public:
	Index1();
	virtual ~Index1();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Index2
 */
class Index2: public Index{
public:
	Index2();
	virtual ~Index2();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*){}
};
/*
 * Operant_Exprssion
 */
class Operant_Exprssion: public ParseTree{
public:
	virtual ~Operant_Exprssion(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};
/*
 * Operant_Exprssion1
 */
class Operant_Exprssion1: public Operant_Exprssion{
public:
	Operant_Exprssion1();
	virtual ~Operant_Exprssion1();
	void parsetree(Scanner *);
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant_Exprssion2
 */
class Operant_Exprssion2: public Operant_Exprssion{
public:
	Operant_Exprssion2();
	virtual ~Operant_Exprssion2();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*){}
};
/*
 * Operant
 */
class Operant: public ParseTree{
public:
	virtual ~Operant(){}
	static ParseTree* parsetree(Scanner *);
	virtual void typecheck(Symboltable *) = 0;
	virtual void makeCode(ostringstream &, Symboltable*) = 0;
};
/*
 * Operant1
 */
class Operant1: public Operant{
public:
	Operant1();
	virtual ~Operant1();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant2
 */
class Operant2: public Operant{
public:
	Operant2();
	virtual ~Operant2();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant3
 */
class Operant3: public Operant{
public:
	Operant3();
	virtual ~Operant3();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant4
 */
class Operant4: public Operant{
public:
	Operant4();
	virtual ~Operant4();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant5
 */
class Operant5: public Operant{
public:
	Operant5();
	virtual ~Operant5();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant6
 */
class Operant6: public Operant{
public:
	Operant6();
	virtual ~Operant6();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant7
 */
class Operant7: public Operant{
public:
	Operant7();
	virtual ~Operant7();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant8
 */
class Operant8: public Operant{
public:
	Operant8();
	virtual ~Operant8();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
/*
 * Operant9
 */
class Operant9: public Operant{
public:
	Operant9();
	virtual ~Operant9();
	virtual void typecheck(Symboltable *);
	virtual void makeCode(ostringstream &, Symboltable*);
};
#endif /* EXPRESSION_H_ */
