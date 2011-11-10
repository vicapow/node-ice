
#ifndef NODEICE_H
#define NODEICE_H

#include <node.h>
#include <v8.h>
#include <iostream>

using namespace v8;
using namespace node;
using namespace std;

#include "communicator.h"

namespace NodeIce{
	
	void Initialize(Handle<v8::Object> target){
		
		HandleScope scope;
		cout << "NodeIce::Initialize" << endl;
		
		// just an example for now
		target->Set( String::New("Communicator"), String::New("this is a string") );
		
		Local<FunctionTemplate> ice_initialize_template = FunctionTemplate::New(Communicator::Initialize);
		target->Set( String::New("initialize"),ice_initialize_template->GetFunction());
		// calling ice.initalize() returns a communicator object
		
	}
}

#endif /*NODEICE_H*/