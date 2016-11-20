#include <iostream>
#include <unistd.h>
using namespace std;
class Machine   //class machine whose behaviour depends on state,
{
    //so make state a nested class in state
    class State *current;//machine has a pointer (*current) which points to state
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
    {
        usleep(50000000);
        cout << "   going from IDLE to SENSING";
        m->setCurrent(new SENSING());
        delete this;
    }
};
void PROC::idle(Machine *m)
{

    cout << "   going from PROCessing to IDLE";
    usleep(50000000);
    m->setCurrent(new IDLE());
    delete this;
}

Machine::Machine()
{
    current = new IDLE();
    cout << '\n';
}

int main()
{
    void(Machine:: *ptrs[])() =//an array of pointers to functions in class Machine
    {
        Machine::idle, Machine::sensing, Machine::proc//these are the functions in machine that can be pointed at
    };                   //   [0] means idle,[1] means sesning etc.
    Machine fsm;//instantiate an object of class machine
    int num =1;
    for(num=0; num<20; num++)
    {
        //cout << "Enter 1 to start the machine: ";//ie. point at function sensing
        //  cin >> num;
        (fsm.*ptrs[num%3])();

    }
}

