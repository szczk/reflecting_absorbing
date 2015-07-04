#ifndef __ABSORBING_BORDER__
#define __ABSORBING_BORDER__


#include "Border.hh"





class AbsorbingBorder : public Border {


public:

     AbsorbingBorder ( double position );
     virtual ~AbsorbingBorder();
     virtual const char * toString();
     virtual void operator() ( Particle * );

};




#endif