#include "main.hh"



void saveHisto ( gsl_histogram * histogram, const char * variable , double tMin, double tMax, int nBins, Settings * settings );


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
     int tenPerc = ( ntrajectories>10 ) ? ( int ) ( ntrajectories*0.01 ) : 1;

     Simulation * sim = new Simulation ( &settings );

     double L = settings.get("BORDER_L");

          sim->setLeftBorder( new AbsorbingBorder( -L ) );
//      sim->setLeftBorder ( new ReflectingBorder ( -L ) );
     sim->setRightBorder ( new ReflectingBorder ( L ) );



     int nBins = settings.get("NBINS");

//      gsl_histogram * p_total = gsl_histogram_alloc ( nBins );
//      gsl_histogram_set_ranges_uniform ( p_total, -L , L );

     time_t start_time = ::time ( 0 );


     AnimatedPDFCreator * anim = new AnimatedPDFCreator ( &settings , -L, L,nBins );

     //generate trajectories
     for ( int nt =0; nt < ntrajectories ; nt++ ) {

          if ( nt%tenPerc==0 ) {
               double perc = ( ( 100.0*nt ) / ( ntrajectories ) );
               //cout << nt<<"/"<<ntrajectories<< "\t"<< ((int) perc) << "% in " << timeTaken <<"s" << "\t ETA:" <<  (timeTaken*100)/perc << endl;
               cout << nt<<"/"<<ntrajectories<< "\t"<< ( ( int ) perc ) << "% \t" << System::calculateTime ( start_time, perc ) << endl;

          }

          sim->run ( anim );

     }



     delete sim;

//      saveHisto ( p_total, "p(x)" , -L, L, nBins, &settings );

//      gsl_histogram_free ( p_total );



     anim->save();
     delete anim;

     ///===================================================================================================


     sys.finish();
     sys.printTimeSummary();

     return 0;
}


