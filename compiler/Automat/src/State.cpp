#include "State.h"
#include <ctype.h>


/*
 *
 *InitialState
 *
 */

void InitialState::read(char c, Automat* automat ,Lexem* lexem){
    if(isalpha(c)){
		//Wechseln zum IdentifierState
        automat->setCurrentState(IdentifierState::getState());
        automat->incrementColumn();
        //Need next True
        lexem->setNeedNext(true);
        lexem->setBufferBack(0);
        lexem->setTokenType(IDENTIFIER);
        
	} else  if(isdigit(c)){
		//Wechseln zum DigitState
        automat->setCurrentState(DigitState::getState());
        automat->incrementColumn();
        //Need next True
        lexem->setNeedNext(true);
        lexem->setBufferBack(0);
        lexem->setTokenType(INTEGER);
    }else{
        switch (c) {
            case '=':
                //Wechseln zum EqualState
                automat->setCurrentState(EqualState::getState());
                automat->incrementColumn();
                
                lexem->setNeedNext(true);
                lexem->setBufferBack(0);
                lexem->setTokenType(EQUALS_SIGN);
                break;
            case '/':
                //Wechseln zum SlashState
                automat->setCurrentState(SlashState::getState());
                automat->incrementColumn();
                
                lexem->setNeedNext(true);
                lexem->setBufferBack(0);
                lexem->setTokenType(SLASH_SIGN);
                break;
            case '+':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(PLUS_SIGN);
                break;
            case '-':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(HYPHEN_SIGN);
                break;
            case ';':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(SEMICOLON_SIGN);
                break;
            case '<':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(LESS_THAN_SIGN);
                break;
            case '>':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(MORE_THAN_SIGN);
                break;
            case '*':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(STAR_SIGN);
                break;
            case '!':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(NOT_SIGN);
                break;
            case '&':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(AND_SIGN);
                break;
            case '(':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(PARENTHESIS_OPEN_SIGN);
                break;
            case ')':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(PARENTHESIS_CLOSE_SIGN);
                break;
            case '{':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(BRACES_OPEN_SIGN);
                break;
            case '}':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(BRACES_CLOSED_SIGN);
                break;
            case '[':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(SQUARE_BRACKET_OPEN_SIGN);
                break;
            case ']':
                automat->incrementColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(SQUARE_BRACKET_CLOSE_SIGN);
                break;
            case'\t':
            	automat->incrementColumn();
            	automat->incrementColumn();
            	automat->incrementColumn();
            case ' ':
                automat->incrementColumn();
                //Bleib
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(SPACE_SIGN);
                break;
            case '\n':
                automat->incrementRow();
                automat->resetColumn();
                //Bleibt
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(SPACE_SIGN);
                break;
                /*Windows sonder Fall wird nicht mitgezählt*/
            case '\r':
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(SPACE_SIGN);
                break;
            case '\0':
                //Datei ende
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(FILE_END);
                break;
            default:
                automat->incrementColumn();
                //Fehler
                lexem->setNeedNext(false);
                lexem->setBufferBack(0);
                lexem->setTokenType(ERROR_SIGN);
                break;
        }
    }
    
}

State* InitialState::state = 0;

State* InitialState::getState(){
	if( !(state) ){
		state = new InitialState();
	}
	return state;
}

/*
 *
 * DigitState
 *
 */

State* DigitState::state = 0;

State* DigitState::getState(){
	if( !(state) ){
		state = new DigitState();
	}
	return state;
}

void DigitState::read(char c, Automat* automat ,Lexem* lexem){
	if(isdigit(c)){
		// Bleibt im state
        automat->incrementColumn();
        lexem->setNeedNext(true);
        lexem->setBufferBack(0);
        lexem->setTokenType(INTEGER);
        
	} else if(isalpha(c)){
        //Column wird nicht erhöht da das zeichen nochmal gelesen wird
        automat->setCurrentState(InitialState::getState());
        
        lexem->setNeedNext(false);
        lexem->setBufferBack(1);
        lexem->setTokenType(INTEGER);
    }
    else{
        switch (c) {
        	case'\t':
        		automat->incrementColumn();
        		automat->incrementColumn();
        		automat->incrementColumn();
            case ' ':
                automat->incrementColumn();
                automat->setCurrentState(InitialState::getState());
                
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(INTEGER);
                break;
            case '\n':
                automat->resetColumn();
                automat->incrementRow();
                automat->setCurrentState(InitialState::getState());
                
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(INTEGER);
                break;
            case '\0':
            case '=':
            case '/':
            case '+':
            case '-':
            case ';':
            case '<':
            case '>':
            case '*':
            case '!':
            case '&':
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            default:
                //Column wird nicht erhöht da das zeichen nochmal gelesen wird
                automat->setCurrentState(InitialState::getState());
                
                lexem->setNeedNext(false);
                lexem->setBufferBack(1);
                lexem->setTokenType(INTEGER);
                break;
        }

    }
}

