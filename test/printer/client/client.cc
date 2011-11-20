
#include <iostream>
using namespace std;

#include <Ice/Ice.h>

#include <Printer.h>
using namespace Demo;

/**
  * this is the test client we'll be using to test our test server.
  */
int main(int argc, char* argv[]){
	int status = 0;
	Ice::CommunicatorPtr ic;
	try {
		ic = Ice::initialize(argc,argv);
		// were 'SimplePrinter' is the servent name we provided to the adapter. (not the adapater name itself)
		Ice::ObjectPrx base = ic->stringToProxy("SimplePrinter:default -p 10000");// the printer proxy
		PrinterPrx printer = PrinterPrx::checkedCast(base);// cast it to the apporicate type
		if(!printer){
			throw "Invalid proxy. (check cast type)";
		}
		printer->printString("Hello World!");
		// client code here...
		status = 0; //success status
	}catch(const Ice::Exception& e){
		cerr << e << endl;
		status = 1; //error status
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