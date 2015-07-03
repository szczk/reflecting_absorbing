#ifndef __BORDER_HH__
#define __BORDER_HH__

// #include "../core/Randoms.hh"
// #include "../core/Settings.hh"
// #include "../main.hh"

using namespace std;

/**
 * Granica ukladu
 * 
 * funktor
 */
class Border {

private:
     double positionX;
     void init();

     void destroy();


public:
     Border(double position);
     virtual ~Border() =0 ;

     virtual const char * toString();

     virtual void operator()() = 0 ;


//      virtual vec getExact ( const vec X, double dt ) = 0;

};


#endif

