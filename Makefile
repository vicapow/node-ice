#just for convience so all that needs to happen is make run
all:
	node-waf configure build
	
run: all
	node driver.js