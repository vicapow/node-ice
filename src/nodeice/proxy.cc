
#include "proxy.h"

namespace NodeIce{

Handle<Value> Proxy::Initialize(const Arguments &args){

	cout << "Communicator::StringToProxy" << endl;
	HandleScope scope;

	if(args.Length()!=1) return v8::ThrowException(v8::String::New("Invalid number of arguments"));

	string ice_proxy_args(*String::Utf8Value(args[0]->ToString()));
	Handle<v8::Object> self = (args.This());
	NodeIce::Proxy * ex = new NodeIce::Proxy();
	Communicator * communicator = (Communicator*)(self->GetPointerFromInternalField(0));

	// create and try to return the ICE proxy
	Ice::ObjectPrx base = communicator->ic->stringToProxy(ice_proxy_args);
	if (!base) return v8::ThrowException(v8::String::New("Could not create proxy"));

	Local<FunctionTemplate> proxy_ft = FunctionTemplate::New();
	proxy_ft->SetClassName(String::NewSymbol("Proxy"));
	proxy_ft->InstanceTemplate()->SetInternalFieldCount(1);//make room for the nodeice proxy class ptr
	Local<Function> proxy_f = proxy_ft->GetFunction();// get an instance of the proxy to be returned
	Local<v8::Object> proxy_o = proxy_f->NewInstance();
	
	Proxy *proxy = new Proxy();
	
	proxy->setBase(base);
	proxy->Wrap(proxy_o);
	return scope.Close(proxy_o);
}

} // namespace NodeIce