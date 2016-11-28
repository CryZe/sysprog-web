/*
 * TypecheckError.h
 *
 *  Created on: 17.12.2013
 *      Author: henrik
 */

#ifndef TYPECHECKERROR_H_
#define TYPECHECKERROR_H_

class TypecheckError {
private:
	static TypecheckError* singelton;
	int valueOfError;
	TypecheckError();
public:
	virtual ~TypecheckError();
	static TypecheckError* getTypecheckError();
	static void reset();

	int getValueOfError() const {
		return valueOfError;
	}
};

#endif /* TYPECHECKERROR_H_ */
