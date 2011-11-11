
#ifndef NODEICE_UTIL_H
#define NODEICE_UTIL_H

#include <node.h>
#include <v8.h>
#include <iostream>

using namespace v8;
using namespace node;


namespace NodeIce{

class Util {
	public:
		static Handle<Value> GetInternalFieldCount(const Arguments& args){
			HandleScope scope;
			if(args.Length()!=1) return ThrowException(String::New("invalid arguments"));
			Handle<v8::Object> obj = args[0]->ToObject();
			return Number::New(obj->InternalFieldCount());
		}
		
		static Handle<Value> Intialize(Handle<v8::Object> target){
			HandleScope scope;
			NODE_SET_METHOD(target,"getInternalFieldCount",Util::GetInternalFieldCount);
		}
};


}


#endif