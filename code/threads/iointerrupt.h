#ifndef IO_INTERRUPT_H
#define IO_INTERRUPT_H

#include "thread.h"
#include "request.h"

#pragma once

class IOInterrupt{

    public :
    	static void Read(char* str);     
        static  void Write(char* str);
};
#endif