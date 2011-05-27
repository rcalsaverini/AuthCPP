#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include "Agent.hpp"
using namespace boost::accumulators;

int getSeed();


//class to accumulate the statistics about the simulation
class Results {
private:
  
  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > accDouble;
  typedef accumulator_set<int,    stats<tag::mean, tag::variance(lazy)> > accInt;
  
  accDouble accEnergy, accMaxCentrality, accAvgCentrality, accLength, accAccept, accAvgDeg;
  accInt    accMaxDeg;

public:
  Results(){};                  // constructor;
  
  void acc(double energy, 
	   double accept,
	   int    maxdeg,
	   double avgdeg, 
	   double length, 
	   double maxcen, 
	   double avgcen) {   // accumulate values to calculate means and variances
    
    accEnergy(energy); 
    accAccept(accept);
    accMaxDeg(maxdeg);
    accAvgDeg(avgdeg);     
    accMaxCentrality(maxcen);
    accAvgCentrality(avgcen);
    accLength(length);
  }

  double avgEnergy()		{return  mean(accEnergy);}              //get mean energy
  double varEnergy()		{return  variance(accEnergy);}          //get energy variance
  double avgAcceptance()	{return  mean(accAccept);}		//get mean monte carlo acceptance rate
  double varAcceptance()	{return  variance(accAccept);}		//get mc acceptance rate variance
  double avgMaxDeg()		{return  mean(accMaxDeg);}		//get mean maximum degree
  double varMaxDeg()		{return  variance(accMaxDeg);}		//get variance maximum degree
  double avgAvgDeg()		{return  mean(accAvgDeg);}		//get mean average degree
  double varAvgDeg()		{return  variance(accAvgDeg);}		//get variance average degree
  double avgMaxCen()		{return  mean(accMaxCentrality);}	//get mean maximum centrality
  double varMaxCen()		{return  variance(accMaxCentrality);}	//get variance maximum centrality
  double avgAvgCen()		{return  mean(accAvgCentrality);}	//get mean average centrality
  double varAvgCen()		{return  variance(accAvgCentrality);}	//get variance average centrality
  double avgLength()		{return  mean(accLength);}		//get mean average geodesic length
  double varLength()		{return  variance(accLength);}		//get variance average geodesic length
  
 
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
  SimSolo(int n_, double beta_, double alpha_);		//constructor
  bool flipStep(double& E0);				// a single flipstep
  double mcStep(double& E0);				// a single montecarlo step = n flipsteps
  void metroLoop(int nsteps, int burn, Results& res);	//full montecarlo loop.

};


