/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_
#include <exception>
#include <pthread.h>
class Buffer {
public:
	Buffer(const char* data)throw( std::exception );
	char* getNextChar();
	void goBack(unsigned int steps);
	virtual ~Buffer();

private:
	const char *next;
};


#endif /* BUFFER_H_ */
