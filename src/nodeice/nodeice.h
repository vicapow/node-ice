
#ifndef NODEICE_H
#define NODEICE_H

#include <node.h>
#include <v8.h>
#include <iostream>

using namespace v8;
using namespace node;
using namespace std;

#include "communicator.h"
#include "util.h"

namespace NodeIce{
	
	void Initialize(Handle<v8::Object> target){
		
		HandleScope scope;
		//cout << "NodeIce::Initialize" << endl;
		
		// so that calling ice.initalize() returns a communicator object
		Local<FunctionTemplate> ice_initialize_template = FunctionTemplate::New(Communicator::Initialize);
		NODE_SET_METHOD(target,"initialize",Communicator::Initialize);
		
		Handle<v8::Object> util_o = v8::Object::New();
		Util::Intialize(util_o);
		target->Set(String::NewSymbol("util"),util_o);
	}
}

#endif /*NODEICE_H*/