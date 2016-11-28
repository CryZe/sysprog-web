/*
 * TypecheckError.cpp
 *
 *  Created on: 17.12.2013
 *      Author: henrik
 */

#include "TypecheckError.h"

TypecheckError::~TypecheckError() {
	// TODO Auto-generated destructor stub
}

TypecheckError::TypecheckError() {
	this->valueOfError = 0;
}

TypecheckError* TypecheckError::singelton = 0;

TypecheckError* TypecheckError::getTypecheckError(){
if(!(singelton)){
		singelton = new TypecheckError();
	}else
	{
		singelton->valueOfError++;
	}
	return singelton;
}

void TypecheckError::reset() {
    if(singelton) {
        singelton->valueOfError = -1;
    }
}
