#include "sensor.h"
using namespace std;
sensor::sensor()
{
    //ctor
}

sensor::~sensor()
{
    //dtor
}
int sensor::getrdg() //getrdg is a function in class sensor. It returns and int.
{    rdg = 5*3;
    return (rdg);
}
