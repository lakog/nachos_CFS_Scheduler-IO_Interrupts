#ifndef IO_TIMER_H
#define IO_TIMER_H

#include "copyright.h"
#include "utility.h"
#include "callback.h"
#include "iointerrupt.h"
#pragma once 

class IOTimer : public CallBackObj {
  public:
    IOTimer(CallBackObj *cb);

    virtual ~IOTimer() {}
    
    void Disable();
    				
    void CallBack();
			
    void SetInterrupt();  	

  private:

    CallBackObj *callPeriodically; 

    bool disable;  
 
    
};

#endif