#include "Simulation.hh"


Simulation::Simulation ( Settings * s )  : rand ( nullptr ) , leftBorder ( nullptr ), rightBorder ( nullptr ), ok ( false )
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
     rand->reset();



}



void Simulation::cleanUp()
{
     cout << "destroying simulation"<<endl;

     if ( rand!=nullptr ) delete rand;
     if ( leftBorder!=nullptr ) {
          cout << " deleting left border" <<endl;
          delete leftBorder;
     }
     if ( rightBorder!=nullptr ) {
          delete rightBorder;
          cout << " deleting right border" <<endl;
     }

}

void Simulation::reset()
{

     this->rand->reset();


}


void Simulation::run ( AnimatedPDFCreator * anim )
{
   
     this->ok = ( leftBorder!=nullptr ) && ( rightBorder!=nullptr );


     if ( !ok ) {
          cerr << "not both borders set!" << endl;
          return;
     }


     Particle * walker = new Particle ( this->settings->getX0() );
     double t = this->settings->getStartTime();
     double endTime = this->settings->get ( "maxT" );
     double dt = this->settings->getDt();
     double alpha = this->settings->getAlpha();
     double beta = this->settings->getBeta();
     double sigma = this->settings->getNoiseIntensity();
     double dL = exp ( log ( dt ) /alpha ); //pow(dt, 1.0/alpha);

     double dx  = 0.0;
// cout << " ---------------------"<< endl;
     while ( ( !walker->absorbed() ) && ( t <= endTime ) ) {

          dx  =  dL * this->rand->getLevyStable ( alpha,beta,  sigma,  0.0 );

// 	  cout << " move  from " << walker->getPosition() << " + " << dx << endl;
	  walker->advance ( dx );
	  
	  
          if ( walker->getPosition() >= rightBorder->getPosition() ) {
               //move right
// 		cout << " move right from " << walker->getPosition() << " + " << dx << endl;

//                if ( ( walker->getPosition() + dx )  >= rightBorder->getPosition() ) {
                    rightBorder->interact ( walker );
//                } else {
//                     walker->advance ( dx );
//                }

          } else if ( walker->getPosition() <= leftBorder->getPosition() ) {
               //move left
// 	       cout << " move left from " << walker->getPosition() << " + " << dx << endl;

//                if ( ( walker->getPosition() + dx ) <= leftBorder->getPosition() ) {
                    leftBorder->interact ( walker );
//                } else {
//                     walker->advance ( dx );
//                }
          }


          anim->add(t, walker->getPosition() );

          t+=dt;
     }
     
     
//      if ( !walker->absorbed() ) {
//           gsl_histogram_increment ( p_total, walker->getPosition() );
//      }
//      cout << "t = " << t << " last position: " << walker->getPosition() << " + " << dx << endl;


     delete walker;
}

