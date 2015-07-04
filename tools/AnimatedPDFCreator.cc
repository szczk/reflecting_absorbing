#include "AnimatedPDFCreator.hh"




AnimatedPDFCreator::AnimatedPDFCreator ( Settings *s , double min, double max, int bins ) : settings ( s ),nBins ( bins ), tMin ( min ), tMax ( max ),  histograms ( nullptr )
{
     this->init();
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
          gsl_histogram_set_ranges_uniform ( h, tMin , tMax );
     }
     return h;
}


void AnimatedPDFCreator::add ( double time, double position )
{
     gsl_histogram * h = this->getHistogram ( time );
     gsl_histogram_increment ( h, position );
}


void AnimatedPDFCreator::save()
{
     if ( histograms!=nullptr ) {

          for ( auto it = histograms->begin() ; it != histograms->end(); ++it ) {
               this->saveHistogram ( ( *it ).second, ( *it ).first );
          }
     }

}


void AnimatedPDFCreator::saveHistogram ( gsl_histogram* histogram, double time )
{

}


/*
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


}*/