/*
 *
 * IdentifierState
 *
 */

State* IdentifierState::state = 0;

State* IdentifierState::getState(){
	if( !(state) ){
		state = new IdentifierState();
	}
	return state;
}


void IdentifierState::read(char c, Automat* automat ,Lexem* lexem){
	if(isalpha(c)||isdigit(c)){
		// Bleibt im state
        automat->incrementColumn();
        //Need next True
        lexem->setNeedNext(true);
        lexem->setBufferBack(0);
        lexem->setTokenType(IDENTIFIER);
	} else {
		switch (c) {
			case'\t':
				automat->incrementColumn();
				automat->incrementColumn();
				automat->incrementColumn();
            case ' ':
                automat->incrementColumn();
                automat->setCurrentState(InitialState::getState());
                
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(IDENTIFIER);
                break;
            case '\n':
                automat->resetColumn();
                automat->incrementRow();
                automat->setCurrentState(InitialState::getState());
                
                lexem->setNeedNext(false);
                lexem->setBufferBack(-1);
                lexem->setTokenType(IDENTIFIER);
                break;
            case '\0':
            case '=':
            case '/':
            case '+':
            case '-':
            case ';':
            case '<':
            case '>':
            case '*':
            case '!':
            case '&':
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            default:
                //Column wird nicht erhöht da das zeichen nochmal gelesen wird
                automat->setCurrentState(InitialState::getState());
                
                lexem->setNeedNext(false);
                lexem->setBufferBack(1);
                lexem->setTokenType(IDENTIFIER);
                break;
        }
	}
}

/*
 *
 * SlashState
 *
 */

State* SlashState::state = 0;

State* SlashState::getState(){
	if( !(state) ){
		state = new SlashState();
	}
	return state;
}


void SlashState::read(char c, Automat* automat ,Lexem* lexem){
    switch (c) {
        case '*':
            //Kommentar
            automat->setCurrentState(SlashStarState::getState());
            automat->incrementColumn();
            lexem->setTokenType(SPACE_SIGN);
            lexem->setNeedNext(false);
            lexem->setBufferBack(-2);
            break;
        case'\t':
        	automat->incrementColumn();
        	automat->incrementColumn();
        	automat->incrementColumn();
        case ' ':
            //
            automat->setCurrentState(InitialState::getState());
            automat->incrementColumn();
            lexem->setBufferBack(-1);
            lexem->setNeedNext(false);
            lexem->setTokenType(SLASH_SIGN);
            break;
        case '\n':
            automat->setCurrentState(InitialState::getState());
            automat->incrementRow();
            automat->resetColumn();
            
            lexem->setBufferBack(-1);
            lexem->setNeedNext(false);
            lexem->setTokenType(SLASH_SIGN);
            break;
            
        default:
            automat->setCurrentState(InitialState::getState());
            
            lexem->setNeedNext(false);
            lexem->setBufferBack(1);
            lexem->setTokenType(SLASH_SIGN);
            break;
            break;
    }
    
}
/*
 *
 * SlashStarState
 *
 */

State* SlashStarState::state = 0;

State* SlashStarState::getState(){
	if( !(state) ){
		state = new SlashStarState();
	}
	return state;
}


