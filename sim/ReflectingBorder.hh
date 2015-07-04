#ifndef __REFLECTING_BORDER__
#define __REFLECTING_BORDER__


#include "Border.hh"





class ReflectingBorder : public Border {


public:

     ReflectingBorder ( double position );
     virtual ~ReflectingBorder();
     virtual const char * toString();
     virtual void operator() ( Particle * );

};


#endif
