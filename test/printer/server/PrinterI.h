
#ifndef DEMO_PRINTER_I_H
#define DEMO_PRINTER_I_H
#include <Ice/Ice.h>
#include <Printer.h>

using namespace std;
using namespace Demo;

/**
  * the implementation of our printer interface
  */
class PrinterI : public Printer {
	public:
		virtual void printString(const string& s, const Ice::Current&){
			cout << s << endl;
		}
};

#endif /* DEMO_PRINTER_I_H */