#include "AnimatedPDFCreator.hh"




AnimatedPDFCreator::AnimatedPDFCreator ( Settings *s , double min, double max, int bins ) : settings ( s ),nBins ( bins ), tMin ( min ), tMax ( max ),  histograms ( nullptr )
{
     this->init();
     double every = s->get("HISTO_EVERY");
     this->saveEverySteps = every/s->getDt();

     cout << "saveEverySteps = " << saveEverySteps <<endl ;
}


AnimatedPDFCreator::~AnimatedPDFCreator()
{
     this->cleanUp();
}


void AnimatedPDFCreator::init()
{
     this->histograms = new map<double, gsl_histogram *>();
}

void AnimatedPDFCreator::cleanUp()
{
     if ( histograms!=nullptr ) {
          cout << "deleting histograms " << endl;
          for ( auto it = histograms->begin() ; it != histograms->end(); ++it ) {

               gsl_histogram * h = ( *it ).second;
               gsl_histogram_free ( h );
          }
          delete histograms;
     }
}


gsl_histogram* AnimatedPDFCreator::getHistogram ( double time )
{
     gsl_histogram * h = nullptr;
     if ( histograms->count ( time ) > 0 ) {
          h = histograms->at ( time );
     } else {
          h = gsl_histogram_alloc ( nBins );
          gsl_histogram_set_ranges_uniform ( h, tMin , tMax + 0.001 );
          this->histograms->insert ( pair<double, gsl_histogram*> ( time,h ) );
     }
     return h;
}


void AnimatedPDFCreator::add ( double time, double position )
{

     if ( steps % saveEverySteps ==0 ) {

          gsl_histogram * h = this->getHistogram ( time );
          gsl_histogram_increment ( h, position );

//     cout << "save, step = "<< steps << "\t t = " << time << " map size = " << histograms->size() <<endl;
     }
     ++steps;


}


void AnimatedPDFCreator::save()
{
     cout << "save()" <<endl;
     int c = 0;
     if ( histograms!=nullptr ) {
          for ( auto it = histograms->begin() ; it != histograms->end(); ++it ) {
               this->saveHistogram ( ( *it ).second, ( *it ).first , ( c++ ) );
          }
     }
     cout << "saved" <<endl;
}

void AnimatedPDFCreator::newSim()
{
     this->steps = 0;
}


void AnimatedPDFCreator::saveHistogram ( gsl_histogram* histogram, double time, int count )
{
     if ( histogram==nullptr ) {
          cout << "NULL HISTOGRAM!!!"<<endl;
          return;
     }

     char datafileName[200];
     char dataFullPath[200];
     char datafileNamePlot[200];

     sprintf ( datafileName,"%s_distribution_t_%f.txt", settings->getFullOutputFilesPrefix().c_str() , time );
     sprintf ( dataFullPath,"%s/%s", settings->getStoragePath() , datafileName );
     sprintf ( datafileNamePlot,"%s/%s_distribution_t_%f.plt",settings->getStoragePath(), settings->getFullOutputFilesPrefix().c_str() , time );


     ofstream plotScript ( datafileNamePlot ,ios_base::out );

     plotScript << "reset\n";
//      plotScript << "set term png enhanced \n";

     plotScript << "set title '{/Symbol a} = " << settings->getAlpha();
     plotScript << " {/Symbol b} = " << settings->getBeta();
     plotScript << " D = " << settings->getNoiseIntensity();
     plotScript << " t = " << time;
     plotScript << "'\n";


     plotScript << "set terminal pngcairo enhanced size 320,240;\n";
     plotScript << "set output \""<< settings->getFullOutputFilesPrefix() << "_distribution_t_"<< count <<".png\"\n";

//      plotScript << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
//      plotScript << "set output \""<< settings->getFullOutputFilesPrefix() << "_distribution_t_"<< count <<".eps\"\n";


     plotScript << "set xrange ["<< tMin <<":"<<  tMax << "]\n";
     plotScript << "set yrange [0:0.2]\n";

     plotScript << "set xlabel 'x'\n";
     plotScript << "set ylabel 'p(x)'\n";


//      double dt = ( tMax-tMin ) / nBins;

     double scale = 1.0/ ( gsl_histogram_sum ( histogram ) );
//   cout << "dt = " << dt << "scale: "<< scale << endl;
     gsl_histogram_scale ( histogram,  scale );

     FILE * pFile = fopen ( dataFullPath,"w" );
     gsl_histogram_fprintf ( pFile,  histogram, "%g", "%g" );
     fclose ( pFile );


     plotScript<< "plot '"<<datafileName <<"' using ($1+ ($2-$1)/2):3 with linespoints title 'p(x)' lc rgbcolor 'red' lw 2\n";
     plotScript.close();
}



