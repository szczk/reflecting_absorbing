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





void Border::operator() ( )
{

    // ..
}

const char* Border::toString()
{
     return "base class!";
}
