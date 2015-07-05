#ifndef __ANIMATED_PDF_CREATOR__
#define __ANIMATED_PDF_CREATOR__

#include "../core/Settings.hh"
#include <gsl/gsl_histogram.h>
#include <map>
#include <iostream>

using namespace std;

// creates histograms for every time point

class AnimatedPDFCreator {
  
private:
  Settings * settings;
  int nBins;
  double tMin;
  double tMax;
  
  int steps = 0;
  int saveEverySteps;
  
  map<double , gsl_histogram *> * histograms;
  
  void init();
  void cleanUp();
  
  
  gsl_histogram * getHistogram(double time);
  
  void saveHistogram(gsl_histogram * histogram, double time, int count);
  
public:
  
  AnimatedPDFCreator(Settings *s , double min, double max, int bins);
  ~AnimatedPDFCreator();
  
  
  /**
   * Add value point at time  and position 
   * 
   */
  void add(double time, double position);
  
  void newSim();
  
  void save();
  
};

#endif