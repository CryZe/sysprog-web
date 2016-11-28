/*
 * InfoContainer.h
 *
 *  Created on: 04.11.2013
 *      Author: craw
 */
//#include "Type.h"

#ifndef INFOCONTAINER_H_
#define INFOCONTAINER_H_
#include "../../Parser/src/NodeType.h"
#include "../../Automat/src/TokenType.h"

class InfoContainer {
public:
	InfoContainer(char* lexem);
	char* lexem;
	TokenType keyword;
	virtual ~InfoContainer();

	NodeType getNodeType() const ;

	void setNodeType(NodeType nodeType);

private:
	NodeType nodeType;
};

#endif /* INFOCONTAINER_H_ */
