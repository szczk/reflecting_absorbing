#include "main.hh"
#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_histogram.h>
#include <fstream>




int main ( int argc, char **argv )
{
     cout << endl << endl;

     System& sys = System::getInstance();
     sys.start();

     sys.printInfo();

     Settings& settings = Settings:: getInstance ( "settings.dat" );
     settings.readCommandLineParameters ( argc,argv );
     settings.printParameters();


     ///==================================================================================


     //double maxT = settings.get ( "maxT" );
     //double dt = settings.get("dt");

     double ntrajectories = settings.getNtrajectories();
     int tenPerc = ( ntrajectories>10 ) ? ( int ) ( ntrajectories*0.1 ) : 1;

     Simulation * sim = new Simulation( &settings );


     //generate trajectories
     for ( int nt =0; nt < ntrajectories ; nt++ ) {

          if ( nt%tenPerc==0 ) {
               cout << nt<<"/"<<ntrajectories<<endl;
          }  

          sim->run();

     }



     delete sim;



     ///===================================================================================================


     sys.finish();
     sys.printTimeSummary();

     return 0;
}