void SlashStarState::read(char c, Automat* automat ,Lexem* lexem){
    switch (c) {
        case '*':
            //Zurück TO DOO
            automat->setCurrentState(SlashStarEndState::getState());
            automat->incrementColumn();
            //Rest vom lexem bleibt auf false und Spacesign
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            break;
        case '\n':
            automat->resetColumn();
            automat->incrementRow();
            //Rest vom lexem bleibt auf false und Spacesign
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            break;
        /*Windows sonderfall*/
        case '\r':
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            break;
        case '\0':
            //Datei ende
            lexem->setNeedNext(false);
            lexem->setBufferBack(0);
            lexem->setTokenType(FILE_END);
            break;
        case'\t':
        	automat->incrementColumn();
        	automat->incrementColumn();
        	automat->incrementColumn();
        default:
            automat->incrementColumn();
            //Rest vom lexem bleibt auf True und Spacesign
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            break;
    }
}
/*
 *
 * SlashStarEndState
 *
 */

State* SlashStarEndState::state = 0;

State* SlashStarEndState::getState(){
	if( !(state) ){
		state = new SlashStarEndState();
	}
	return state;
}


void SlashStarEndState::read(char c, Automat* automat ,Lexem* lexem){
    switch (c) {
        case '/':
            automat->setCurrentState(InitialState::getState());
            automat->incrementColumn();
            lexem->setBufferBack(-1);
            lexem->setNeedNext(false);
            lexem->setTokenType(SPACE_SIGN);
            break;
        case '\n':
            automat->setCurrentState(SlashStarState::getState());
            automat->incrementRow();
            automat->resetColumn();
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            lexem->setTokenType(SPACE_SIGN);
            break;
        case '\0':
            //Datei ende
            lexem->setNeedNext(false);
            lexem->setBufferBack(0);
            lexem->setTokenType(FILE_END);
            break;
        case'\t':
        	automat->incrementColumn();
        	automat->incrementColumn();
        	automat->incrementColumn();
        default:
            automat->setCurrentState(SlashStarState::getState());
            automat->incrementColumn();
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            lexem->setTokenType(SPACE_SIGN);
            break;
    }
}


/*
 *
 * EqualState
 *
 */

State* EqualState::state = 0;

State* EqualState::getState(){
	if( !(state) ){
		state = new EqualState();
	}
	return state;
}


void EqualState::read(char c, Automat* automat ,Lexem* lexem){
    
    switch (c) {
        case '!':
            automat->setCurrentState(EqualNotState::getState());
            
            lexem->setNeedNext(true);
            lexem->setBufferBack(0);
            lexem->setTokenType(EQUALS_SIGN);
            break;
        case '=':
            automat->setCurrentState(InitialState::getState());
            automat->incrementColumn();
            
            lexem->setNeedNext(false);
            lexem->setBufferBack(0);
            lexem->setTokenType(DOUBLE_EQUALS_SIGN);
            break;
        case'\t':
        	automat->incrementColumn();
        	automat->incrementColumn();
        	automat->incrementColumn();
        case ' ':
            automat->incrementColumn();
            automat->setCurrentState(InitialState::getState());
            
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            lexem->setTokenType(EQUALS_SIGN);
            break;
        case '\n':
            automat->resetColumn();
            automat->incrementRow();
            automat->setCurrentState(InitialState::getState());
            
            lexem->setNeedNext(false);
            lexem->setBufferBack(-1);
            lexem->setTokenType(EQUALS_SIGN);
            break;
        default:
            //Column wird nicht erhöht da das zeichen nochmal gelesen wird
            automat->setCurrentState(InitialState::getState());
            
            lexem->setNeedNext(false);
            lexem->setBufferBack(1);
            lexem->setTokenType(EQUALS_SIGN);
            break;
    }
    
}


/*
 *
 * EqualNotState
 *
 */

State* EqualNotState::state = 0;

State* EqualNotState::getState(){
	if( !(state) ){
		state = new EqualNotState();
	}
	return state;
}


void EqualNotState::read(char c, Automat* automat ,Lexem* lexem){
    switch (c) {
        case '=':
            //erhöht um zwei da vorher nicht erhöht wurde um ein Rückschrit zu vermeiden
            automat->incrementColumn();
            automat->incrementColumn();
            automat->setCurrentState(InitialState::getState());
            
            lexem->setTokenType(EQUAL_NOT_EQUAL_SIGN);
            lexem->setNeedNext(false);
            lexem->setBufferBack(0);
            break;
            
        default:
            //um zwei zurück gehn und (= Sign)
            automat->setCurrentState(InitialState::getState());
            lexem->setBufferBack(2);
            lexem->setNeedNext(false);
            lexem->setTokenType(EQUALS_SIGN);
            break;
    }
    
}
