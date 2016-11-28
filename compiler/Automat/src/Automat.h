/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *  Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_
#include "Lexem.h"

class State;

class Automat {
    
public:
    
	Automat();
    virtual ~Automat();
    
	void setCurrentState(State *state);
    Lexem* read(char *character);
    
    void incrementColumn();
    void resetColumn();
    int getColumn();
    int getRow();
    void incrementRow();
    
private:
	State *current_state;
    int column;
    int row;
    Lexem *lexem;
};

#endif /* Automat_H_ */
