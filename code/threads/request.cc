#include "request.h"
#include "main.h"

Request::Request(char t, Thread* parent, char* s){
   
    //Creating request object
   	str = s;
    thread = parent;
    type = t;
    
    int random= rand()%10 * 100;

    startingTime = kernel->stats->totalTicks;
    completionTime = random + kernel->stats->totalTicks;
    
}


void 
Request::setStartingTime(int t){
	startingTime = t;
}

void 
Request::setCompletionTime(int t){
	completionTime = t;
}
void 
Request::setStr(char *s){
	str = s;
}


char 
Request::getType() {
	return type;
}

int 
Request::getStartingTime() {
	return startingTime;
}
int 
Request::getCompletionTime() {
	return completionTime;
}

Thread* Request::getThread() {
	return thread;
}

char* 
Request::getStr() {
	return str;
}

