
#include <iostream>
using namespace std;

#include <Ice/Ice.h>

#include "PrinterI.h"

int main(int argc, char* argv[]){
	int status = 1;
	Ice::CommunicatorPtr ic;
	try{
		// server code here...
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("SimplePrinterAdapter","default -p 10000");
		// instantiate and register one or more servants here...
		Ice::ObjectPtr simplePrinter = new PrinterI();
		adapter->add(simplePrinter, ic->stringToIdentity("SimplePrinter"));
		adapter->activate();
		ic->waitForShutdown();
		status = 0;
	}catch(const Ice::Exception& e){
		cerr << "error initailizing server" << endl;
		cerr << e << endl;
		status = 1;
	}catch(const char* msg){
		cerr << msg << endl;
		status = 1;
	}
	if(ic){
		try{
			ic->destroy();
		}catch(const Ice::Exception& e){
			cerr << e << endl;
			status = 1;
		}
	}
	return status;
}