#ifndef __SIMULATION__HH__
#define __SIMULATION__HH__

#include "../core/Settings.hh"
#include "../core/Randoms.hh"
#include <gsl/gsl_histogram.h>
#include "Particle.hh"
#include "Border.hh"
#include "../tools/AnimatedPDFCreator.hh"
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


     bool ok;
     void reset();

public:

     Simulation ( Settings* s );
     ~Simulation();




     void run ( AnimatedPDFCreator * );

     void setLeftBorder ( Border * b ) {
          this->leftBorder = b;
          cout <<"Left border: " << this->leftBorder->toString() << " at " << leftBorder->getPosition() << endl;
     }

     void setRightBorder ( Border * b ) {
          this->rightBorder = b;
          cout <<"Right border: " << this->rightBorder->toString() << " at " << rightBorder->getPosition() << endl;
     }


};



#endif
