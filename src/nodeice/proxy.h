
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
	class Proxy : ObjectWrap {
		
		protected:
			Ice::ObjectPrx base;
		
		public:
			
			Proxy() {
				//cout << "Proxy::Constructor" << endl;
			}
			
			~Proxy(){
				//cout << "Proxy::Destructor" << endl;
			}
			
			void sayHello(){
				cout << "Hello from proxy!" << endl;
			}
			
			void setBase(Ice::ObjectPrx base){
				this->base = base;
			}
			
			static Handle<Value> Initialize(const Arguments &args);
	};
}


#endif