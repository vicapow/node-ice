

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
	
	// give the communicator a 'private' reference to the ice module object.
	// this is required if we want to allow Proxys to be created via the Communicator.
	// see Communicator::StringToProxy for an example of this usage.
	t->InstanceTemplate()->Set("__ice",target);
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
  * take the string provided as the first argument and return a new Ice Proxy
  */
Handle<Value> Communicator::StringToProxy(const Arguments &args){
	HandleScope scope;
	cout << "Communicator::StringToProxy" << endl;
	
	if(args.Length()!=1) return v8::ThrowException(v8::String::New("Ice.Communicator: Invalid number of arguments"));
	if(!args[0]->IsString()) return v8::ThrowException(v8::String::New("Ice.Communicator: Invalid argument 0. expected string"));
	
	Handle<v8::Object> ice_module = args.Holder()->Get(String::New("__ice"))->ToObject();
	Handle<v8::Value> proxy_constructor_value = ice_module->Get(String::New("Proxy"));
	Handle<v8::Function> proxy_constructor_func = Handle<Function>::Cast(proxy_constructor_value);
	Handle<v8::Object> proxy_obj = proxy_constructor_func->NewInstance();
	Proxy* proxy = ObjectWrap::Unwrap<Proxy>(proxy_obj);
	
	Handle<String> proxy_str = args[0]->ToString(); //proxy string to use
	Communicator* c = ObjectWrap::Unwrap<Communicator>(args.Holder());
	proxy->base = c->ic->stringToProxy(*String::Utf8Value(proxy_str));
	cout << "argument 0: " << *String::Utf8Value(proxy_str) << endl;
	
	scope.Close(proxy_obj); // return the new proxy
}


}