/*
 * State.h
 *
 *  Created on: 23.10.2013
 *  Author: craw
 *  Edit by : Henrik Hierl
 */

#ifndef STATE_H_
#define STATE_H_
#include "Automat.h"
// Forward declarations
class Automat;

class State{
    
public:
	virtual void read(char c, Automat* automat ,Lexem* lexem) = 0;
	virtual ~State(){};
};

/*
 *
 *InitialState
 *
 */

class InitialState: public State{
    
private:
	InitialState(){};
	static State *state;

public:
	virtual void read(char c, Automat* automat ,Lexem* lexem);
	static State* getState();
};

/*
 *
 * DigitState
 *
 */

class DigitState: public State{
    
private:
	DigitState(){};
	static State *state;
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};

/*
 *
 * IdentifierState
 *
 */

class IdentifierState: public State{
    
private:
	IdentifierState(){};
	static State *state;
    
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};

/*
 *
 * SlashState
 *
 */

class SlashState: public State{
    
private:
    SlashState(){};
    static State *state;
    
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};

/*
 *
 * SlashStarState
 *
 */

class SlashStarState: public State{
    
private:
    SlashStarState(){};
    static State *state;
    
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};

/*
 *
 * SlashStarEndState
 * Neu benennen
 */

class SlashStarEndState: public State{
    
private:
    SlashStarEndState(){};
    static State *state;
    
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};

/*
 *
 * EqualState
 *
 */
class EqualState: public State{
    
private:
    EqualState(){};
    static State *state;
    
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};

/*
 *
 * EqualNotState
 *
 */
class EqualNotState: public State{
    
private:
    EqualNotState(){};
    static State *state;
    
public:
    virtual void read(char c, Automat* automat ,Lexem* lexem);
    static State* getState();
};


#endif /* STATE_H_ */
