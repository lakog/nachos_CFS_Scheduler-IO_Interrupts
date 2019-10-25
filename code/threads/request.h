#ifndef REQUEST_H
#define REQUEST_H


#include "thread.h"
#pragma once


class Request{

	private : 

		char* str;

		char type; 
		Thread* thread;

		int completionTime;      
		int startingTime;  

	public : 

		Request(char t, Thread *parent, char* s);  

		~Request();

		char getType();
		int getStartingTime();
		int getCompletionTime();
		Thread* getThread();
		char* getStr();

		void setCompletionTime(int delay);
		void setStartingTime(int delay);
		void setStr(char *s);

};
#endif