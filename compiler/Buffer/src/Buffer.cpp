/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "Buffer.h"
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

Buffer::Buffer(const char* data) throw (exception){
	next = data;
}

Buffer::~Buffer() {
}

char* Buffer::getNextChar(){
	return (char*)(next++);
}

void Buffer::goBack(unsigned int steps){
	next -= steps;
}


