#include "AbsorbingBorder.hh"

AbsorbingBorder::AbsorbingBorder ( double position ) : Border ( position )
{

}

AbsorbingBorder::~AbsorbingBorder()
{

}


const char* AbsorbingBorder::toString()
{
     return "Absorbing border";
}


bool AbsorbingBorder::operator() ( Particle * p )
{
  p->absorb();
  /*
     if ( ( p->getPosition() > 0.0 ) && ( this->getPosition() > 0.0 ) ) {
          //we are right border
          if ( p->getPosition() >=  this->getPosition() )  p->absorb();
	  
	  cout << "right absorbing border: at "<< getPosition() <<"  particle position : " << p->getPosition() <<endl;
	  
	  
     } else if ( ( p->getPosition() < 0.0 ) && ( this->getPosition() < 0.0 ) ) {
          // we are left border
          if ( p->getPosition() <=  this->getPosition() )  p->absorb();
	  
	  cout << "left absorbing border: at "<< getPosition() <<"  particle position : " << p->getPosition() <<endl;
	  
     } else {
          cerr << "unexpected situation!" << endl;
          throw -1;
     }
     
     */
  return true;
}
