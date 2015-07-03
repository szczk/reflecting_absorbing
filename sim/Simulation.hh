#ifndef __SIMULATION__HH__
#define __SIMULATION__HH__

#include "../core/Settings.hh"
#include "../core/Randoms.hh"

#include "Particle.hh"
#include "Border.hh"
// #include "../tools/Datafile.hh"

// #include "QuadraticPotential.hh"
// #include "SquarePotential.hh"


using namespace std;



class Simulation {

private:
     Settings * settings;
     Randoms * rand;
     
     void init();
     void cleanUp();

     Border * leftBorder;
     Border * rightBorder;
     

     void reset();

public:

     Simulation ( Settings* s );
     ~Simulation();




     void run ();


};



#endif
