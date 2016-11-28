/*
 * Automat.cpp
 *
 */

#include "Automat.h"
#include "State.h"
#include <stdio.h>

Automat::Automat() {
    //Initialisiert den currentState
	current_state = InitialState::getState();
    row=1;
    column=1;
    lexem = new Lexem();
}

Lexem* Automat::read(char *character){
    current_state->read(*character , this, lexem);
    return lexem;
}

Automat::~Automat() {
	delete lexem;
    // delete InitialState::getState();
    // delete DigitState::getState();
    // delete IdentifierState::getState();
    // delete EqualState::getState();
    // delete EqualNotState::getState();
    // delete SlashState::getState();
    // delete SlashStarState::getState();

}

void Automat::setCurrentState(State * state){
    this->current_state = state;
}

void Automat::incrementColumn(){
    column ++;
}
void Automat::resetColumn(){
    column=1;
}
int Automat::getColumn(){
    return column;
}
int Automat::getRow(){
    return row;
}
void Automat::incrementRow(){
    row ++;
}
