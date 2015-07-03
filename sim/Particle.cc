#include "Particle.hh"


Particle::Particle(double initialX) :  positionX(0.0), isAbsorbed(false) {
  this->positionX = initialX;
}


Particle::~Particle() {
  
}

void Particle:: advance(double dX) {
 this->positionX += dX; 
}