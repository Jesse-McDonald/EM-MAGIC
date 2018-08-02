#include <state>
#include <iostream>
int startServer(){
	std::cout<<"server not yet implimented"<<std::endl;
	return 0;
}
int startNode(){
	std::cout<<"node not yet implimented"<<std::endl;
	return 0;
}
int startProcessing(){
	if(SERVER){	
		return startServer;
	}else if(NODE{
		return startNode();
	}else{
		//rough program flow, flesh out later		
	
	}
}

