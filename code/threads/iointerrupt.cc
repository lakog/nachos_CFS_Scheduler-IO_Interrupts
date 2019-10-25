#include "iointerrupt.h"
#include "main.h"


void IOInterrupt:: Read(char* str){

    // creating IO read request
    Request* req = new Request('r', kernel->currentThread, str);

    cout << "\n=======  Read request >> Tick: "<< kernel->stats->totalTicks<<"  ======="<<endl;
    kernel->events->Insert(req); // add to events queue

    cout << "Added to Queue" <<endl;
    cout << "Event Queue Length is "<< kernel->events->NumInList() <<endl<<endl;

    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    kernel->interrupt->SetLevel(IntOn);
    cout << "!! Read - Woke UP " <<endl; // Thread woke up after alarm callback

}

void IOInterrupt:: Write(char* str){

    // creating IO write request
    Request* req = new Request('w', kernel->currentThread, str);

    cout << "\n=======  Write request >> Tick: "<< kernel->stats->totalTicks<<" ======="<<endl;
    kernel->events->Insert(req); // add to events queue

    cout << "Added to Queue" <<endl;
    cout << "Event Queue Length is "<< kernel->events->NumInList() <<endl;
    
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    kernel->interrupt->SetLevel(IntOn);
    cout << "!! Write - Woke UP " <<endl; // Thread woke up after alarm callback
}

