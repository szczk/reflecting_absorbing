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





bool Border::operator() (Particle *p)
{
    cerr << "base class!";
    throw -1;
}

bool Border::interact(Particle *p ) 
{
    return this->operator()(p);
}

const char* Border::toString()
{
     return "base class!";
}
