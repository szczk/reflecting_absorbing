#include "Border.hh"


Border:: Border ( double position ) : positionX(position)
{
    
     this->init();
}



Border:: ~Border()
{

     this->destroy();
}



void Border::init()
{

}


void Border::destroy()
{
    
}





void Border::operator() (Particle *p)
{
    cerr << "base class!";
    throw -1;
}

void Border::interact(Particle *p ) 
{
    this->operator()(p);
}

const char* Border::toString()
{
     return "base class!";
}
