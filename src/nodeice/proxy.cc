
#include "proxy.h"

namespace NodeIce{


// keep this around forever. (or at least i think. check out the node source code for node_crypto.cc for a similar example.)
static Persistent<FunctionTemplate> proxy_constructor;

Proxy::Proxy(){
	cout << "Proxy constructor" << endl;
}

/**
  * create the object template
  * you can think of this like the following code:
  * var Proxy = function() { // Initialize...  }
  */
Handle<Value> Proxy::Initialize(const Handle<v8::Object> target){
	cout << "Proxy::Initialize" << endl;
	
	HandleScope scope;
	
	Local<FunctionTemplate> t = FunctionTemplate::New(Proxy::New);
	proxy_constructor = Persistent<FunctionTemplate>::New(t);
	
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(String::NewSymbol("Proxy"));
	
	target->Set(String::NewSymbol("Proxy"), t->GetFunction());
	
	// //if(args.Length()!=1) return v8::ThrowException(v8::String::New("Invalid number of arguments"));
	// 
	// //get the ICE proxy arguments from the first parameter
	// string ice_proxy_args(*String::Utf8Value(args[0]->ToString()));
	// Handle<v8::Object> self = (args.This());
	// NodeIce::Proxy * ex = new NodeIce::Proxy();
	// Communicator * communicator = (Communicator*)(self->GetPointerFromInternalField(0));
	// 
	// // create and try to return the ICE proxy
	// Ice::ObjectPrx base = communicator->ic->stringToProxy(ice_proxy_args);
	// if (!base) return v8::ThrowException(v8::String::New("Could not create proxy"));
	// 
	// Local<FunctionTemplate> proxy_ft = FunctionTemplate::New();
	// proxy_ft->SetClassName(String::NewSymbol("Proxy"));
	// proxy_ft->InstanceTemplate()->SetInternalFieldCount(1);//make room for the nodeice proxy class ptr
	// Local<Function> proxy_f = proxy_ft->GetFunction();// get an instance of the proxy to be returned
	// Local<v8::Object> proxy_o = proxy_f->NewInstance();
	// 
	// Proxy *proxy = new Proxy();
	// 
	// proxy->setBase(base);
	// proxy->Wrap(proxy_o);
	// return scope.Close(proxy_o);
}

Handle<Value> Proxy::New(const Arguments& args) {
	cout << "Proxy::New" << endl;
	HandleScope scope;
	Proxy *p = new Proxy();
	p->Wrap(args.Holder());
	return scope.Close(args.This());
}



} // namespace NodeIce