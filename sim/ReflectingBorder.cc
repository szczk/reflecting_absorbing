#include "ReflectingBorder.hh"


ReflectingBorder::ReflectingBorder ( double position ) : Border ( position )
{

}


ReflectingBorder::~ReflectingBorder()
{

}

bool ReflectingBorder::operator() ( Particle * p )
{

     if (  ( this->getPosition() > 0.0 ) ) {
          //we are right border
          if ( p->getPosition() >=  this->getPosition() )  p->setPosition ( this->getPosition() );
	  
// 	  cout << "right reflecting border: setting particle position to " << this->getPosition() <<endl;

     } else if ( ( this->getPosition() < 0.0 ) ) {
          // we are left border
          if ( p->getPosition() <=  this->getPosition() )  p->setPosition ( this->getPosition() );
	  
	  
// 	  cout << "left reflecting border: setting particle position to " << this->getPosition() <<endl;
	  
	  
     } else {
          cerr << "unexpected situation at reflecting border! " << "border position: " << getPosition() <<", particle position: " << p->getPosition() << endl;
          throw -1;
     }
     return false;
}


const char * ReflectingBorder::toString()
{
     return "Reflecting border ";
}


