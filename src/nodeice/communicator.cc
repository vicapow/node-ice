

#include "communicator.h"

namespace NodeIce{


Handle<Value> Communicator::Initialize(const Arguments &args){
	
	cout << " IceInitializeHandler()" << endl;
	HandleScope scope;
	
	if(args.Length()!=1) return v8::ThrowException(v8::String::New("Invalid number of arguments"));
	
	// create the 'Communicator' class
	Local<FunctionTemplate> communicator_ft = FunctionTemplate::New();
	communicator_ft->SetClassName(String::NewSymbol("Communicator"));
	communicator_ft->InstanceTemplate()->SetInternalFieldCount(1);//the instance template is what's returned with the function is called as a constructor
	
	// create the 'stringToProxy' function
	Local<FunctionTemplate> stringToProxy_ft = FunctionTemplate::New(Communicator::StringToProxy);
	communicator_ft->InstanceTemplate()->Set(String::NewSymbol("stringToProxy"),stringToProxy_ft->GetFunction());
	Local<Function> communicator_f = communicator_ft->GetFunction();
	Local<v8::Object> communicator_o = communicator_f->NewInstance();
	
	Communicator* communicator = new Communicator();
	
	//set the arguements for ice and set the communicator ptr
	char* ice_args[1];
	ice_args[0] = *String::Utf8Value(args[0]->ToString());
	int argc = 1;
	communicator->ic = Ice::initialize(argc, ice_args);
	
	communicator->Wrap(communicator_o);
	return scope.Close(communicator_o);
}


Handle<Value> Communicator::StringToProxy(const Arguments &args){
	HandleScope scope;
	return scope.Close(Proxy::Initialize(args));
}


}