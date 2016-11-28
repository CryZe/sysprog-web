#include "Buffer.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {

	Buffer*  buffer;
	try{
	buffer = new Buffer("/home/henrik/git/SystemProgrammierung/Buffer/srcs/data.txt");
	}catch(exception &e){
		cerr<<"exception"<<endl;
		return 0;
	}

    char *test;
    for(int i=0;i<400;i++){
    	test = buffer->getNextChar();

    	    cout<< *test<<endl;
    }

    cout<<*test<<endl;


    for(int i=0;i<20;i++){
    	test = buffer->getNextChar();
    	cout<< *test<<endl;
    }
    delete buffer;
}
