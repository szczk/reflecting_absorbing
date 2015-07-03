#include "Simulation.hh"


Simulation::Simulation ( Settings * s )  : rand ( nullptr ) 
{
     this->settings = s;
     this->init();
}


Simulation::~Simulation()
{


     this->cleanUp();
}


void Simulation::init()
{
     cout << "initializing simulation"<<endl;
     this->rand = new Randoms();
     this->reset();
}



void Simulation::cleanUp()
{
     cout << "destroying simulation"<<endl;

     if ( rand!=nullptr ) delete rand;
    

}

void Simulation::reset()
{
//      this->rand->reset();  
}


void Simulation::run (  )
{
  
   Particle * walker = new Particle( this->settings->getX0() );
   double t = this->settings->getStartTime();
   double endTime = this->settings->get ( "maxT" );
   double dt = this->settings->getDt();
   double alpha = this->settings->getAlpha();
   double beta = this->settings->getBeta();
   
   double dL = exp ( log ( dt ) /alpha ); //pow(dt, 1.0/alpha);
   
   while( walker->absorbed() ||  t <= endTime ) {
     
     double this->rand->getLevyStable ( alpha,beta,  sigma,  0.0 );();
     
     
     
     t+=dt;
   }
   
   

   delete walker;
}

