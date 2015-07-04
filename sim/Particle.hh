#ifndef __PARTICLE_HH__
#define __PARTICLE_HH__

#include <iostream>

/**
 * single random-walking particle
 * 
 */

class Particle {
  
private:
      double positionX;
      bool isAbsorbed;
      
public:
  
      Particle(double initialX);
      ~Particle();
      
      
      double getPosition() { return positionX; }
      void setPosition(double x) { this->positionX = x; }
      
      void advance(double dx);
      
      void absorb() { this->isAbsorbed = true; }
      
      bool absorbed() {return isAbsorbed;}
  
  
};


#endif
