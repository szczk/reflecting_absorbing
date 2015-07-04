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

     double L = 5.0;

     //      sim->setLeftBorder( new AbsorbingBorder( -L ) );
     sim->setLeftBorder ( new ReflectingBorder ( -L ) );
     sim->setRightBorder ( new ReflectingBorder ( L ) );



     int nBins = 100;

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



void saveHisto ( gsl_histogram * histogram, const char * variable , double tMin, double tMax, int nBins, Settings * settings )
{
     if ( histogram==nullptr ) {
          cout << "NULL HISTOGRAM!!!"<<endl;
          return;
     }


     char datafileName[200];
     char dataFullPath[200];
     char datafileNamePlot[200];

     sprintf ( datafileName,"%s_residence_time_distr_%s.txt", settings->getFullOutputFilesPrefix().c_str() , variable );
     sprintf ( dataFullPath,"%s/%s", settings->getStoragePath() , datafileName );
     sprintf ( datafileNamePlot,"%s/%s_residence_time_distr_%s.plt",settings->getStoragePath(), settings->getFullOutputFilesPrefix().c_str() , variable );




     ofstream plotScript ( datafileNamePlot ,ios_base::out );

     plotScript << "reset\n";
//      plotScript << "set term png enhanced \n";

     plotScript << "set title '{/Symbol a} = " << settings->getJumpsParameter();
     plotScript << " D = " << settings->getNoiseIntensity();
     plotScript << "'\n";

     plotScript << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     plotScript << "set output \""<< settings->getFullOutputFilesPrefix() << "_residence_time_distr_"<< variable <<".eps\"\n";

     plotScript << "set xrange ["<< tMin <<":"<<  tMax << "]\n";
//      plotScript << "set yrange [0:1]\n";

     plotScript << "set xlabel 'x'\n";
     plotScript << "set ylabel '"<< variable << "'\n";


     double dt = ( tMax-tMin ) / nBins;
     cout << "dt = " << dt << endl;
     double scale = 1.0/ ( gsl_histogram_sum ( histogram ) );
     cout << "scale: "<< scale << endl;
     //gsl_histogram_scale ( histogram,  scale );



     FILE * pFile = fopen ( dataFullPath,"w" );

     gsl_histogram_fprintf ( pFile,  histogram, "%g", "%g" );

     fclose ( pFile );


     plotScript<< "plot '"<<datafileName <<"' using ($1+ ($2-$1)/2):3 with linespoints title '"<< variable << "' lc rgbcolor 'red' lw 2\n";


     plotScript.close();


}
