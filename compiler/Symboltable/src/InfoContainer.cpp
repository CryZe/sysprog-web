#include "InfoContainer.h"
#include "../../Automat/src/TokenType.h"
#include "../../Parser/src/NodeType.h"
InfoContainer::InfoContainer(char* lexem) {
	this->nodeType = noType;
	this->lexem = lexem;
	this->keyword = IDENTIFIER;
}

InfoContainer::~InfoContainer() {


}

NodeType InfoContainer::getNodeType() const {
	return nodeType;
}

void InfoContainer::setNodeType(NodeType nodeType) {
	this->nodeType = nodeType;
}
