
#ifndef NODEICE_PROXY_WRAPPER_H
#define NODEICE_PROXY_WRAPPER_H

#include <node.h>
#include <v8.h>
#include <iostream>
#include <vector>

using namespace v8;
using namespace node;
using namespace std;

// Ice 
#include <Ice/Ice.h>
//using namespace Ice;

#include "communicator.h"

namespace NodeIce{

/**
  * a wrapper for the Ice Object Proxy (aka, ObjectPrx)
  */
class Proxy : ObjectWrap {
	
	public:
		
		Proxy(); // constructor
		
		static Handle<Value> Initialize(const Handle<v8::Object> target);
		
		// the ICE ObjectPrx object for more details, reference the ICE documentation
		Ice::ObjectPrx base;
		
	protected:
		
		// member functions
		static Handle<Value> New(const Arguments& args);
};
	
}


#endif