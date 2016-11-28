
#ifndef Lexem_H_
#define Lexem_H_
#include "TokenType.h"

class Lexem {

private:
    
	int bufferBack;
	bool needNext;
    TokenType tokenType;
    
public:
    
	void reset();
    void setBufferBack(int);
    void setTokenType(TokenType);
    void setNeedNext(bool);
    int getBufferBack();
	bool getNeedNext();
    TokenType getTokenType();
    Lexem();
    ~Lexem(){};
};
#endif /* Lexem_H_ */