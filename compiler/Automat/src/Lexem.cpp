#include "Lexem.h"
/*
 * State.h
 *
 *  Created on: 30.10.2013
 *  Author: Henrik Hierl
 */

Lexem::Lexem(){
    bufferBack = 0;
    needNext = false;
    tokenType = ERROR_SIGN;
}

void Lexem::reset() {
    bufferBack = 0;
    needNext = false;
    tokenType = ERROR_SIGN;
}

void Lexem::setBufferBack(int value){
    bufferBack = value;
}
void Lexem::setTokenType(TokenType token){
    tokenType=token;
}
void Lexem::setNeedNext(bool value){
    needNext = value ;
}

int Lexem::getBufferBack(){
    return bufferBack;
}
bool Lexem::getNeedNext(){
    return needNext;
}
TokenType Lexem::getTokenType(){
    return tokenType;
}