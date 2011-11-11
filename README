
::WARNING:: This is very much a work in progress


This project provides a bridge to the ZeroC ICE RPC framework.

What follows is a simple example. Note that this hasn't yet even been fully implemented but this should give you an idea of what we're aiming for:

var ice = require('ice')
	, Demo = require('./gen-src/Demo')

try{
	var communicator = new ice.initialize("SimplePrinter:default -p 9000");
	var proxy = communicator.stringToProxy("Demo/Printer -f m0");
	var printer = Demo.PrinterPrx.ice_checkCast(proxy,'::Demo::Printer');
	print.printString("Hello World!",function(err){
		if(err) throw err;
		console.log('success!');
	});
}catch(err){
	console.log('unable to connect to ice');
	console.log(err);
}