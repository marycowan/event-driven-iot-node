#include <iostream>
#include <unistd.h>
#include "sensor.h"
#include "iotDataQueue.h"
using namespace std;
class Machine   //class machine whose behaviour depends on state,
{
    //so make state a nested class in state
    class State *current;//machine has a pointer (*current) which points to state
    // class State
public:
    Machine();//functions in machine
    void setCurrent(State *s)// a pointer to state is passed into setCurrent
    {
        current = s;
    }
    void sensing();//functions in machine
    void idle();
    void proc();
};

class State
{
public:
    virtual void sensing(Machine *m)//virtual functions in class state
    {
        // show that state is an abstract class
        cout << "   machine SENSING\n";
    }
    virtual void idle(Machine *m)
    {
        cout << "   machine IDLE\n";
    }
    virtual void proc (Machine *m)
    {
        cout << "  machine Processing\n";
    }
};

void Machine::sensing()//sensing is a function in class machine
{
    current->sensing(this);//current is a pointer to the current state of the machine
}

void Machine::idle()//idle is a function in class machine
{
    current->idle(this);//asking idle function of current state to run a
    // function associated with itself CALLBACK****
}
void Machine::proc()//proc is a function in class machine
{
    current->proc(this);//ASK PROC TO RUN A FUNCTION ASSOC WITH ITSELF.
}
class PROC: public State//Class PROC is a CHILD of state, inherits from state
{
public:
    PROC()
    {
        cout << "   PROC-ctor ";
    };
    ~PROC()
    {
        cout << "   dtor-PROC\n";
    };
    void idle(Machine *m);

};

class SENSING: public State
{
public:
    SENSING()
    {
        cout << "   SENSING-ctor ";
    };
    ~SENSING()
    {
        cout << "   dtor-SENSING\n";
    };
    void proc(Machine *m);
    /*  {
          cout << "   going from SENSING to processing";
          m->setCurrent(new PROC());
          delete this;
      }*/
    //  void idle(Machine *m);
};
void SENSING::proc(Machine *m)
{
    usleep(5000000);
    iotDataQueue temperature;//create q object
    sensor tempSens;// sensor object
    temperature.init();//init temp q
    for(int num=0; num<10; num++)//loop to get 10 readings from teh two sensors and put into queues.
    {
        int latestTemp = tempSens.getrdg();// get reading from temp sensor and assign to latestTemp

        temperature.qput(latestTemp);//put latestTemp into  Q
cout << "latest temp to be read is: " << latestTemp;
cout << '\n';
    }

    cout << "   going from SENSING to processing";
    usleep(5000000);
    m->setCurrent(new PROC());
    delete this;
}

class IDLE: public State
{
public:
    IDLE()
    {
        cout << "   IDLE-ctor ";
    };
    ~IDLE()
    {
        cout << "   dtor-IDLE\n";
    };
    void sensing(Machine *m)
    {int go;
        usleep(50000000);
        cout << " press 1 to proceed from idle to sensing:";// User must press a button to move from idle to sensing.
        while (go !=1)
              cin >> go;// could use a timer either
        cout << "   going from IDLE to SENSING";
        m->setCurrent(new SENSING());
        delete this;
    }
};
void PROC::idle(Machine *m)
{
    usleep(50000000);
    iotDataQueue temperature;//create q object
    sensor tempSens;// sensor object
    temperature.init();//init temp q
    cout << "Contents of Temperature queue: \n";
    for(int num=0; num<10; num++)//loop to cout 10 times
    {
        cout << temperature.qget() << " degrees C\n";
    }


    cout << "   going from PROCessing to IDLE";
    usleep(50000000);
    m->setCurrent(new IDLE());
    delete this;
}

Machine::Machine()
{
    current = new IDLE(); // all new machines created in IDLE state
    cout << '\n';
}

int main()
{
    void(Machine:: *ptrs[])() =//an array of pointers to functions in class Machine
    {
        Machine::idle, Machine::sensing, Machine::proc//these are the functions in machine that can be pointed at
    };
    int go;                 //   [0] means idle,[1] means sensing etc.
    Machine fsm;//instantiate an object of class machine
    cout << "FSM created in IDLE state:";
    usleep(50000000);
    //cout << " press 1 to proceed to sensing:";
   //     while (go !=1)
   //           cin >> go;
    int num  ;
        for(num=1; num<20; num++)
    {

                (fsm.*ptrs[num%3])();

    }
}

