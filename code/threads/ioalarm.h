#ifndef IO_ALARM_H
#define IO_ALARM_H

#include "callback.h"
#include "iotimer.h"
#include "utility.h"
#pragma once

class IOAlarm : public CallBackObj{

    public :

        IOAlarm();   
        ~IOAlarm(); 
        
        Request *currentRequest;
        IOTimer *iotimer;

    private : 
       
        void CallBack(); 

};

#endif