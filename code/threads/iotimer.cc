#include "iotimer.h"
#include "main.h"
#include "sysdep.h"

 IOTimer:: IOTimer(CallBackObj *cb){
  callPeriodically = cb;
  SetInterrupt();
}

void IOTimer :: CallBack(){

  if(!kernel->events->IsEmpty()){
    cout<<"\n-------	Events Count:   "<< kernel->events->NumInList()<<" Tick: "<<kernel->stats->totalTicks<<"-------\n";
  }

  callPeriodically->CallBack();

  SetInterrupt();

}

void IOTimer:: Disable(){
  disable = TRUE; 
}

void IOTimer::SetInterrupt(){

  kernel->interrupt->Schedule(this, TimerTicks, IOInt);
}