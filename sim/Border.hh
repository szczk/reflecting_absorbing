#ifndef __BORDER_HH__
#define __BORDER_HH__

// #include "../core/Randoms.hh"
// #include "../core/Settings.hh"
// #include "../main.hh"
#include "Particle.hh"
#include <iostream>

using namespace std;

/**
 * Granica ukladu
 * 
 * funktor
 */
class Border {

protected:
     double positionX;
     void init();

     void destroy();


public:
     Border(double position);
     virtual ~Border() =0 ;

     virtual const char * toString();

     virtual bool operator()(Particle *) = 0;
     double getPosition() { return positionX; }


     bool interact(Particle *p);
//      virtual vec getExact ( const vec X, double dt ) = 0;

};


#endif

