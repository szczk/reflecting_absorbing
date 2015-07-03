#ifndef __PARTICLE_HH__
#define __PARTICLE_HH__


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
      
      
      
      void advance(double dx);
      
      void absorb() { this->isAbsorbed = true; }
      
      bool absorbed() {return isAbsorbed;}
  
  
};


#endif
