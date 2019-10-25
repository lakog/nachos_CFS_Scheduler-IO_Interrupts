    #include <iostream>
    #include <fstream>
    #include <string>
    #include <sstream>
    #include "main.h"
    #include "thread.h"
    #include "rbt.h"

    void IOBound(int arg){
        // Writing and Reading operations
        cout<<endl;
        cout << "Thead ("<< kernel->currentThread->getName()<<")"<<endl;
        IOInterrupt *ioInterrupt = new IOInterrupt;
        ioInterrupt->Write("TEST");

        ioInterrupt->Read("TEST");

        ioInterrupt->Write("TEST2");

        for(int i=0;i<100;i++){

            kernel->interrupt->OneTick();
        }
        ioInterrupt->Write("TEST3");
        ioInterrupt->Read("TEST4");

        ioInterrupt->Read("TEST4");
        cout << kernel->currentThread->getName()<< " Finished"<<endl; 
        return;

    }

    void CPUBound(int arg){
        // Computations for 1 million time ticks
        cout<<endl;
        cout << "Thead ("<< kernel->currentThread->getName()<<")"<<endl;
        
        for(int i=0; i < 1000000; i++){

            kernel->interrupt->OneTick();
        }
        cout << kernel->currentThread->getName()<< " Finished"<<endl; 
    }

    void Mixed(int arg){
        // Miixed operations
        cout<<endl;
        cout << "Thead ("<< kernel->currentThread->getName()<<")"<<endl;

        IOInterrupt *mixedInterrupt = new IOInterrupt;
        mixedInterrupt->Write("TEST");
        
        cout <<"Thread "<< kernel->currentThread->getName()<<" Ticks ("<<kernel->stats->totalTicks<<")"<<endl;
        
        for(int i=0;i<50;i++){
            kernel->interrupt->OneTick();
        }
        
        cout <<"Thread "<< kernel->currentThread->getName()<<" Ticks ("<<kernel->stats->totalTicks<<")"<<endl;
        
        mixedInterrupt->Read("TEST");

        for(int i=0;i<50;i++){
            kernel->interrupt->OneTick();
        }
        mixedInterrupt->Write("TEST");

        cout << kernel->currentThread->getName()<< " Finished"<<endl; 
    }


    void
    ThreadTest()
    {

        cout<< "*** Simulation Start ***"<<endl;
        
        for (int i = 0; i < 10; ++i)
        {
            //forking IO bound threads
            ostringstream iostrm;
            iostrm << i+1;
            string numStr1 = "IO Task "+iostrm.str();

            char *cstr1 = new char[numStr1.length() + 1];
            strcpy(cstr1, numStr1.c_str()); //creating thread name for debugging

            Thread *t1 = new Thread(cstr1);
            t1->Fork((VoidFunctionPtr) IOBound, (void *) 1);

            //forking CPU bound threads
            // ostringstream iostrm;
            // iostrm << i+1;
            string numStr2 = "CPU Task "+iostrm.str();

            char *cstr2 = new char[numStr2.length() + 1];
            strcpy(cstr2, numStr2.c_str()); //creating thread name for debugging

            Thread *t2 = new Thread(cstr2);
            t2->Fork((VoidFunctionPtr) CPUBound, (void *) 1);

            //forking Mixed bound threads
            // ostringstream iostrm;
            // iostrm << i+1;
            string numStr3 = "MIXED Task "+iostrm.str();

            char *cstr3 = new char[numStr3.length() + 1];
            strcpy(cstr3, numStr3.c_str()); //creating thread name for debugging

            Thread *t3 = new Thread(cstr3);
            t3->Fork((VoidFunctionPtr) Mixed, (void *) 1);

        }   
        // for (int i = 0; i < 10; ++i)
        // {

        // }   
        // for (int i = 0; i <10 ; ++i)
        // {

        // }


    }