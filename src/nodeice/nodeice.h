
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
	
	/**
	  * helper function and also to conform to the specification already implemented 
	  * across other ICE language bindings. ie, allows for the following:
	  * var ic = ice.initialize("args");//returns a communicator object
	  */
	Handle<Value> InitializeCommunicator(const Arguments& args){
		HandleScope scope;
		Handle<v8::Object> self = args.This();
		Handle<v8::Value> retval = self->Get(String::New("Communicator"));
		if(!retval->IsFunction()){
			return v8::ThrowException(v8::String::New("Node Ice: Communicator object not found on Ice object"));
		}
		Handle<v8::Function> communicator_f = Handle<v8::Function>::Cast(retval);
		Handle<v8::Value>* _args = new Handle<v8::Value>[args.Length()];
		for(int i = 0; i < args.Length();i++){
			_args[i] = args[i];
		}
		Handle<v8::Object> communicator_o = communicator_f->NewInstance(args.Length(),_args);
		return scope.Close(communicator_o);
	}
	
	void Initialize(Handle<v8::Object> target){
		
		HandleScope scope;
		cout << "NodeIce::Initialize" << endl;
		
		Proxy::Initialize(target);
		Communicator::Initialize(target);
		
  		NODE_SET_METHOD(target, "initialize", NodeIce::InitializeCommunicator);
	}
}

#endif /*NODEICE_H*/