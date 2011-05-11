#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/*#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>*/
//using namespace boost::accumulators;

#include "Sim.hpp"

//get current time in milisseconds precision
int getms() {  
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return (int) tv.tv_usec;    
}

//get the maximum of a vector
template <class a> 
a getMax(std::vector<a>& xs) {
  return std::accumulate(xs.begin(), xs.end(), 0, std::max<a>);
}

//get the mean of a vector
template <class a> 
double getMean(std::vector<a>& xs) {
  return double(std::accumulate(xs.begin(), xs.end(), 0.0))/double(xs.size());
}


//new random agent
Agent newRndAgent(int size, double alpha) {
  Agent tmp(size,getms(), alpha);
  tmp.propose(20*size);
  tmp.accept();
  return tmp;
}

  


SimSolo::SimSolo(int n_, double beta_, double alpha_) : n(n_), alpha(alpha_), beta(beta_)
						      , rng(getms()*getms()) 
						      , agent(n_,getms(), alpha_,0)  {
  //agent.propose(n);
  //agent.accept();
  //std::cout << "energia inicial: " << agent.energy() << std::endl;
}


bool SimSolo::metropStep(double& E0){
  int flips = int(sqrt(n));
  double E = agent.propose(flips);
  if (exp(- beta * (E - E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agent.accept();
    return true;
  }
  return false;
  
}

void SimSolo::metroLoop(int nsteps, int burn, bool verbose,
			double& energy, double& varEnergy, double& avgDeg, double& maxDeg, double& meanAccept,
			double& maxCen, double& avgCen, double& len){

  double E0 = agent.energy();
  int accept = 0;

  //accumulators
  accDouble accEnergy, accMaxCentrality, accAvgCentrality, accLength;
  accInt accAccept, accMaxDeg, accAvgDeg;

  //main loop
  for(int i = 0; i < nsteps; ++i) {
    accept = metropStep(E0);
    if (i > burn) {
      std::vector<int>    tmpdegrees    = agent.degrees();
      std::vector<double> tmpcentrality = agent.betweenness();
      double avgdeg = getMean(tmpdegrees);
      int    maxdeg = getMax(tmpdegrees);
      double avgCentrality = getMean(tmpcentrality);
      double maxCentrality = getMax(tmpcentrality);
      double length = agent.avgLength();
      accEnergy(E0); 
      accAccept(accept);
      accMaxDeg(maxdeg);
      accAvgDeg(avgdeg);     
      accMaxCentrality(maxCentrality);
      accAvgCentrality(avgCentrality);
      accLength(length);

      if(verbose){
	std::cout << i      << " "; //1
	std::cout << E0     << " "; //2
	std::cout << accept << " "; //3
	std::cout << maxdeg << " "; //4
	std::cout << avgdeg << " "; //5 
	std::cout << std::endl;
      }
    }
  }
  energy = mean(accEnergy);
  varEnergy = variance(accEnergy);
  avgDeg = mean(accAvgDeg);
  maxDeg = mean(accMaxDeg);
  meanAccept = mean(accAccept);
  maxCen = mean(accMaxCentrality);
  avgCen = mean(accAvgCentrality);
  len = mean(accLength);
  //std::cout << "Energia final: " << agent.energy() << std::endl;
}



void SimSolo::metroRun(int msteps, int nsteps, int burn) {
  
  double energy, varEnergy, avgDeg, maxDeg, meanAccept, maxCen, avgCen, length;
  if(msteps > 1) {
    accDouble accEnergy, accVarEnergy, accAccept, accMaxDeg, accAvgDeg, accMaxCen, accAvgCen, accLength;
    for(int i = 0; i < msteps; i++){ 
      agent = newRndAgent(n, alpha);
      metroLoop(nsteps, burn, 0, energy, varEnergy, avgDeg, maxDeg, meanAccept, maxCen, avgCen, length);
      accEnergy(energy);
      accVarEnergy(varEnergy);
      accAccept(meanAccept);
      accMaxDeg(maxDeg);
      accAvgDeg(avgDeg);
      accMaxCen(maxCen); accAvgCen(avgCen); accLength(length);
    }
    std::cout << mean(accEnergy) << " " << mean(accVarEnergy) << " ";
    std::cout << mean(accAccept) << " ";
    std::cout << mean(accMaxDeg) << " ";
    std::cout << mean(accAvgDeg) << " ";;
    std::cout << mean(accLength) << " ";;
    std::cout << mean(accMaxCen) << " ";;
    std::cout << mean(accAvgCen) << " ";;
    std::cout << std::endl;
  }
  else {
    metroLoop(nsteps, burn, 0, energy, varEnergy, avgDeg, maxDeg, meanAccept, maxCen, avgCen, length);
    std::cout << energy << " " << varEnergy << " ";
    std::cout << meanAccept << " ";
    std::cout << maxDeg << " ";
    std::cout << avgDeg << " ";
    std::cout << length << " ";
    std::cout << maxCen << " ";
    std::cout << avgCen << " ";
    std::cout << std::endl;
  }
  
}
