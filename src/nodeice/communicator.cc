

#include "communicator.h"

namespace NodeIce{


static Persistent<FunctionTemplate> communicator_constructor;

/**
  * initialize the function template.
  * this is equivilent to:
  * var Communicator = function() { ..Initialize.. }
  * by passing the target module this is as if we did the following:
  * Ice.Communicator = Communicator
  * and then, whenever we wanted a new instance of a communicator:
  * var communicator = new Ice.Communicator("...");
  */
Handle<Value> Communicator::Initialize(const Handle<v8::Object> target){
	HandleScope scope;
	
	cout << "Proxy::Initialize" << endl;
	
	Local<FunctionTemplate> t = FunctionTemplate::New(Communicator::New);
	communicator_constructor = Persistent<FunctionTemplate>::New(t);
	
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(String::NewSymbol("Communicator"));
	
	// set methods
	NODE_SET_PROTOTYPE_METHOD(t,"stringToProxy",Communicator::StringToProxy);
	
	target->Set(String::NewSymbol("Communicator"), t->GetFunction());
}


/** 
  * this function is called when the communicator function is called as a constructor.
  * ie, var foo = new Communicator("...");
  */
Handle<Value> Communicator::New(const Arguments& args) {
	HandleScope scope;
	cout << "Communicator::New" << endl;
	
	// validate arguments
	if(args.Length()>1) return v8::ThrowException(v8::String::New("Ice.Communicator: Invalid number of arguments"));
	Communicator *p = new Communicator();
	
	//set the args for ice and set the communicator ptr
	char* ice_args[1];
	if(args.Length()>0) ice_args[0] = *String::Utf8Value(args[0]->ToString());
	else ice_args[0] = "";
	int argc = 1;
	p->ic = Ice::initialize(argc, ice_args); //intialize ice
	
	// wrap it up!
	// bind the c++ communicator object to the javascript Communicator object we just created
	p->Wrap(args.Holder());
	return args.This();
}

/**
  * 
  */
Handle<Value> Communicator::StringToProxy(const Arguments &args){
	HandleScope scope;
	cout << "Communicator::StringToProxy" << endl;
	//return scope.Close(Proxy::Initialize(args));
}


}