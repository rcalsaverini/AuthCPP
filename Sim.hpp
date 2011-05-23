#include "Agent.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
using namespace boost::accumulators;

int getSeed();


class Results {
private:
  
  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > accDouble;
  typedef accumulator_set<int,    stats<tag::mean, tag::variance(lazy)> > accInt;
  
  accDouble accEnergy, accMaxCentrality, accAvgCentrality, accLength, accAccept, accAvgDeg;
  accInt    accMaxDeg;

public:
  Results(){};
  void acc(double energy, 
	   double accept,
	   int    maxdeg,
	   double avgdeg, 
	   double length, 
	   double maxcen, 
	   double avgcen) {
    
    accEnergy(energy); 
    accAccept(accept);
    accMaxDeg(maxdeg);
    accAvgDeg(avgdeg);     
    accMaxCentrality(maxcen);
    accAvgCentrality(avgcen);
    accLength(length);
  }

  double avgEnergy()		{return  mean(accEnergy);}
  double varEnergy()		{return  variance(accEnergy);}
  double avgAcceptance()	{return  mean(accAccept);}
  double varAcceptance()	{return  variance(accAccept);}
  double avgMaxDeg()		{return  mean(accMaxDeg);}
  double varMaxDeg()		{return  variance(accMaxDeg);}
  double avgAvgDeg()		{return  mean(accAvgDeg);}
  double varAvgDeg()		{return  variance(accAvgDeg);}
  double avgMaxCen()		{return  mean(accMaxCentrality);}
  double varMaxCen()		{return  variance(accMaxCentrality);}
  double avgAvgCen()		{return  mean(accAvgCentrality);}
  double varAvgCen()		{return  variance(accAvgCentrality);}
  double avgLength()		{return  mean(accLength);}
  double varLength()		{return  variance(accLength);}
  
 
};

class SimSolo {
private:
  int n;
  double alpha;
  double beta;
  RndGen rng;
  Agent agent;
  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > accDouble;
  typedef accumulator_set<int,    stats<tag::mean, tag::variance(lazy)> > accInt;

public:
  SimSolo(int n_, double beta_, double alpha_);
  bool flipStep(double& E0);
  double mcStep(double& E0);
  void metroLoop(int nsteps, int burn, Results& res);

};


