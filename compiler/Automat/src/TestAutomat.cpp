
#include "Automat.h"
#include <iostream>
#include "State.h"
using namespace std;

int main (int argc, char* argv[]){
	
    Automat* automat;
    
    char test ='/';
    char teste ='*';
    char testeeee ='*';
    char testee ='*';
    char testeee ='/';
	automat = new Automat();
    automat->read(&test);
    automat->read(&teste);
    automat->read(&testeeee);
    automat->read(&teste);
    automat->read(&testee);
    automat->read(&testeee);
    delete automat;
	return 0;
}
