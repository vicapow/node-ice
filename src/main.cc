/**
  * for an simple client example using ICE with C++: http://doc.zeroc.com/pages/viewpage.action?pageId=12648478
  */

// Ice 
#include <Ice/Ice.h>
using namespace Ice;

// Node JS
#include <v8.h>
#include <node.h>
using namespace v8;
using namespace node;

// local includes
#include "nodeice/nodeice.h"


void init(Handle<v8::Object> target) {
	NodeIce::Initialize(target);
}

NODE_MODULE(main, init);