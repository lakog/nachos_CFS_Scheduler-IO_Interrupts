// ioalarm.cc
//routines to put Request in queue and set interrupt schedule

#include "ioalarm.h"
#include "main.h"

IOAlarm:: IOAlarm(){

    iotimer = new IOTimer(this);
}

IOAlarm:: ~IOAlarm(){

    delete iotimer;
}

void IOAlarm :: CallBack(){

    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    List<Request*> temp; // temporary list to keep requests that need more time
    
    while(!kernel->events->IsEmpty()){
        
        Request *req = kernel->events->RemoveFront();
        // cout << "!!! Current request's runtime is "<< req->getCompletionTime()<<endl;
        
        if(req->getCompletionTime() > kernel->stats->totalTicks){
            // cout << "!!! Request's runtime is more than current ticks\n";
            temp.Append(req);

        }else
        {
            kernel->scheduler->ReadyToRun(req->getThread());
        }
    
    }
    while(!temp.IsEmpty()){

        kernel->events->Insert(temp.RemoveFront()); // reinsert needed requests to the events queue

    }


}