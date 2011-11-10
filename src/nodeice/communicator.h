
#ifndef NODEICE_COMMUNICATOR_WRAPPER_H
#define NODEICE_COMMUNICATOR_WRAPPER_H

#include <node.h>
#include <v8.h>
#include <iostream>
#include <vector>

using namespace v8;
using namespace node;
using namespace std;

// Ice 
#include <Ice/Ice.h>
using namespace Ice;

#include "proxy.h"

class Proxy;

namespace NodeIce{
	class Communicator : ObjectWrap {
		public:
			
			Ice::CommunicatorPtr ic;
			
			Communicator() {
				cout << "Communicator::Constructor" << endl;
			}
			
			
			
			~Communicator(){
				cout << "Communicator::Destructor" << endl;
			}
			
			
			
			/**
			  * returns the communicator pointer given the provided ice arguments
			  * for example: var communicator = nodeice.initialize("args...");
			  */
			static Handle<Value> Initialize(const Arguments &args);
			
			static Handle<Value> StringToProxy(const Arguments &args);
	};
}


#endif