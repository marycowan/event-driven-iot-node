#include <iostream>
#include "iotDataQueue.h"

using namespace std;

iotDataQueue::iotDataQueue()
{
    //ctor
}

iotDataQueue::~iotDataQueue()
{
    //dtor
}
void iotDataQueue::init()//define functions in class iotDataQueue
{
    // init initialises the queue
    rloc = sloc = 0;
}

//initialise the queue
void iotDataQueue::qput(int i)// qput puts the data into the queue until it's full
{
    if(sloc==10)
    {
        cout << "queue is full. \n";
        return;
    }
    sloc++;
    q[sloc] = i;// I swapped these lines, were they in the right place?

}

//get an integer from the queue
int iotDataQueue::qget()// qget gets the data from the queue
{
    if(rloc == sloc)
    {
        cout << "queue underflow. \n";// I don't understand this line really does it mean
        return 0;                      // less than 10 readings in queue, doesn't seem to...
    }
    rloc++;
    return q[rloc];

}
